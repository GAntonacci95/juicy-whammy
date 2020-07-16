#include "LilArray.h"

LilArray::LilArray(int size)
{
    this->size = size;
    this->data = new float[size];
    this->clear();
}

LilArray::~LilArray()
{
    delete data;
}

int LilArray::getSize()
{
    return this->size;
}

void LilArray::clear()
{
    FloatVectorOperations::fill(this->data, 0, this->size);
}

float LilArray::getDatum(int pos)
{
    return data[pos];
}

void LilArray::setDatum(int pos, float value)
{
    data[pos] = value;
}

float* LilArray::getData()
{
    return this->data;
}

void LilArray::setData(const float* inData, int start, int count)
{
    for(int i = start; i < start + count; i++)
    {
        setDatum(i, inData[i]);
    }
}
void LilArray::setData(const float* inData)
{
    this->setData(inData, 0, getSize());
}

void LilArray::setData(float* inData, int start, int count)
{
    for(int i = start; i < start + count; i++)
    {
        setDatum(i, inData[i]);
    }
}
void LilArray::setData(float* inData)
{
    this->setData(inData, 0, getSize());
}

void LilArray::setData(LilArray* inData, int start, int count)
{
    this->setData(inData->getData(), start, count);
}
void LilArray::setData(LilArray* inData)
{
    this->setData(inData->getData());
}
