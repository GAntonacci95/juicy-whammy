#include "CustomMIMOShiftRegister.h"

CustomMIMOShiftRegister::CustomMIMOShiftRegister(const float* inPtr, Window* window)
{
    this->currRef = inPtr;
    this->window = window;
    
    // inizializzo i (3 blocchi + 3 duplicati) tutti a 0
    
    blocks = new SISOShiftRegister(window->getBlockSize(), window->getOverlapSize(), window->getHopSize());
//    dups = new SISOShiftRegister(window);
//    shifts = new SISOShiftRegister(window->getBlockSize(), window->getOverlapSize(), window->getHopSize());
}

CustomMIMOShiftRegister::~CustomMIMOShiftRegister()
{
    delete blocks;
//    delete dups;
//    delete shifts;
}

void CustomMIMOShiftRegister::doShift()
{
    blocks->leftShift(currRef);
//    dups->doShift(currRef);
    // aggiorno AllDups e gli applico la finestra
    updateAllDups();
    windowAllDups();
}

void CustomMIMOShiftRegister::updatePrevDup()
{
    prevDup->clearQuick();
    prevDup->addArray(prevBlock, prevBlock->size());
}
void CustomMIMOShiftRegister::updateCurrDup()
{
    currDup->clearQuick();
    currDup->addArray(currBlock, currBlock->size());
}
void CustomMIMOShiftRegister::updateHorseDup()
{
    horseDup->clearQuick();
    horseDup->addArray(horseBlock, horseBlock->size());
}
void CustomMIMOShiftRegister::updateAllDups()
{
    updatePrevDup();
    updateCurrDup();
    updateHorseDup();
}
void CustomMIMOShiftRegister::windowAllDups()
{
    Window::applyWindow(prevDup, window);
    Window::applyWindow(horseDup, window);
    Window::applyWindow(currDup, window);
}
