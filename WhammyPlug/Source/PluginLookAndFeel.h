#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class PluginLookAndFeel : public LookAndFeel_V4
{
public:
	PluginLookAndFeel();
	virtual ~PluginLookAndFeel();
    
    //==============================================================================
    /* int to keep track of the position of the slider
       used in drawLinearSlider and PluginEditor.cpp initializations*/

    int high = 0;
    //==============================================================================

    virtual void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider);

    virtual void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginLookAndFeel)
};