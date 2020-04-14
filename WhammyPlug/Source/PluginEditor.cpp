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

    knob.setColour(TextButton::buttonColourId, Colours::black);
    knob_container.setColour(TextButton::buttonColourId, Colours::darkred);

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
    pedal_level.setValue(0.0);
    pedal_level.addListener(this);

    // Slider that is used to choose the amount of pitch shift
    addAndMakeVisible(&pitch_choice);
    pitch_choice.setSliderStyle(Slider::Rotary);
    pitch_choice.setRange(-12, 12, 1.0);
    pitch_choice.setTextBoxStyle(Slider::NoTextBox, false, 90, 20);
    pitch_choice.setValue(12.0);
    pitch_choice.addListener(this);

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
    getParameters(0);
    buttonClicked(&(optionButtons[0]));
}


int WhammyPlugAudioProcessorEditor::getParameters(int button_index) {
    return OPTIONS[OPTION_KEYS[button_index]];
}


WhammyPlugAudioProcessorEditor::~WhammyPlugAudioProcessorEditor()
{
}

//==============================================================================
void WhammyPlugAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::darkred);
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
    pedal_level.setBounds(slider_container_area.removeFromTop(slider_container_area.getHeight()*29/30).reduced(slider_container_margin)); // -20

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
    
    for (int i = 0; i < N_OPTIONS; i++)
        optionButtons[i]
            .setBounds(boxes_container_area.removeFromTop(boxes_height)
            .reduced(boxes_container_margin));
}

void WhammyPlugAudioProcessorEditor::sliderValueChanged(Slider* s)
{
    if (s == &pedal_level) {
        processor.setPitchSemiTones(s->getValue());
    }
    else if (s == &pitch_choice) {
        processor.knob_value = s->getValue();

        if (s->getValue() > 0) {
            pedal_level.setRange(0, s->getValue());
            pedal_level.setValue(0.0);
            pedal_level.setNumDecimalPlacesToDisplay(2);
        }
        else if (s->getValue() < 0) {
            auto range = NormalisableRange<double>(s->getValue(), 0.0,
                [](auto rangeStart, auto rangeEnd, auto normalised)
                { return jmap(normalised, rangeEnd, rangeStart); },
                [](auto rangeStart, auto rangeEnd, auto value)
                { return jmap(value, rangeEnd, rangeStart, 0.0, 1.0); },
                [](auto rangeStart, auto rangeEnd, auto value)
                { return value; });
            pedal_level.setNormalisableRange(range);
            pedal_level.setNumDecimalPlacesToDisplay(2);
            pedal_level.setValue(0.0);
        }

        switch (processor.knob_value) {
        case 12:
            optionButtons[0].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 0)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 11:
            optionButtons[1].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 1)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 9:
            optionButtons[2].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 2)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 7:
            optionButtons[3].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 3)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 5:
            optionButtons[4].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 4)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 4:
            optionButtons[5].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 5)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 2:
            optionButtons[6].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 6)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;

        case -2:
            optionButtons[7].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 7)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -4:
            optionButtons[8].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 8)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -5:
            optionButtons[9].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 9)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -7:
            optionButtons[10].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 10)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -9:
            optionButtons[11].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 11)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -11:
            optionButtons[12].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 12)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -12:
            optionButtons[13].setColour(TextButton::buttonColourId, Colours::yellow);
            for (int i = 0; i < N_OPTIONS; i++) {
                if (i != 13)
                    optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -1:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 1:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 3:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -3:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 6:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -6:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 8:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -8:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case 10:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        case -10:
            for (int i = 0; i < N_OPTIONS; i++) {
                optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
            }
            break;
        }
    }
}

void WhammyPlugAudioProcessorEditor::buttonClicked(Button* sender)
{
    auto max_range = 0;
    pitch_choice.setValue(0.0);
    
    for (int j = 0; j < N_OPTIONS; j++)
        if (&(optionButtons[j]) != sender)
            optionButtons[j].setColour(TextButton::buttonColourId, Colours::maroon);
        else if (&(optionButtons[j]) == sender)
            max_range = getParameters(j); // seleziona il numero massimo di semitoni corrispondenti al tasto cliccato

    sender->setColour(TextButton::buttonColourId, Colours::yellow);

    if (max_range > 0) {
        pedal_level.setRange(0, max_range);
        pedal_level.setValue(0.0);
    }
    else if (max_range < 0) {
        auto range = NormalisableRange<double>(max_range, 0.0,
            [](auto rangeStart, auto rangeEnd, auto normalised)
            { return jmap(normalised, rangeEnd, rangeStart); },
            [](auto rangeStart, auto rangeEnd, auto value)
            { return jmap(value, rangeEnd, rangeStart, 0.0, 1.0); },
            [](auto rangeStart, auto rangeEnd, auto value)
            { return value; });
        pedal_level.setNormalisableRange(range);
        pedal_level.setValue(0.0);
    }
    pedal_level.setNumDecimalPlacesToDisplay(2); 
}