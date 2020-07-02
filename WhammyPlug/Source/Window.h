#pragma once

#include <JuceHeader.h>
#include "juce_dsp/juce_dsp.h"
#include <cmath>

using namespace dsp;

class Window
{
public:
	Window();
	~Window();

	void hamming(float* window, size_t size);
	void applyWindow(float* data, float* window, size_t size);
};


