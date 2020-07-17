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
    
    horseWinShift = new LilArray(reg->getWindow()->getSize());
    currWinShift = new LilArray(reg->getWindow()->getSize());
    
    readyDataPreInt = new LilArray(reg->getWindow()->getHopSize() + reg->getWindow()->getSize());
    readyData = new LilArray(reg->getWindow()->getSize());
    
    isConfiged = true;
}

ChannelThread::~ChannelThread()
{
    shifter->clear();
    shifter->flush();
    delete shifter;
    delete reg;
    delete interpolator;
    
    horseWinShift->clear();
    currWinShift->clear();
    readyDataPreInt->clear();
    readyData->clear();
    delete horseWinShift;
    delete currWinShift;
    delete readyDataPreInt;
    delete readyData;
}

void ChannelThread::setPitchSemiTones(double currentPitch)
{
    shifter->setPitchSemiTones(currentPitch);
}

bool ChannelThread::isConfigured()
{
    return isConfiged;
}

LilArray* ChannelThread::getReadyData()
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
        LilArray* horseWin = reg->getHorseWin();
        horseWinShift->setData(horseWin);
        LilArray* currWin = reg->getCurrentWin();
        currWinShift->setData(currWin);
        
        shifter->putSamples(horseWin->getData(), horseWin->getSize());
        shifter->receiveSamples(horseWinShift->getData(), horseWinShift->getSize());
        // e di frame corrente
        shifter->putSamples(currWin->getData(), currWin->getSize());
        shifter->receiveSamples(currWinShift->getData(), currWinShift->getSize());
        
        // merge di horseWinShift e currWinShift (OLA, vettore eccedente)
        Window::OLA(horseWinShift, currWinShift,
                    reg->getWindow()->getOverlapSize(), readyDataPreInt);
        
        // applicazione dell'interpolazione al vettore eccedente qui sopra
        interpolator->process(((double)readyDataPreInt->getSize() / readyData->getSize()), // = 1.5 downsample rate
                              readyDataPreInt->getData(), readyData->getData(), readyData->getSize());
        
        // restituzione del vettore eccedente interpolato:
        // !! hey listener I'm ready!
        // my end notification
        token->signal();
    }
}
