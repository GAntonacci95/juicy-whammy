#include "ChannelThread.h"

ChannelThread::ChannelThread(const String& threadName, WaitableEvent* waitToken, uint sampleRate, Window* window)
    : Thread(threadName)
{
    this->token = waitToken;
    this->shifter = new SoundTouch();
    this->reg = new CustomRegister(window);
    this->interpolator = new LagrangeInterpolator();
    this->isConfiged = false;
    
    // HI latency? -> combo (QUICK = true, AA = false)
    this->shifter->setSetting(SETTING_USE_QUICKSEEK, false);
    this->shifter->setSetting(SETTING_USE_AA_FILTER, true);
    this->shifter->setSampleRate(sampleRate);
    this->shifter->setChannels(1);

    this->shifter->setPitchSemiTones(0);
}

// configurazione post-costruttore, preparazione
void ChannelThread::configure(const float* inPtr)
{
    this->currRef = inPtr;
    
    readyData.resize(2 * reg->getWindow()->getBlockSize() - reg->getWindow()->getOverlapSize());
    readyData.fill(0);
    
    isConfiged = true;
}

ChannelThread::~ChannelThread()
{
    shifter->clear();
    shifter->flush();
    delete shifter;
    delete interpolator;
    
    readyData.clear();
    delete &readyData;
}

void ChannelThread::setPitchSemiTones(double currentPitch)
{
    shifter->setPitchSemiTones(currentPitch);
}

bool ChannelThread::isConfigured()
{
    return isConfiged;
}

Array<float> ChannelThread::getReadyData()
{
    return readyData;
}

// ------------------------------ Logica del Thread ------------------------------
void ChannelThread::run()
{
    while(this->isConfigured())
    {
        // ! wait for the presence of new data
        this->wait(-1);
        
        this->reg->leftShift(currRef);
        
        // pitch-shifting
        // di frame a cavallo (del precedente col corrente)
        horseWin = reg->getHorseWin();
        horseWinShift.clearQuick();
        horseWinShift.addArray(horseWin);
        currWin = reg->getCurrentWin();
        currWinShift.clearQuick();
        currWinShift.addArray(currWin);
        
        shifter->putSamples(horseWin.data(), horseWin.size());
        shifter->receiveSamples(horseWinShift.data(),
                                horseWinShift.size());
        // e di frame corrente
        shifter->putSamples(currWin.data(), currWin.size());
        shifter->receiveSamples(currWinShift.data(),
                                currWinShift.size());
        
        // merge di horseWinShift e currWinShift (OLA, vettore eccedente)
        Window::OLA(horseWinShift, currWinShift,
                    reg->getWindow()->getOverlapSize(),
                    readyDataPreInt);
        
        // applicazione dell'interpolazione al vettore eccedente qui sopra
        interpolator->process(speedRatio, readyDataPreInt.data(),
                             readyData.data(), readyData.size());
        
        // restituzione del vettore eccedente interpolato:
        // !! hey listener I'm ready!
        // my end notification
        token->signal();
    }
}
