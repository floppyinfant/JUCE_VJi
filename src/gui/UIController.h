//
// Created by thorsten on 28.10.2025.
//
#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

/**
 * Event Loop, Event Handler (OnClick, ...), Action Listener (addListener), Callbacks
 * https://juce.com/tutorials/tutorial_listeners_and_broadcasters/
 * https://docs.juce.com/master/classjuce_1_1Button_1_1Listener.html
 * https://docs.juce.com/master/classjuce_1_1KeyListener.html
 * https://docs.juce.com/master/classjuce_1_1Component.html (MouseListener is extended by Component)
 *
 * Parameters, APVTS (AudioProcessorValueTreeState), Properties
 * https://juce.com/tutorials/tutorial_value_tree/
 * https://docs.juce.com/master/classjuce_1_1ValueTree.html
 * https://juce.com/tutorials/tutorial_audio_processor_value_tree_state/
 * https://juce.com/tutorials/tutorial_audio_parameter/
 *
 * Event Dispatch Thread (EDT), Dispatcher
 * https://docs.juce.com/master/classjuce_1_1AsyncUpdater.html (Async)
 *
 * --------------------------------------------------------------
 *
 * User Interface
 *
 * Model, View, Controller (MVC) Paradigm, Observer Pattern (notifyObservers())
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
 * https://docs.juce.com/master/classjuce_1_1UIViewComponent.html (UIViewComponent)
 * https://developer.apple.com/documentation/uikit/view-controllers
 * https://developer.apple.com/documentation/UIKit/UIViewController
 */

class UIController : public juce::Component //, public juce::KeyListener
{
public:
    UIController(PluginAudioProcessor&);
    ~UIController() override;

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

    // ===========================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UIController)
};
