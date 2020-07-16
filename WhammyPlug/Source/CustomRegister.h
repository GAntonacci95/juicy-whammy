#ifndef CustomMIMOShiftRegister_h
#define CustomMIMOShiftRegister_h

#include "SISOShiftRegister.h"
#include "Window.h"

class CustomMIMOShiftRegister
{
public:
    CustomMIMOShiftRegister(const float* inPtr, Window* window);
    ~CustomMIMOShiftRegister();
    void doShift();
    Window* getWindow();
    Array<float>* getPrevBlock();
    Array<float>* getWinPrevBlock();
    Array<float>* getWinHorseBlock();
    Array<float>* getCurrBlock();
    Array<float>* getWinCurrBlock();
    
private:
    const float* currRef;
    Window* window;
    SISOShiftRegister* blocks;
    SISOShiftRegister* shifts;
    
    // frame duplicati: cache cui si applica la finestra
    Array<float>* prevDup;
    Array<float>* horseDup;
    Array<float>* currDup;
    
    void updatePrevDup();
    void updateCurrDup();
    void updateHorseDup();
    void updateAllDups();
    void windowAllDups();
};

#endif /* CustomMIMOShiftRegister_h */
