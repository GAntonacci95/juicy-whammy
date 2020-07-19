#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Window
{
public:
	~Window();
    int getSize();
    double getHopRate();
    double getOverlapRate();
    int getHopSize();
    int getOverlapSize();
    float* getSamples();
    
    static Window* hamming(int size);
    static void applyWindow(float* data, Window* window);

private:
    Window(int size, double hopRate);
    int size;
    double hopRate;
    
    float* samples;
};
