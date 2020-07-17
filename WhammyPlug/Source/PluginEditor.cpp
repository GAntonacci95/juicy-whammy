/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

//==============================================================================
WhammyPlugAudioProcessorEditor::WhammyPlugAudioProcessorEditor(WhammyPlugAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    setSize(600, 600);
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
    pedal_level.setRange(0, 12, 0.01);
    pedal_level.setTextBoxStyle(Slider::NoTextBox, false, 90, 20);
    pedal_level.setPopupDisplayEnabled(true, true, this);
    pedal_level.setTextValueSuffix(" semitones");
    pedal_level.setValue(processor.currPitch, juce::dontSendNotification);
    pedal_level.onValueChange = [this]()
    { 
        pedalValueChanged(&pedal_level);
        processor.targetPitch = pedal_level.getValue();
    };

    // Slider that is used to choose the amount of pitch shift
    addAndMakeVisible(&pitch_choice);
    pitch_choice.setSliderStyle(Slider::Rotary);
    pitch_choice.setRange(0, N_OPTIONS - 1, 1.0);
    // default for triggering the initial update via optionButtons[0].triggerClick();
    // @ the end of the function
    pitch_choice.setValue(N_OPTIONS - 1);
    pitch_choice.setTextBoxStyle(Slider::NoTextBox, false, 90, 20);
    pitch_choice.onValueChange = [this](){ knobValueChanged(&pitch_choice); };

    // Boxes for semitones
    for (int i = 0; i < N_OPTIONS; i++)
    {
        OPTIONS.set(OPTION_KEYS[i], OPTION_VALUES[i]);
        
        addAndMakeVisible(optionButtons[i]);
        optionButtons[i].setColour(TextButton::buttonColourId, Colours::maroon);
        optionButtons[i].setColour(TextButton::textColourOffId, Colours::black);
        optionButtons[i].setButtonText(OPTION_KEYS[i]);

        optionButtons[i].onClick = [this, i](){ optionButtonClicked(&(optionButtons[i])); };
    }
    
    optionButtons[0].triggerClick();
}

WhammyPlugAudioProcessorEditor::~WhammyPlugAudioProcessorEditor()
{
}

//==============================================================================
void WhammyPlugAudioProcessorEditor::paint(Graphics& g)
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
    pedal_level.setBounds(slider_container_area.removeFromTop(slider_container_area.getHeight() * 29 / 30).reduced(slider_container_margin)); // -20

    // knob is inside the knob container area
    auto knob_container_area = knob_area.removeFromLeft(knob_area.getWidth());
    auto knob_container_margin = knob_container_area.getWidth() / 5;

    knob_container.setBounds(knob_container_area.reduced(knob_container_margin));
    pitch_choice.setBounds(knob_container_area.removeFromTop(knob_container_area.getHeight()).reduced(knob_container_margin));

    // semitones boxes are inside the boxes container area
    auto boxes_container_area = boxes_area.removeFromLeft(boxes_area.getWidth());
    auto boxes_container_margin = boxes_container_area.getWidth() / 30;

    boxes_container.setBounds(boxes_container_area.removeFromTop(50));

    auto boxes_height = boxes_container_area.getHeight() / 15;

    for (int i = 0; i < N_OPTIONS; i++)
        optionButtons[i]
        .setBounds(boxes_container_area.removeFromTop(boxes_height)
            .reduced(boxes_container_margin));
}

void WhammyPlugAudioProcessorEditor::pedalValueChanged(Slider* s)
{
    //double tmp = s->getValue();
    processor.currPitch = s->getValue();
    // shifter update only if the slider difference is noticeable
    // in order not to make too many heavy calls
    //if (abs(tmp - processor.getPitchSemiTones()) >= 1E-3)
        //processor.setPitchSemiTones(tmp);

    if (abs(processor.currPitch - processor.getPitchSemiTones()) >= 1E-3)
        processor.setPitchSemiTones(processor.currPitch);
}

void WhammyPlugAudioProcessorEditor::pedalMaxValueSetup(int option_index)
{
    int max_range = OPTION_VALUES[option_index];
    if (max_range > 0)
        pedal_level.setRange(0, max_range);
    else
    {
        auto range = NormalisableRange<double>(max_range, 0.0,
            [](auto rangeStart, auto rangeEnd, auto normalised)
            { return jmap(normalised, rangeEnd, rangeStart); },
            [](auto rangeStart, auto rangeEnd, auto value)
            { return jmap(value, rangeEnd, rangeStart, 0.0, 1.0); },
            [](auto rangeStart, auto rangeEnd, auto value)
            { return value; });
        pedal_level.setNormalisableRange(range);
    }
    pedal_level.setValue(0.0);
    pedal_level.setNumDecimalPlacesToDisplay(2);
}

void WhammyPlugAudioProcessorEditor::updateOptionButtonAppearence(Button* which)
{
    for (int j = 0; j < N_OPTIONS; j++)
        if (&(optionButtons[j]) != which)
            optionButtons[j].setColour(TextButton::buttonColourId, Colours::maroon);
    which->setColour(TextButton::buttonColourId, Colours::yellow);
}

void WhammyPlugAudioProcessorEditor::knobValueChanged(Slider *sender)
{
    int option_index = (int)sender->getValue();
    // update of the pedal bound
    pedalMaxValueSetup(option_index);
    // and update of the button selection appearence
    // avoiding further handler triggers
    updateOptionButtonAppearence(&(optionButtons[option_index]));
}

void WhammyPlugAudioProcessorEditor::optionButtonClicked(Button* sender)
{
    for(int i = 0; i < N_OPTIONS; i++)
        if(!OPTION_KEYS[i].compare(sender->getButtonText())) // useless indexOf =(
        {
            // trigger automatico di knobValueChanged
            pitch_choice.setValue(i);
            break;
        }
}
