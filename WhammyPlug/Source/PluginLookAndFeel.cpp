
#include "PluginLookAndFeel.h"
#include "PluginEditor.h"

PluginLookAndFeel::PluginLookAndFeel()
{
};

PluginLookAndFeel::~PluginLookAndFeel()
{
}


void PluginLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos,
    float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    if (style == Slider::LinearVertical)
    {
        if (slider.isVertical()) {
            g.setColour(Colours::black.withAlpha(1.0f));
            
            g.fillRect(width * 7 / 18, y + height, width * 2 / 9, y);        
            g.fillRect(width * 7 / 18, (int)sliderPos, width * 2 / 9, height / 30);
            
            g.setColour(Colours::black.withAlpha(0.4f));
            g.fillRect(width / 2 - width / 20, y + (int)sliderPos, width / 10, height);
            
        }
    }
}

void PluginLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
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
    Colour color = Colours::black;
    g.setColour(color.withAlpha(0.7f));
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

    g.setColour(Colours::black.withAlpha(1.0f));
    g.fillPath(p);
}

