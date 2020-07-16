#include "Window.h"

Window::Window(int size, double hopRate)
{
    this->blockSize = size;
    this->hopRate = hopRate;
    this->samples = new float[blockSize];
}

Window::~Window() {}

int Window::getBlockSize()
{
    return this->blockSize;
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
    return (int)(getHopRate() * getBlockSize());
}
int Window::getOverlapSize()
{
    return (int)(getOverlapRate() * getBlockSize());
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
	double delta = 2 * juce::MathConstants<float>::pi / (double)outWindow->getBlockSize();

	for (int i = 0; i < outWindow->getBlockSize(); ++i)
	{
		outWindow->getSamples()[i] = (float)(0.54 - 0.46 * cos(phase));
		phase += delta;
	}
    return outWindow;
}

void Window::applyWindow(LilArray* data, Window* window)
{
	for (int i = 0; i < data->getSize(); ++i)
	{
        data->setDatum(i, data->getDatum(i) * window->getSamples()[i]);
	}
}

void Window::OLA(LilArray* first, LilArray* second, int overlapSize, LilArray* output)
{
    for (int i = 0; i < output->getSize(); i++)
    {
        if (i < first->getSize() - overlapSize)
            output[i] = first->getDatum(i);
        else if (i >= first->getSize())
            output[i] = second->getDatum(i - first->getSize());
        else
            output[i] = first->getDatum(i) +
                second->getDatum(i - first->getSize());
    }
}
