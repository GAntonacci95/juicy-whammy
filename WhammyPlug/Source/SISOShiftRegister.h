#ifndef CustomSISOShiftRegister_hpp
#define CustomSISOShiftRegister_hpp

#include <JuceHeader.h>
#include "Window.h"

class CustomSISOShiftRegister
{
public:
    CustomSISOShiftRegister(Window* window);
    ~CustomSISOShiftRegister();
    Array<float>* getPrevious();
    Array<float>* getWinPrevious();
    Array<float>* getWinHorse();
    Array<float>* getCurrent();
    Array<float>* getWinCurrent();
    void leftShift(const float* inPtr);
    
private:
    Window* window;
    
    Array<float>* prevBlock;
    // horse cache a cavallo
    Array<float>* horseBlock;
    Array<float>* currBlock;
    
    Array<float>* getWin(Array<float>* which);
    void updatePrevBlock();
    void updateCurrBlock(const float* inPtr);
    void updateHorseBlock();
};

#endif /* CustomSISOShiftRegister_hpp */
