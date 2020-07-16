#ifndef SISOShiftRegister_h
#define SISOShiftRegister_h

#include <JuceHeader.h>
#include "Window.h"

// TODO: Valutare attentamente l'uso dei riferimenti, ricreati o const?!
class SISOShiftRegister
{
public:
    SISOShiftRegister(int blockSize, int overlapSize = 0, int hopSize = 0);
    ~SISOShiftRegister();
    Array<float> getPrevious();
    Array<float> getHorse();
    Array<float> getCurrent();
    void leftShift(const float* inPtr);
    
private:
    int blockSize;
    int overlapSize;
    int hopSize;
    
    Array<float> prevBlock;
    // horse cache a cavallo
    Array<float> horseBlock;
    Array<float> currBlock;
    
    void updatePrevBlock();
    void updateCurrBlock(const float* inPtr);
    void updateHorseBlock();
};

#endif /* SISOShiftRegister_h */
