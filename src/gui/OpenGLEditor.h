//
// Created by thorsten on 26.10.2025.
//

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include <juce_opengl/juce_opengl.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "components/OpenGLComponent.h"

class OpenGLEditor final : public juce::AudioProcessorEditor
{
public:
    explicit OpenGLEditor (PluginAudioProcessor&);
    ~OpenGLEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    PluginAudioProcessor& processor;

    OpenGLComponent openGLComponent;
};
