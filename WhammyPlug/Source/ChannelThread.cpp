#include "ChannelThread.h"

ChannelThread::ChannelThread(const String& threadName, WaitableEvent* waitToken, uint sampleRate) : Thread(threadName)
{
    token = waitToken;
    shifter = new SoundTouch();
    isConfiged = false;
    
    // HI latency? -> combo (QUICK = true, AA = false)
    shifter->setSetting(SETTING_USE_QUICKSEEK, false);
    shifter->setSetting(SETTING_USE_AA_FILTER, true);
    shifter->setSampleRate(sampleRate);
    shifter->setChannels(1);

    shifter->setPitchSemiTones(0); // ADDED NOW
}

ChannelThread::~ChannelThread()
{
    shifter->clear();
    shifter->flush();
    delete shifter;
    delete readyData;
}

void ChannelThread::run()
{
    while(true)
    {
        // ! wait for the presence of new data
        this->wait(-1);
        // processing...
        shifter->putSamples(inPtr, blockSize);
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
}

float* ChannelThread::getReadyData()
{
    return readyData;
}
