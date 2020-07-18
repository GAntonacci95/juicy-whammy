#ifndef ChannelThread_h
#define ChannelThread_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "SoundTouch.h"
#include "../modules/juce_dsp/juce_dsp.h"
#include "Window.h"

using namespace soundtouch;
using namespace dsp;

class ChannelThread : public Thread
{
public:
    ChannelThread(const String& threadName, WaitableEvent* waitToken, uint sampleRate, size_t samplePerBlock);
    ~ChannelThread();
    void run() override;
    void setPitchSemiTones(double currentPitch);
    bool isConfigured();
    void configure(const float* inptr, int num);
    float* getReadyData();

private:
    WaitableEvent* token;
    SoundTouch* shifter;
    bool isConfiged;
    const float* inPtr;
    int blockSize;
    float* readyData;
    LagrangeInterpolator* interpolator;
    Window* window;
    double speedRatio = 3;
    float* windowSamples;
    float* inPtrWindowed;
};

#endif /* ChannelThread_h */
