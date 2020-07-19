#include "ChannelThread.h"

ChannelThread::ChannelThread(const String& threadName, WaitableEvent* waitToken, uint sampleRate, Window* window) 
    : Thread(threadName)
{

    this->token = waitToken;
    this->window = window;
    this->shifter = new SoundTouch();
    this->readyData = new float[window->getSize()];
    this->inPtrWindowed = new float[window->getSize()];
    this->interpolator = new LagrangeInterpolator();
    this->isConfiged = false;
    
    shifter->setSetting(SETTING_USE_QUICKSEEK, false);
    shifter->setSetting(SETTING_USE_AA_FILTER, true);
    /*shifter->setSetting(SETTING_SEQUENCE_MS, 100);
    shifter->setSetting(SETTING_SEEKWINDOW_MS, 50);
    shifter->setSetting(SETTING_OVERLAP_MS, 50);*/
    shifter->setSampleRate(sampleRate);
    shifter->setChannels(1);

    shifter->setPitchSemiTones(0);
}

ChannelThread::~ChannelThread()
{
    shifter->clear();
    shifter->flush();
    // pulire window all'esterno
    delete shifter;
    delete readyData;
    delete inPtrWindowed;
    delete interpolator;
}

void ChannelThread::run()
{
    while(true)
    {
        // ! wait for the presence of new data
        this->wait(-1);
        // processing...
        shifter->putSamples(inPtr, window->getSize());
        // windowing with Hamming window
        FloatVectorOperations::copy(inPtrWindowed, inPtr, window->getSize());
        Window::applyWindow(inPtrWindowed, window);
        // Lagrange Interpolation with windowed signal
        interpolator->LagrangeInterpolator::process(speedRatio, inPtrWindowed, readyData, speedRatio*window->getSize()); // 512
        shifter->receiveSamples(readyData, window->getSize());
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

void ChannelThread::configure(const float* inptr)
{
    this->inPtr = inptr;
    this->isConfiged = true;
}

float* ChannelThread::getReadyData()
{
    return readyData;
}
