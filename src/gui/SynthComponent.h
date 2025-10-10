/*
  ==============================================================================

    SynthComponent.h
    Created: 1 Sep 2022 7:17:40pm
    Author:  thorsten

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class SynthComponent : public juce::GroupComponent  // Component || Editor ???
    , public juce::Slider::Listener
    , public juce::Button::Listener
    , public juce::ComboBox::Listener
    , private juce::Timer
{
public:

    SynthComponent();  //SQ251AudioProcessor& p
    ~SynthComponent();

    void paint(juce::Graphics&) override;
    void resized() override;

    //--------------------------------------------------------------------------
    // Listener Callbacks
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* btn) override;
    void comboBoxChanged(juce::ComboBox* cb) override;
    void timerCallback() override;

private:

    //--------------------------------------------------------------------------
    // Groups
    juce::GroupComponent generators;
    juce::GroupComponent modifiers;

    juce::GroupComponent vco;
    juce::GroupComponent mix;
    juce::GroupComponent vcf;
    juce::GroupComponent vca;

    //--------------------------------------------------------------------------
    // Components
    juce::Slider slider;
    juce::Label label;
    // Attachements connect the Component to the Parameter via the APVTS
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;


    // examples: definition (make_unique) in CTOR-Init-List
    //std::unique_ptr<juce::Slider> sliderGain;
    //std::unique_ptr<juce::Label> labelGain;
    //juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachments;
    //std::unique_ptr<juce::GroupComponent> sliderGroup;

};
