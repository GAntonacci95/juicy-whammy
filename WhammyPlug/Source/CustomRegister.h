#ifndef CustomRegister_h
#define CustomRegister_h

#include "SISOShiftRegister.h"
#include "Window.h"

// TODO: Valutare attentamente l'uso dei riferimenti, ricreati o const?!
class CustomRegister : public SISOShiftRegister
{
public:
    CustomRegister(Window* window);
    ~CustomRegister();
    Window* getWindow();
    Array<float> getPreviousWin();
    Array<float> getHorseWin();
    Array<float> getCurrentWin();
    
private:
    Window* window;
    
    Array<float> windowing(Array<float> which);

//    // frame duplicati: cache cui si applica la finestra
//    Array<float>* prevDup;
//    Array<float>* horseDup;
//    Array<float>* currDup;
//
//    void updatePrevDup();
//    void updateCurrDup();
//    void updateHorseDup();
//    void updateAllDups();
//    void windowAllDups();
};

#endif /* CustomRegister_h */
