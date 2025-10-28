//
// Created by thorsten on 28.10.2025.
//
#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

/**
 * User Interface View Controller
 * MVC-Paradigm
 */
class ViewController : public juce::Component
{
public:
    ViewController();
    ~ViewController() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    // --------------------------------
    void mouseEnter(const MouseEvent &event) override;
    void mouseExit(const MouseEvent &event) override;
    void mouseMove(const MouseEvent &event) override;
    void mouseDown(const MouseEvent &event) override;
    void mouseUp(const MouseEvent &event) override;
    void mouseDrag(const MouseEvent &event) override;
    void mouseDoubleClick(const MouseEvent &event) override;
    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;
    void mouseMagnify(const MouseEvent &event, float scaleFactor) override;
    // --------------------------------
    bool keyPressed(const KeyPress &key) override;
    bool keyStateChanged(bool isKeyDown) override;
    void modifierKeysChanged(const ModifierKeys &modifiers) override;
    // --------------------------------

private:
    PluginAudioProcessor& processor;
    AudioProcessorEditor& editor;
    AudioProcessorValueTreeState& vts;
};
