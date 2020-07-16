#include "CustomRegister.h"

CustomRegister::CustomRegister(Window* window)
    : SISOShiftRegister(window->getBlockSize(), window->getOverlapSize(), window->getHopSize())
{
    this->window = window;
}

CustomRegister::~CustomRegister() { }

Window* CustomRegister::getWindow()
{
    return this->window;
}
Array<float> CustomRegister::windowing(Array<float> which)
{
    Array<float> tmp;
    tmp.addArray(which);
    Window::applyWindow(tmp, window);
    return tmp;
}
Array<float> CustomRegister::getPreviousWin()
{
    return windowing(getPrevious());
}
Array<float> CustomRegister::getHorseWin()
{
    return windowing(getHorse());
}
Array<float> CustomRegister::getCurrentWin()
{
    return windowing(getCurrent());
}
