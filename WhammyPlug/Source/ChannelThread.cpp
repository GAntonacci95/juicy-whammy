#include "ChannelThread.h"

ChannelThread::ChannelThread(const String& threadName, WaitableEvent* waitToken, uint sampleRate, size_t samplePerBlock) 
    : Thread(threadName)
{

    token = waitToken;
    shifter = new SoundTouch();
    isConfiged = false;
    
    // HI latency? -> combo (QUICK = true, AA = false)
    shifter->setSetting(SETTING_USE_QUICKSEEK, false);
    shifter->setSetting(SETTING_USE_AA_FILTER, true);
    shifter->setSampleRate(sampleRate);
    shifter->setChannels(1);

    shifter->setPitchSemiTones(0);

    window = new Window();
    /*windowSamples = new float[samplePerBlock];
    window->hamming(windowSamples, samplePerBlock);*/
}

ChannelThread::~ChannelThread()
{
    shifter->clear();
    shifter->flush();
    delete shifter;
    delete readyData;
    ///////////////////////////////////////////////
    delete inPtrWindowed;
    delete windowSamples;
}

void ChannelThread::run()
{
    while(true)
    {
        // ! wait for the presence of new data
        this->wait(-1);
        // processing...
        shifter->putSamples(inPtr, blockSize);
        // WINDOWING DI INPTR CON FINESTRA DI HAMMING
        memcpy(inPtrWindowed, inPtr, sizeof(float)*blockSize); // copio inPtr in inPtrWindowed
        window->applyWindow(inPtrWindowed, windowSamples, blockSize);
        // LAGRANGE INTERPOLATION SU SEGNALE A CUI E APPLICATA LA WINDOW
        interpolator.LagrangeInterpolator::process(speedRatio, inPtrWindowed, readyData, speedRatio*blockSize); // 512
        shifter->receiveSamples(readyData, blockSize);
        // !! hey listener I'm ready!
        // my end notification
        token->signal();
    }
}

void ChannelThread::setPitchSemiTones(double currentPitch)
{
    shifter->setPitchSemiTones(currentPitch);
}

bool ChannelThread::isConfigured()
{
    return isConfiged;
}

void ChannelThread::configure(const float* inptr, int num)
{
    inPtr = inptr;
    blockSize = num;
    readyData = new float[blockSize];
    isConfiged = true;
    ////////////////////////////////////////////////////////////////
    windowSamples = new float[blockSize];
    window->hamming(windowSamples, blockSize);
    inPtrWindowed = new float[blockSize];
}

float* ChannelThread::getReadyData()
{
    return readyData;
}
