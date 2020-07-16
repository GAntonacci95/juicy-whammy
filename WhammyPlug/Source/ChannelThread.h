#ifndef ChannelThread_h
#define ChannelThread_h

#include <JuceHeader.h>
#include <SoundTouch.h>
#include "Window.h"
#include "CustomRegister.h"

using namespace soundtouch;

// TODO: Valutare attentamente l'uso dei riferimenti, ricreati o const?!
class ChannelThread : public Thread
{
public:
    ChannelThread(const String& threadName, WaitableEvent* waitToken, uint sampleRate, Window* window);
    ~ChannelThread();
    void run() override;
    void setPitchSemiTones(double currentPitch);
    bool isConfigured();
    void configure(const float* inPtr);
    LilArray* getReadyData();

private:
    const float* currRef;
    WaitableEvent* token;
    SoundTouch* shifter;
    CustomRegister* reg;
    LagrangeInterpolator* interpolator;
    const double speedRatio = 3;
    
    LilArray* horseWinShift;
    LilArray* currWinShift;
    LilArray* readyDataPreInt;
    LilArray* readyData;
    bool isConfiged;
};

#endif /* ChannelThread_h */
