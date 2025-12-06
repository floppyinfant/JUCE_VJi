//
// Created by thorsten on 01.12.2025.
//

#pragma once

#include "PluginProcessor.h"
#include "ImGuiComponent.h"

class ImGuiEditor final : public juce::AudioProcessorEditor
{
public:
    explicit ImGuiEditor (PluginAudioProcessor&);
    ~ImGuiEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginAudioProcessor& processorRef;

    // --------------------------------
    // ImGui
    // --------------------------------
    ImGuiComponent imGuiComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImGuiEditor)
};
