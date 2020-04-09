#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class PluginLookAndFeel : public LookAndFeel_V4
{
public:
	PluginLookAndFeel();
    ~PluginLookAndFeel();
    
    //==============================================================================
    //==============================================================================

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override;

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional,
        float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginLookAndFeel)
};
