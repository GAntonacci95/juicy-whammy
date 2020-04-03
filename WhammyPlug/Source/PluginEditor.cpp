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

    // Slider that controls the amount of use of the pedal
    // max_pitch must be the maximum value selected using the rotary slider
    pedal_level->setSliderStyle(Slider::LinearVertical);
    pedal_level->setRange(0, 5);
    pedal_level->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    pedal_level->setPopupDisplayEnabled(true, true, this);
    pedal_level->setTextValueSuffix(" semitones");
    pedal_level->setValue(0.0);
    //pedal_level->addListener(this);
    addAndMakeVisible(pedal_level);

    // Slider that is used to choose the amount of pitch shift
    pitch_choice->setSliderStyle(Slider::Rotary);
    pitch_choice->setRange(-12, 12, 1.0);
    pitch_choice->setTextBoxStyle(Slider::NoTextBox, false, 180, 0);
    pitch_choice->setValue(0.0);
    //pitch_choice->addListener(this);
    addAndMakeVisible(pitch_choice);
}

WhammyPlugAudioProcessorEditor::~WhammyPlugAudioProcessorEditor()
{
    /*
    pedal_level = nullptr;
    pitch_choice = nullptr;
    */
}

//==============================================================================
void WhammyPlugAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colour(185, 0, 0));
    
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::horizontallyCentred, 1);
    
}

void WhammyPlugAudioProcessorEditor::resized()
{
    pedal_level->setBounds(getWidth() / 4, getHeight() / 10, 10, getHeight()/2);
    pitch_choice->setBounds(getWidth() / 2, getHeight() / 10, getWidth() / 8, getHeight() / 8);
}

/*
void WhammyPlugAudioProcessorEditor::sliderValueChanged(Slider* s)
{
    if (s == pedal_level)
        processor.pitch_value = s->getValue();
    else if (s == pitch_choice)
        processor.knob_value = s->getValue();
}
*/
/*
void WhammyPlugAudioProcessorEditor::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto radius = 40.0f;
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
*/

