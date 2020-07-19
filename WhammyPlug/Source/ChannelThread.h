#ifndef ChannelThread_h
#define ChannelThread_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "SoundTouch.h"
#include "Window.h"

using namespace soundtouch;

class ChannelThread : public Thread
{
public:
    ChannelThread(const String& threadName, WaitableEvent* waitToken, uint sampleRate, Window* window);
    ~ChannelThread();
    void run() override;
    void setPitchSemiTones(double currentPitch);
    bool isConfigured();
    void configure(const float* inPtr);
    float* getReadyData();

private:
    WaitableEvent* token;
    SoundTouch* shifter;
    bool isConfiged;
    const float* inPtr;
    float* readyData;
    LagrangeInterpolator* interpolator;
    Window* window;
    const double speedRatio = 3;
    float* inPtrWindowed;
};

#endif /* ChannelThread_h */
