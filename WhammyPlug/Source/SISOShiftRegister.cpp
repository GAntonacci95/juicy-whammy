#include "CustomSISOShiftRegister.h"

CustomSISOShiftRegister::CustomSISOShiftRegister(Window* window)
{
    this->window = window;
    
    // inizializzo i 3 blocchi tutti a 0
    prevBlock = new Array<float>();
    prevBlock->resize(window->getBlockSize());
    prevBlock->fill(0);
    
    horseBlock = new Array<float>();
    horseBlock->resize(window->getOverlapSize() + window->getHopSize());
    horseBlock->fill(0);
    
    currBlock = new Array<float>();
    currBlock->addArray(prevBlock);
}

CustomSISOShiftRegister::~CustomSISOShiftRegister()
{
    prevBlock->clear();
    horseBlock->clear();
    currBlock->clear();
    delete prevBlock;
    delete horseBlock;
    delete currBlock;
}

Array<float>* CustomSISOShiftRegister::getPrevious()
{
    return this->prevBlock;
}
Array<float>* CustomSISOShiftRegister::getWin(Array<float>* which)
{
    Array<float>* tmp = new Array<float>();
    tmp->addArray(which);
    Window::applyWindow(tmp, window);
    return tmp;
}
Array<float>* CustomSISOShiftRegister::getWinPrevious()
{
    return getWin(prevBlock);
}
Array<float>* CustomSISOShiftRegister::getWinHorse()
{
    return getWin(horseBlock);
}
Array<float>* CustomSISOShiftRegister::getCurrent()
{
    return this->currBlock;
}
Array<float>* CustomSISOShiftRegister::getWinCurrent()
{
    return getWin(currBlock);
}

void CustomSISOShiftRegister::leftShift(const float* inPtr)
{
    // copio currBlock in prevBlock
    updatePrevBlock();
    // copio currRef in currBlock
    updateCurrBlock(inPtr);
    // aggiorno horseBlock
    updateHorseBlock();
}

void CustomSISOShiftRegister::updatePrevBlock()
{
    prevBlock->clearQuick();
    prevBlock->addArray(currBlock, currBlock->size());
}

void CustomSISOShiftRegister::updateCurrBlock(const float* inPtr)
{
    currBlock->addArray(inPtr, currBlock->size());
    currBlock->removeRange(0, currBlock->size() / 2);
}

void CustomSISOShiftRegister::updateHorseBlock()
{
    // TODO: CHECK - clearQuick (in caso correggere anche altrove NEI FILEs) e correttezza riferimenti
    horseBlock->clearQuick();
    horseBlock->addArray(&(prevBlock[window->getHopSize()]), window->getOverlapSize());
    horseBlock->addArray(currBlock, window->getHopSize());
}
