#ifndef LilArray_h
#define LilArray_h

#include <JuceHeader.h>

// GENERICI INFAMI in C++ =(
class LilArray
{
public:
    LilArray(int size);
    ~LilArray();
    int getSize();
    float* getData();
    void clear();
    void setDatum(int pos, float value);
    float getDatum(int pos);
    
    void setData(const float* inData, int start, int count);
    void setData(const float* inData);
    void setData(float* inData, int start, int count);
    void setData(float* inData);
    void setData(LilArray* inData, int start, int count);
    void setData(LilArray* inData);
    
private:
    int size;
    float* data;
};

#endif /* LilArray_h */
