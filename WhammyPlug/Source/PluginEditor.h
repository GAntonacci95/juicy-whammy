/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginLookAndFeel.h"

//==============================================================================

class WhammyPlugAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener,
                                        public Button::Listener
{
public:
    WhammyPlugAudioProcessorEditor (WhammyPlugAudioProcessor&);
    ~WhammyPlugAudioProcessorEditor();
    
    //==============================================================================
    //==============================================================================

    void paint(Graphics&) override;
    void resized() override;
    int getParameters(int button_index);

    void sliderValueChanged(Slider* slider) override;
    void buttonClicked(Button* sender) override;

private:
    WhammyPlugAudioProcessor& processor;

    PluginLookAndFeel customLookAndFeel;

    // Sliders to control the number of semitones
    Slider pedal_level;
    Slider pitch_choice;

    TextButton slider_container;
    TextButton knob_container;
    TextButton boxes_container;
    
    TextButton pedal;
    TextButton knob;
    TextButton boxes;

    // semitones
    static const int N_OPTIONS = 14;
    static const inline String OPTION_KEYS[] = {
        "+8th", "+7th", "+6th", "+5th", "+4th", "+3rd", "+2nd",
        "-2nd", "-3rd", "-4th", "-5th", "-6th", "-7th", "-8th"
    };

    static const inline int OPTION_VALUES[] = {
        12, 11, 9, 7, 5, 4, 2,
        -2, -4, -5, -7, -9, -11, -12
    };
    HashMap<String, int> OPTIONS;
    TextButton optionButtons[N_OPTIONS];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WhammyPlugAudioProcessorEditor)
};
