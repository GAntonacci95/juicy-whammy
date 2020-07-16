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
    Array<float> getReadyData();

private:
    const float* currRef;
    WaitableEvent* token;
    SoundTouch* shifter;
    CustomRegister* reg;
    
    Array<float> horseWin;
    Array<float> horseWinShift;
    Array<float> currWin;
    Array<float> currWinShift;
    Array<float> readyDataPreInt;
    Array<float> readyData;
    bool isConfiged;
    
    LagrangeInterpolator* interpolator;
    const double speedRatio = 3.0;
};

#endif /* ChannelThread_h */
