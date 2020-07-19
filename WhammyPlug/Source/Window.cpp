#include "Window.h"

Window::Window(int size, double hopRate)
{
    this->size = size;
    this->hopRate = hopRate;
    this->samples = new float[size];
}

Window::~Window() {}

int Window::getSize()
{
    return this->size;
}
double Window::getHopRate()
{
    return this->hopRate;
}
double Window::getOverlapRate()
{
    return 1 - getHopRate();
}
int Window::getHopSize()
{
    return (int)(getHopRate() * getSize());
}
int Window::getOverlapSize()
{
    return (int)(getOverlapRate() * getSize());
}
float* Window::getSamples()
{
    return this->samples;
}

// ------------------------------ UTILITA' STATICHE ------------------------------
Window* Window::hamming(int size)
{
    Window* outWindow = new Window(size, 0.5);
	double phase = 0;
	double delta = 2 * juce::MathConstants<float>::pi / (double)outWindow->getSize();

	for (int i = 0; i < outWindow->getSize(); ++i)
	{
		outWindow->getSamples()[i] = (float)(0.54 - 0.46 * cos(phase));
		phase += delta;
	}
    return outWindow;
}

void Window::applyWindow(float* data, Window* window)
{
	for (int i = 0; i < window->getSize(); ++i)
	{
        data[i] *= window->getSamples()[i];
	}
}
