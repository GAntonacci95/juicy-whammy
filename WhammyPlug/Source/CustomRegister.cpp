#include "CustomRegister.h"

CustomRegister::CustomRegister(Window* window)
    : SISOShiftRegister(window->getSize(), window->getOverlapSize(), window->getHopSize())
{
    this->window = window;
    this->prevWin = new LilArray(window->getSize());
    this->horseWin = new LilArray(window->getSize());
    this->currWin = new LilArray(window->getSize());
}

CustomRegister::~CustomRegister() { }

Window* CustomRegister::getWindow()
{
    return this->window;
}

LilArray* CustomRegister::getPreviousWin()
{
    prevWin->setData(getPrevious());
    Window::applyWindow(prevWin, window);
    return this->prevWin;
}
LilArray* CustomRegister::getHorseWin()
{
    horseWin->setData(getHorse());
    Window::applyWindow(horseWin, window);
    return this->horseWin;
}
LilArray* CustomRegister::getCurrentWin()
{
    currWin->setData(getCurrent());
    Window::applyWindow(currWin, window);
    return this->currWin;
}
