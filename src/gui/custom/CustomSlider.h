// AulusSlider.h
// https://forum.juce.com/t/solved-make-custom-slider-rotary/38889

#pragma once

#include <JuceHeader.h>
#include "CustomSliderLookAndFeel.h"

class CustomSlider : public Slider
{
public:
    CustomSlider();
    ~CustomSlider();

    void mouseDown(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;


private:
    CustomSliderLookAndFeel customSliderLookAndFeel;
    Point<int> mousePosition;

    // --------------------------------
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSlider)
};
