#pragma once

#include "PluginProcessor.h"
#include "gui/custom/CustomSlider.h"

//==============================================================================
class PluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit PluginAudioProcessorEditor (PluginAudioProcessor&);
    ~PluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginAudioProcessor& processorRef;

    CustomSlider rotary;

    // ===========================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginAudioProcessorEditor)
};
