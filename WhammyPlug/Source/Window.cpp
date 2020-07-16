#include "Window.h"

Window::Window(const String& name, int num)
{
    this->blockSize = num;
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
void Window::setHopRate(double rate)
{
    // check [0,1] ...
    this->hopRate = rate;
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

// ------------------------------ UTILIA' STATICHE ------------------------------
void Window::hamming(Window* outWindow)
{
    outWindow->setHopRate(0.5);
	double phase = 0;
	double delta = 2 * juce::MathConstants<float>::pi / (double)outWindow->getBlockSize();

	for (int i = 0; i < outWindow->getBlockSize(); ++i)
	{
		outWindow->getSamples()[i] = (float)(0.54 - 0.46 * cos(phase));
		phase += delta;
	}
}

void Window::applyWindow(Array<float> data, Window* window)
{
	for (int i = 0; i < data.size(); ++i)
	{
        data.getReference(i) *= window->getSamples()[i];
	}
}

void Window::OLA(Array<float> first, Array<float> second, int overlapSize, Array<float> output)
{
    output.clearQuick();
    output.resize(first.size() + second.size() - overlapSize);
    output.fill(0);
    
    for (int i = 0; i < output.size(); i++)
    {
        if (i < first.size() - overlapSize)
            output.add(first.getReference(i));
        else if (i >= first.size())
            output.add(second.getReference(i - first.size()));
        else
            output.add(first.getReference(i) +
                        second.getReference(i - first.size()));
    }
}
