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
    LilArray* getPreviousWin();
    LilArray* getHorseWin();
    LilArray* getCurrentWin();
    
private:
    Window* window;
    
    LilArray* prevWin;
    LilArray* horseWin;
    LilArray* currWin;
};

#endif /* CustomRegister_h */
