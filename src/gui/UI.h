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

    // Toolbar
    // from WidgetsDemo/ToolbarDemoComp
    Toolbar toolbar;
    Slider depthSlider  { Slider::LinearHorizontal, Slider::TextBoxLeft };
    Label depthLabel  { {}, "Toolbar depth:" },
          infoLabel   { {}, "As well as showing off toolbars, this demo illustrates how to store "
                            "a set of SVG files in a Zip file, embed that in your application, and read "
                            "them back in at runtime.\n\nThe icon images here are taken from the open-source "
                            "Tango icon project."};

    // Menu
    // from WidgetsDemo/MenuPage
    TextButton menuButton { "Menu" };
    void makeMenu();

    //LookAndFeel& laf;
    //LookAndFeel_V4& laf;
    //AudioProcessorValueTreeState& vts;

};
