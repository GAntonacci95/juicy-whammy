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
    pedal.setColour(TextButton::buttonOnColourId, Colours::black);
    addAndMakeVisible(pedal);

    slider_container.setColour(TextButton::buttonColourId, Colours::darkred);
    slider_container.setColour(TextButton::buttonOnColourId, Colours::darkred);
    addAndMakeVisible(slider_container);

//    knob.setColour(TextButton::buttonColourId, Colours::black);
//    knob_container.setColour(TextButton::buttonColourId, Colours::darkred);

    boxes.setColour(TextButton::buttonColourId, Colours::black);
    boxes_container.setColour(TextButton::buttonColourId, Colours::darkred);

    // Slider that controls the amount of use of the pedal
    // max_pitch must be the maximum value selected using the rotary slider
    addAndMakeVisible(&pedal_level);
    pedal_level.setSliderStyle(Slider::LinearVertical);
    pedal_level.setRange(-12, 12);
    pedal_level.setTextBoxStyle(Slider::NoTextBox, false, 90, 20);
    pedal_level.setPopupDisplayEnabled(true, true, this);
    pedal_level.setTextValueSuffix(" semitones");
    pedal_level.setNumDecimalPlacesToDisplay(2);
    pedal_level.setValue(0);
    pedal_level.addListener(this);

    // Slider that is used to choose the amount of pitch shift
//    pitch_choice.setSliderStyle(Slider::Rotary);
//    pitch_choice.setRange(-12, 12, 1.0);
//    pitch_choice.setTextBoxStyle(Slider::NoTextBox, false, 90, 20);
//    pitch_choice.setValue(12.0);
//    pitch_choice.addListener(this);
//    // to change the maximum range of pitch shifting according to the chosen number of semitones
//
//    // TODO: HANDLER?!?!
//    pitch_choice.onValueChange = [this] {
//        if (pitch_choice.getValue() > 0) {
//            pedal_level.setRange(0, pitch_choice.getValue(), dontSendNotification);
//            pedal_level.setValue(0.0);
//        }
//        else if (pitch_choice.getValue() < 0) {
//            auto range = NormalisableRange<double>(pitch_choice.getValue(), 0.0,
//                [](auto rangeStart, auto rangeEnd, auto normalised)
//                { return jmap(normalised, rangeEnd, rangeStart); },
//                [](auto rangeStart, auto rangeEnd, auto value)
//                { return jmap(value, rangeEnd, rangeStart, 0.0, 1.0); },
//                [](auto rangeStart, auto rangeEnd, auto value)
//                { return value; });
//            pedal_level.setNormalisableRange(range);
//            pedal_level.setValue(0.0);
//        }
//    };
//    addAndMakeVisible(&pitch_choice);

    // Boxes for semitones
    for (int i = 0; i < N_OPTIONS; i++)
    {
        OPTIONS.set(OPTION_KEYS[i], OPTION_VALUES[i]);
        
        optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
        optionButtons[i].setColour(TextButton::textColourOffId, Colours::black);
        optionButtons[i].setButtonText(OPTION_KEYS[i]);
        
        optionButtons[i].addListener(this);
        addAndMakeVisible(optionButtons[i]);
    }
    buttonClicked(&(optionButtons[0]));
}

WhammyPlugAudioProcessorEditor::~WhammyPlugAudioProcessorEditor()
{
}

//==============================================================================
void WhammyPlugAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::darkred);

//    if (processor.knob_value == 2) {
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == 4) {
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == 5) {
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == 7) {
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == 9) {
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == 11) {
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == 12) {
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == -2) {
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == -4) {
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == -5) {
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == -7) {
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == -9) {
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == -11) {
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == -12) {
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::yellow);
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
//    else if (processor.knob_value == 1 || processor.knob_value == 3 || processor.knob_value == 6 || processor.knob_value == 8
//            || processor.knob_value == 10 || processor.knob_value == -1 || processor.knob_value == -3 || processor.knob_value == -6
//            || processor.knob_value == -8 || processor.knob_value == -10) {
//        // no button must be selected because these intervals are not considered
//        two_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_up.setColour(TextButton::buttonColourId, Colours::maroon);
//        two_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        four_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        five_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        seven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        nine_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        eleven_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//        twelve_semitones_down.setColour(TextButton::buttonColourId, Colours::maroon);
//    }
}

void WhammyPlugAudioProcessorEditor::resized()
{
    auto area = getLocalBounds(); 

    auto pedal_width = area.getWidth() / 2;
//    auto knob_width = area.getWidth() / 5;
    auto boxes_width = area.getWidth() - pedal_width; // - knob_width;

    auto pedal_area = area.removeFromLeft(pedal_width);
//    auto knob_area = area.removeFromLeft(knob_width);
    auto boxes_area = area.removeFromLeft(boxes_width);

    pedal.setBounds(pedal_area);
//    knob.setBounds(knob_area);
    boxes.setBounds(boxes_area);

    // pedal slider is inside the slider container area
    auto slider_container_area = pedal_area.removeFromLeft(pedal_area.getWidth());
    auto slider_container_margin = slider_container_area.getWidth() / 5;

    slider_container.setBounds(slider_container_area.reduced(slider_container_margin));
    pedal_level.setBounds(slider_container_area.removeFromTop(slider_container_area.getHeight()*29/30).reduced(slider_container_margin)); // -20

    // knob is inside the knob container area
//    auto knob_container_area = knob_area.removeFromLeft(knob_area.getWidth());
//    auto knob_container_margin = knob_container_area.getWidth() / 5;

//    knob_container.setBounds(knob_container_area.reduced(knob_container_margin));
//    pitch_choice
//        .setBounds(knob_container_area.removeFromTop(knob_container_area.getHeight())
//        .reduced(knob_container_margin));

    // semitones boxes are inside the boxes container area
    auto boxes_container_area = boxes_area.removeFromLeft(boxes_area.getWidth());
    auto boxes_container_margin = boxes_container_area.getWidth() / 30; // 25

    boxes_container.setBounds(boxes_container_area.removeFromTop(50));

    auto boxes_height = boxes_container_area.getHeight() / 15; // 22
    
//    for (int i = 0; i < N_OPTIONS; i++)
//        optionButtons[i]
    for(TextButton& button : optionButtons)
        button
            .setBounds(boxes_container_area.removeFromTop(boxes_height)
            .reduced(boxes_container_margin));
    
//    eleven_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    nine_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    seven_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    five_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    four_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    two_semitones_up.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//
//    two_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    four_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    five_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    seven_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    nine_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    eleven_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
//    twelve_semitones_down.setBounds(boxes_container_area.removeFromTop(boxes_height).reduced(boxes_container_margin));
}

void WhammyPlugAudioProcessorEditor::sliderValueChanged(Slider* s)
{
    if (s == &pedal_level) {
        processor.setPitchSemiTones(s->getValue());
    }
//    else if (s == &pitch_choice) {
//        processor.knob_value = s->getValue();
//    }
}

void WhammyPlugAudioProcessorEditor::buttonClicked(Button* sender)
{
//    pitch_choice.setValue(0.0); // TODO: rimuovere del tutto la knob?
    for(TextButton& button : optionButtons)
            button.setColour(TextButton::buttonColourId, Colours::maroon);
    sender->setColour(TextButton::buttonColourId, Colours::yellow);

    pedal_level.setRange(0, OPTIONS[sender->getButtonText()]);
    pedal_level.setValue(0.0);
    pedal_level.setNumDecimalPlacesToDisplay(2);
}
