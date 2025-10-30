//
// Created by thorsten on 30.10.2025.
//
#pragma once

#include <JuceHeader.h>

class UI final : public juce::Component {
public:
    explicit UI();
    ~UI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    //Component parent;
    //PluginAudioProcessor& processor;
    //AudioProcessorEditor& editor;
    //LookAndFeel_V4& laf;
    //AudioProcessorValueTreeState& vts;

};
