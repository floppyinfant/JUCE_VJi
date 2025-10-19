/*
  ==============================================================================

    KeyboardComponent.cpp
    Created: 3 Sep 2022 2:06:43pm
    Author:  thorsten

  ==============================================================================
*/

#include "KeyboardComponent.h"

KeyboardComponent::KeyboardComponent()
{
    // Example Code from JUCE-Tutorial DSPIntroduction_02
    //addAndMakeVisible(midiKeyboardComponent);
    //midiKeyboardComponent.setMidiChannel(1);
    //midiKeyboardState.addListener(&audioProcessor.getMidiMessageCollector());

    // setup Components
    
    // addListener
     
    // addAndMakeVisible

    setSize(800, 600);
}

KeyboardComponent::~KeyboardComponent()
{
    //midiKeyboardState.removeListener(&audioProcessor.getMidiMessageCollector());
}

void KeyboardComponent::paint(juce::Graphics&)
{
}

void KeyboardComponent::resized()
{
}
