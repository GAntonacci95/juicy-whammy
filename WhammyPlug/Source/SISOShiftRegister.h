#ifndef SISOShiftRegister_h
#define SISOShiftRegister_h

#include <JuceHeader.h>
#include "LilArray.h"

// TODO: Valutare attentamente l'uso dei riferimenti, ricreati o const?!
class SISOShiftRegister
{
public:
    SISOShiftRegister(int blockSize, int hopSize, int overlapSize);
    ~SISOShiftRegister();
    LilArray* getPrevious();
    LilArray* getHorse();
    LilArray* getCurrent();
    void leftShift(const float* inPtr);
    void leftShift(float* inPtr);
    
private:
    int blockSize;
    int hopSize;
    int overlapSize;
    
    LilArray* prevBlock;
    // horse cache a cavallo
    LilArray* horseBlock;
    LilArray* currBlock;
    
    void updatePrevBlock();
    void updateCurrBlock(const float* inPtr);
    void updateCurrBlock(float* inPtr);
    void updateHorseBlock();
};

#endif /* SISOShiftRegister_h */
