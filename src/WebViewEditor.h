#pragma once

#include "PluginProcessor.h"
#include <juce_gui_extra/juce_gui_extra.h>

class PluginWebViewEditor final : public juce::AudioProcessorEditor
{
public:
    explicit PluginWebViewEditor (PluginAudioProcessor&);
    ~PluginWebViewEditor() override;

    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginAudioProcessor& processorRef;

    using Resource = juce::WebBrowserComponent::Resource;
    std::optional<Resource> getResource (const juce::String& ur);

    juce::WebBrowserComponent webView;
    //std::unique_ptr<juce::WebBrowserComponent> webView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginWebViewEditor)
};
