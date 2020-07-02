#include "Window.h"

Window::Window() {}

Window::~Window() {}

void Window::hamming(float* window, size_t size)
{
	int i;
	double phase = 0;
	double delta;

	delta = 2 * juce::MathConstants<float>::pi / (double)size;

	for (i = 0; i < size; ++i)
	{
		window[i] = (float)(0.54 - 0.46 * cos(phase));
		phase += delta;
	}
}

void Window::applyWindow(float* data, float* window, size_t size)
{
	int i;

	for (i = 0; i < size; ++i)
	{
		data[i] *= window[i];
	}
}

