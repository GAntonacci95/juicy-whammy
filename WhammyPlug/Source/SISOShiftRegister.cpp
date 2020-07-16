#include "SISOShiftRegister.h"

SISOShiftRegister::SISOShiftRegister(int blockSize, int hopSize, int overlapSize)
{
    this->blockSize = blockSize;
    this->hopSize = hopSize;
    this->overlapSize = overlapSize;
    
    this->prevBlock = new LilArray(blockSize);
    this->horseBlock = new LilArray(blockSize);
    this->currBlock = new LilArray(blockSize);
}

SISOShiftRegister::~SISOShiftRegister()
{
    prevBlock->clear();
    horseBlock->clear();
    currBlock->clear();
    delete prevBlock;
    delete horseBlock;
    delete currBlock;
}

LilArray* SISOShiftRegister::getPrevious()
{
    return this->prevBlock;
}
LilArray* SISOShiftRegister::getHorse()
{
    return this->horseBlock;
}
LilArray* SISOShiftRegister::getCurrent()
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
void SISOShiftRegister::leftShift(float* inPtr)
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
    prevBlock->setData(currBlock);
}

void SISOShiftRegister::updateCurrBlock(const float* inPtr)
{
    currBlock->setData(inPtr);
}
void SISOShiftRegister::updateCurrBlock(float* inPtr)
{
    currBlock->setData(inPtr);
}

void SISOShiftRegister::updateHorseBlock()
{
    horseBlock->setData(prevBlock, hopSize, overlapSize);
    horseBlock->setData(currBlock, 0, hopSize);
}
