#ifndef ChannelThread_h
#define ChannelThread_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "SoundTouch.h"

using namespace soundtouch;

class ChannelThread : public Thread
{
public:
    ChannelThread(const String& threadName, WaitableEvent* waitToken, uint sampleRate);
    ~ChannelThread();
    void run() override;
    void setPitchSemiTones(double currentPitch);
    bool isConfigured();
    void configure(const float* inptr, int n);
    float* getReadyData();
    
private:
    WaitableEvent* token;
    SoundTouch* shifter;
    bool isConfiged;
    const float* inPtr;
    int num;
    float* tmp;
};

#endif /* ChannelThread_h */
