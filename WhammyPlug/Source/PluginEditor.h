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
class WhammyPlugAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener,
                                        public LookAndFeel_V4
{
public:
    WhammyPlugAudioProcessorEditor (WhammyPlugAudioProcessor&);
    ~WhammyPlugAudioProcessorEditor();
    
    //==============================================================================
    LookAndFeel_V4 customLookAndFeel;
    //==============================================================================

    void paint(Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, 
        const float rotaryEndAngle, Slider& slider) override;

private:
    WhammyPlugAudioProcessor& processor;

    // Sliders to control the number of semitones
    Slider pedal_level;
    Slider pitch_choice;

    // provare a usare dei rettangoli come container!!!!!
    TextButton pedal;
    TextButton slider_container;
    TextButton knob;
    TextButton knob_container;
    TextButton boxes;
    TextButton boxes_container;

    // semitones up
    TextButton two_semitones_up;
    TextButton four_semitones_up;
    TextButton five_semitones_up;
    TextButton seven_semitones_up;
    TextButton nine_semitones_up;
    TextButton eleven_semitones_up;
    TextButton twelve_semitones_up;

    // semitones down
    TextButton two_semitones_down;
    TextButton four_semitones_down;
    TextButton five_semitones_down;
    TextButton seven_semitones_down;
    TextButton nine_semitones_down;
    TextButton eleven_semitones_down;
    TextButton twelve_semitones_down;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WhammyPlugAudioProcessorEditor)
};
