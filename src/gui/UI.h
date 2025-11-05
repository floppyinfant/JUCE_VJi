//
// Created by thorsten on 30.10.2025.
//
#pragma once

#include <JuceHeader.h>

using namespace juce;

class UI final : public juce::Component, private juce::FilenameComponentListener {
public:
    explicit UI();
    ~UI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    //PluginAudioProcessor& processor;
    //AudioProcessorEditor& editor;

    //LookAndFeel& laf;
    //LookAndFeel_V4& laf;
    //AudioProcessorValueTreeState& vts;

    // ------------------------------------------------

    // Toolbar
    // from WidgetsDemo/ToolbarDemoComp
    juce::Toolbar toolbar;
    juce::Slider depthSlider  { juce::Slider::LinearHorizontal, juce::Slider::TextBoxLeft };
    juce::Label depthLabel  { {}, "Toolbar depth:" },
          infoLabel   { {}, "As well as showing off toolbars, this demo illustrates how to store "
                            "a set of SVG files in a Zip file, embed that in your application, and read "
                            "them back in at runtime.\n\nThe icon images here are taken from the open-source "
                            "Tango icon project."};

    // Menu
    // from WidgetsDemo/MenuPage
    juce::TextButton menuButton { "Menu" };
    void makeMenu(juce::Button&);

    // ------------------------------------------------

    // MenuBar
    // from MenusDemo
    std::unique_ptr<juce::MenuBarComponent> menuBar;
    juce::ApplicationCommandManager commandManager;

    BurgerMenuComponent burgerMenu;
    //BurgerMenuHeader menuHeader { sidePanel };

    juce::ShapeButton burgerButton { "burgerButton", juce::Colours::lightgrey, juce::Colours::lightgrey, juce::Colours::white };
    void makeBurgerButton();

    juce::SidePanel sidePanel { "Menu", 300, false };
    void showOrHide()
    {
        sidePanel.showOrHide (! sidePanel.isPanelShowing());
    }

    juce::ScopedMessageBox messageBox;
    void alert(const juce::String&, const juce::String&);

    // ------------------------------------------------

    // FileChooser
    // from CodeEditorDemo
    juce::FilenameComponent fileChooser { "File", {}, true, false, false, "*.cpp;*.h;*.hpp;*.c;*.mm;*.m", {}, "Choose a C++ file to open it in the editor" };

    void filenameComponentChanged (juce::FilenameComponent*) override;

    // ------------------------------------------------

    static void toggleView(juce::Component& c) {
        if (c.isVisible()) {
            c.setVisible(false);
        } else {
            c.setVisible(true);
        }
        //sidePanel.showOrHide (! sidePanel.isPanelShowing());
    }

    // ------------------------------------------------

    // ------------------------------------------------

};
