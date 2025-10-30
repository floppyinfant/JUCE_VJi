//
// Created by thorsten on 28.10.2025.
//
#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

/**
 * User Interface View Controller
 * MVC-Paradigm, Observer Pattern (notifyObservers())
 *
 * Model, View, Controller (MVC)
 * https://de.wikipedia.org/wiki/Model_View_Controller
 * https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller
 *
 * ViewModel in Android
 * https://de.wikipedia.org/wiki/Model_View_ViewModel
 * https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93viewmodel
 * https://developer.android.com/topic/libraries/architecture/viewmodel
 * https://learn.microsoft.com/de-de/dotnet/architecture/maui/mvvm
 *
 * ViewController, UIViewController in Swift (iOS)
 * https://developer.apple.com/documentation/uikit/view-controllers
 * https://developer.apple.com/documentation/UIKit/UIViewController
 */
class ViewController : public juce::Component
{
public:
    ViewController(PluginAudioProcessor);
    ~ViewController() override;

    // --------------------------------

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
    //LookAndFeel_V4& laf;
    //AudioProcessorValueTreeState& vts;
};
