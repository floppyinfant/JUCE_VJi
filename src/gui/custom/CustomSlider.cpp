// AulusSlider.cpp
// https://forum.juce.com/t/solved-make-custom-slider-rotary/38889

#include <JuceHeader.h>
#include "CustomSlider.h"

CustomSlider::CustomSlider() : Slider()
{
    // In your constructor, you should add any child components, and
    // initialize any special settings that your component needs.

    setLookAndFeel(&customSliderLookAndFeel);
}

CustomSlider::~CustomSlider()
{
    setLookAndFeel(nullptr);
}

void CustomSlider::mouseDown(const MouseEvent& event)
{
    Slider::mouseDown(event);
    // --------------------------------
    setMouseCursor(MouseCursor::NoCursor);
    mousePosition = Desktop::getMousePosition();
}

void CustomSlider::mouseUp(const MouseEvent& event)
{
    Slider::mouseUp(event);
    // --------------------------------
    Desktop::setMousePosition(mousePosition);
    setMouseCursor(MouseCursor::NormalCursor);
}
