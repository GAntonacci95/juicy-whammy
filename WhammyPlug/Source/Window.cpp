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
            output->setDatum(i, first->getDatum(i));
        else if (i >= first->getSize())
            output->setDatum(i, second->getDatum(i - first->getSize()));
        else
            output->setDatum(i, first->getDatum(i) +
                second->getDatum(i - first->getSize()));
    }
}
