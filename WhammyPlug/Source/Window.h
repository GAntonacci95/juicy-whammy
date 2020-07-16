#pragma once

#include <JuceHeader.h>
#include "LilArray.h"

// TODO: Valutare attentamente l'uso dei riferimenti, ricreati o const?!
class Window
{
public:
	~Window();
    int getBlockSize();
    double getHopRate();
    double getOverlapRate();
    int getHopSize();
    int getOverlapSize();
    float* getSamples();
    
    static Window* hamming(int size);
    static void applyWindow(LilArray* data, Window* window);
    static void OLA(LilArray* first, LilArray* second, int overlapSize, LilArray* output);

private:
    Window(int size, double hopRate);
    int blockSize;
    double hopRate;
    
    float* samples;
};
