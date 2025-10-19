/*
  ==============================================================================

    KeyboardComponent.h
    Created: 3 Sep 2022 2:06:43pm
    Author:  thorsten

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class KeyboardComponent : public juce::Component
{
public:

    KeyboardComponent();
    ~KeyboardComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    // Example Code from JUCE-Tutorial DSPIntroduction_02
    juce::MidiKeyboardState midiKeyboardState;
    juce::MidiKeyboardComponent midiKeyboardComponent{ midiKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard };

};
