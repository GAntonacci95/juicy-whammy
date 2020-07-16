#include "SISOShiftRegister.h"

SISOShiftRegister::SISOShiftRegister(int blockSize, int overlapSize, int hopSize)
{
    this->blockSize = blockSize;
    this->overlapSize = overlapSize;
    this->hopSize = hopSize;
    
    // inizializzo i 3 blocchi tutti a 0
    prevBlock.resize(blockSize);
    prevBlock.fill(0);
    
    horseBlock.resize(overlapSize + hopSize);
    horseBlock.fill(0);
    
    currBlock.addArray(prevBlock);
}

SISOShiftRegister::~SISOShiftRegister()
{
    prevBlock.clear();
    horseBlock.clear();
    currBlock.clear();
    delete &prevBlock;
    delete &horseBlock;
    delete &currBlock;
}

Array<float> SISOShiftRegister::getPrevious()
{
    return this->prevBlock;
}
Array<float> SISOShiftRegister::getHorse()
{
    return this->horseBlock;
}
Array<float> SISOShiftRegister::getCurrent()
{
    return this->currBlock;
}

void SISOShiftRegister::leftShift(const float* inPtr)
{
    // copio currBlock in prevBlock
    updatePrevBlock();
    // copio currRef in currBlock
    updateCurrBlock(inPtr);
    // aggiorno horseBlock
    updateHorseBlock();
}

void SISOShiftRegister::updatePrevBlock()
{
    prevBlock.clearQuick();
    prevBlock.addArray(currBlock, currBlock.size());
}

void SISOShiftRegister::updateCurrBlock(const float* inPtr)
{
    currBlock.addArray(inPtr, currBlock.size());
    currBlock.removeRange(0, currBlock.size() / 2);
}

void SISOShiftRegister::updateHorseBlock()
{
    // TODO: CHECK - clearQuick (in caso correggere anche altrove NEI FILEs) e correttezza riferimenti
    horseBlock.clearQuick();
    // TODO: CORREGGERE QUI SOTTOOOOOOOOOOOOOOOOOOOOOOO
//    horseBlock.addArray(&(prevBlock[hopSize]), overlapSize);
    horseBlock.addArray(currBlock, hopSize);
}
