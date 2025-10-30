//
// Created by thorsten on 30.10.2025.
//

#include "UI.h"

UI::UI()
{
    setOpaque(false);  // Make transparent so layers below show through
    setInterceptsMouseClicks(false, true);
}

UI::~UI() {

}

void UI::paint(juce::Graphics &g) {
    // Example: semi-transparent overlay
    //g.fillAll(juce::Colours::black.withAlpha(0.7f));

    // Draw custom text or shapes on top
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Overlay Layer", getLocalBounds(), juce::Justification::centred);
}

void UI::resized() {

    //Component::resized();
}
