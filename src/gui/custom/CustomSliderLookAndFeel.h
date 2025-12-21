// AulusSliderLookAndFeel.h
// https://forum.juce.com/t/solved-make-custom-slider-rotary/38889

#pragma once

#include <JuceHeader.h>

class CustomSliderLookAndFeel : public LookAndFeel_V4
{
public:
    CustomSliderLookAndFeel();

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
    void drawLabel(Graphics& g, Label& label) override;

private:
    Image knobRelease;
};
