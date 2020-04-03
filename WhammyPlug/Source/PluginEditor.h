/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WhammyPlugAudioProcessorEditor  : public AudioProcessorEditor/*,
                                        private Slider::Listener,
                                        private LookAndFeel_V4*/
{
public:
    WhammyPlugAudioProcessorEditor (WhammyPlugAudioProcessor&);
    ~WhammyPlugAudioProcessorEditor();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;

private:
    /*
    void sliderValueChanged(Slider* slider) override;
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override;
    */
    WhammyPlugAudioProcessor& processor;

    Slider* pedal_level;
    Slider* pitch_choice;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WhammyPlugAudioProcessorEditor)
};
