#include "ChannelThread.h"

ChannelThread::ChannelThread(const String& threadName, WaitableEvent* waitToken, uint sampleRate, size_t samplePerBlock) 
    : Thread(threadName)
{

    token = waitToken;
    shifter = new SoundTouch();
    isConfiged = false;
    
    shifter->setSetting(SETTING_USE_QUICKSEEK, false);
    shifter->setSetting(SETTING_USE_AA_FILTER, true);
    /*shifter->setSetting(SETTING_SEQUENCE_MS, 100);
    shifter->setSetting(SETTING_SEEKWINDOW_MS, 50);
    shifter->setSetting(SETTING_OVERLAP_MS, 50);*/
    shifter->setSampleRate(sampleRate);
    shifter->setChannels(1);

    shifter->setPitchSemiTones(0);

    window = new Window();
    interpolator = new LagrangeInterpolator();
}

ChannelThread::~ChannelThread()
{
    shifter->clear();
    shifter->flush();
    delete shifter;
    delete readyData;
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
        // windowing with Hamming window
        memcpy(inPtrWindowed, inPtr, sizeof(float)*blockSize);
        window->applyWindow(inPtrWindowed, windowSamples, blockSize);
        // Lagrange Interpolation with windowed signal
        interpolator->LagrangeInterpolator::process(speedRatio, inPtrWindowed, readyData, speedRatio*blockSize); // 512
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
    windowSamples = new float[blockSize];
    window->hamming(windowSamples, blockSize);
    inPtrWindowed = new float[blockSize];
}

float* ChannelThread::getReadyData()
{
    return readyData;
}
