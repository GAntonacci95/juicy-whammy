#pragma once

#include <JuceHeader.h>

// TODO: Valutare attentamente l'uso dei riferimenti, ricreati o const?!
class Window
{
public:
	Window(int num);
	~Window();
    int getBlockSize();
    double getHopRate();
    void setHopRate(double rate);
    double getOverlapRate();
    int getHopSize();
    int getOverlapSize();
    float* getSamples();
    
    static void hamming(Window* outWindow);
    static void applyWindow(Array<float> data, Window* window);
    static Array<float> OLA(Array<float> first, Array<float> second, int overlapSize);

private:
    int blockSize;
    double hopRate;
    
    float* samples;
};
