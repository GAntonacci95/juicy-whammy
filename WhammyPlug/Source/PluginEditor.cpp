/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WhammyPlugAudioProcessorEditor::WhammyPlugAudioProcessorEditor (WhammyPlugAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (600, 600);

    LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);

    // displaying pedal, knob and boxes
    pedal.setColour(TextButton::buttonColourId, Colours::black);
    addAndMakeVisible(pedal);

    slider_container.setColour(TextButton::buttonColourId, Colours::darkred);
    addAndMakeVisible(slider_container);

    knob.setColour(TextButton::buttonColourId, Colours::black);
    knob_container.setColour(TextButton::buttonColourId, Colours::darkred);

    boxes.setColour(TextButton::buttonColourId, Colours::black);
    boxes_container.setColour(TextButton::buttonColourId, Colours::darkred);

    // Slider that controls the amount of use of the pedal
    // max_pitch must be the maximum value selected using the rotary slider
    addAndMakeVisible(&pedal_level);
    pedal_level.setSliderStyle(Slider::LinearVertical);
    pedal_level.setRange(-12, 12); // initialization value
    pedal_level.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    pedal_level.setPopupDisplayEnabled(true, true, this);
    pedal_level.setTextValueSuffix(" semitones");
    pedal_level.setValue(0);
    pedal_level.addListener(this);

    // Slider that is used to choose the amount of pitch shift
    addAndMakeVisible(&pitch_choice);
    pitch_choice.setSliderStyle(Slider::Rotary);
    pitch_choice.setRange(-12, 12, 1.0);
    pitch_choice.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    pitch_choice.setValue(0.0);
    pitch_choice.addListener(this);
//    pitch_choice.setLookAndFeel(&customLookAndFeel);
    // to change the maximum range of pitch shifting according to the chosen number of semitones
    pitch_choice.onValueChange = [this] {
        if (pitch_choice.getValue() > 0) {
            pedal_level.setRange(0, pitch_choice.getValue(), dontSendNotification);
            pedal_level.setValue(0.0);
        }
        else if (pitch_choice.getValue() < 0) {
            pedal_level.setRange(pitch_choice.getValue(), 0, dontSendNotification);
            pedal_level.setValue(0.0);
        }
    };

    // Boxes for semitones
    two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
    two_semitones_up.setButtonText("+2nd");
    two_semitones_up.setColour(TextButton::textColourOffId, Colours::black);
    two_semitones_up.onClick = [this] {
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(0, 2);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(two_semitones_up);

    four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
    four_semitones_up.setButtonText("+3rd");
    four_semitones_up.setColour(TextButton::textColourOffId, Colours::black);
    four_semitones_up.onClick = [this] {
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(0, 4);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(four_semitones_up);

    five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
    five_semitones_up.setButtonText("+4th");
    five_semitones_up.setColour(TextButton::textColourOffId, Colours::black);
    five_semitones_up.onClick = [this] {
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(0, 5);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(five_semitones_up);

    seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
    seven_semitones_up.setButtonText("+5th");
    seven_semitones_up.setColour(TextButton::textColourOffId, Colours::black);
    seven_semitones_up.onClick = [this] {
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(0, 7);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(seven_semitones_up);

    nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
    nine_semitones_up.setButtonText("+6th");
    nine_semitones_up.setColour(TextButton::textColourOffId, Colours::black);
    nine_semitones_up.onClick = [this] {
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(0, 9);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(nine_semitones_up);

    eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
    eleven_semitones_up.setButtonText("+7th");
    eleven_semitones_up.setColour(TextButton::textColourOffId, Colours::black);
    eleven_semitones_up.onClick = [this] {
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(0, 11);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(eleven_semitones_up);

    twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
    twelve_semitones_up.setButtonText("+octave");
    twelve_semitones_up.setColour(TextButton::textColourOffId, Colours::black);
    twelve_semitones_up.onClick = [this] {
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(0, 12);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(twelve_semitones_up);

    two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    two_semitones_down.setButtonText("-2nd");
    two_semitones_down.setColour(TextButton::textColourOffId, Colours::black);
    two_semitones_down.onClick = [this] {
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(-2, 0);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(two_semitones_down);

    four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    four_semitones_down.setButtonText("-3rd");
    four_semitones_down.setColour(TextButton::textColourOffId, Colours::black);
    four_semitones_down.onClick = [this] {
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(-4, 0);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(four_semitones_down);

    five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    five_semitones_down.setButtonText("-4th");
    five_semitones_down.setColour(TextButton::textColourOffId, Colours::black);
    five_semitones_down.onClick = [this] {
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(-5, 0);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(five_semitones_down);

    seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    seven_semitones_down.setButtonText("-5th");
    seven_semitones_down.setColour(TextButton::textColourOffId, Colours::black);
    seven_semitones_down.onClick = [this] {
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(-7, 0);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(seven_semitones_down);

    nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    nine_semitones_down.setButtonText("-6th");
    nine_semitones_down.setColour(TextButton::textColourOffId, Colours::black);
    nine_semitones_down.onClick = [this] {
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        pedal_level.setRange(-9, 0);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(nine_semitones_down);

    eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    eleven_semitones_down.setButtonText("-7th");
    eleven_semitones_down.setColour(TextButton::textColourOffId, Colours::black);
    eleven_semitones_down.onClick = [this] {
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);

        pedal_level.setRange(-11, 0);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(eleven_semitones_down);

    twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    twelve_semitones_down.setButtonText("-octave");
    twelve_semitones_down.setColour(TextButton::textColourOffId, Colours::black);
    twelve_semitones_down.onClick = [this] {
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        // SETTARE TUTTI GLI ALTRI AL COLORE ORIGINALE
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);

        pedal_level.setRange(-12, 0);
        pedal_level.setValue(0.0);
    };
    addAndMakeVisible(twelve_semitones_down);
}

WhammyPlugAudioProcessorEditor::~WhammyPlugAudioProcessorEditor()
{
}

//==============================================================================
void WhammyPlugAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::darkred);

    if (processor.knob_value == 2) {
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == 4) {
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == 5) {
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == 7) {
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == 9) {
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == 11) {
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == 12) {
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    } 
    else if (processor.knob_value == -2) {
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == -4) {
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == -5) {
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == -7) {
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == -9) {
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == -11) {
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    else if (processor.knob_value == -12) {
        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
    }
    /*
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::horizontallyCentred, 1);
    */
}

void WhammyPlugAudioProcessorEditor::resized()
{
    auto area = getLocalBounds(); 

    auto pedal_width = area.getWidth() / 2;
    auto knob_width = area.getWidth() / 5;
    auto boxes_width = area.getWidth() - pedal_width - knob_width;

    auto pedal_area = area.removeFromLeft(pedal_width);
    auto knob_area = area.removeFromLeft(knob_width);
    auto boxes_area = area.removeFromLeft(boxes_width);

    pedal.setBounds(pedal_area);
    knob.setBounds(knob_area);
    boxes.setBounds(boxes_area);

    // pedal slider is inside the slider container area
    auto slider_container_area = pedal_area.removeFromLeft(pedal_area.getWidth());
    auto slider_container_margin = slider_container_area.getWidth() / 5;

    slider_container.setBounds(slider_container_area.reduced(slider_container_margin));
    pedal_level.setBounds(slider_container_area.removeFromTop(slider_container_area.getHeight()).reduced(slider_container_margin));

    // knob is inside the knob container area
    auto knob_container_area = knob_area.removeFromLeft(knob_area.getWidth());
    auto knob_container_margin = knob_container_area.getWidth() / 5;

    knob_container.setBounds(knob_container_area.reduced(knob_container_margin));
    pitch_choice.setBounds(knob_container_area.removeFromTop(knob_container_area.getHeight()).reduced(knob_container_margin));

    // semitones boxes are inside the boxes container area
    auto boxes_container_area = boxes_area.removeFromLeft(boxes_area.getWidth());
    auto boxes_container_margin = boxes_container_area.getWidth() / 30; // 25

    boxes_container.setBounds(boxes_container_area.removeFromTop(50));

    auto boxes_height = boxes_container_area.getHeight() / 15; // 22
    // auto boxes_margin = 3;

    twelve_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    eleven_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    nine_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    seven_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    five_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    four_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    two_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));

    two_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    four_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    five_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    seven_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    nine_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    eleven_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
    twelve_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
}


void WhammyPlugAudioProcessorEditor::sliderValueChanged(Slider* s)
{
    if (s == &pedal_level) {
        processor.pitch_value = s->getValue();
    }
    else if (s == &pitch_choice) {
        processor.knob_value = s->getValue();
    }
}

void WhammyPlugAudioProcessorEditor::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto radius = 30.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // fill in the colour of the knob
    Colour color = Colour(185, 0, 0);
    g.setColour(color.withAlpha(0.2f));
    g.fillEllipse(rx, ry, rw, rw);

    // outline
    g.setColour(Colours::black);
    g.drawEllipse(rx, ry, rw, rw, 1.0f);

    // Pointer
    Path p;
    auto pointerLength = radius;
    auto pointerThickness = 2.0f;
    Rectangle<float> r(-pointerThickness * 0.5f, -radius - 2.0f, pointerThickness, pointerLength);
    p.addRectangle(r);
    p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
    Rectangle<float> rect(rx, ry, rw, rw);
    p.addPieSegment(rect, rotaryStartAngle, angle, 0.95f);

    g.setColour(Colours::darkred.withAlpha(1.0f));
    g.fillPath(p);
}
