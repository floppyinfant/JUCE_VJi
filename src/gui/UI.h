//
// Created by thorsten on 30.10.2025.
//
#pragma once

#include <JuceHeader.h>

class UI final : public juce::Component, private FilenameComponentListener {
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
    void makeMenu(Button&);

    // ------------------------------------------------

    // MenuBar
    // from MenusDemo
    std::unique_ptr<MenuBarComponent> menuBar;
    ApplicationCommandManager commandManager;

    BurgerMenuComponent burgerMenu;
    //BurgerMenuHeader menuHeader { sidePanel };

    ShapeButton burgerButton { "burgerButton", Colours::lightgrey, Colours::lightgrey, Colours::white };
    void makeBurgerButton();

    SidePanel sidePanel { "Menu", 300, false };
    void showOrHide()
    {
        sidePanel.showOrHide (! sidePanel.isPanelShowing());
    }

    ScopedMessageBox messageBox;
    void alert(const juce::String&, const juce::String&);

    // ------------------------------------------------

    // FileChooser
    // from CodeEditorDemo
    FilenameComponent fileChooser { "File", {}, true, false, false, "*.cpp;*.h;*.hpp;*.c;*.mm;*.m", {}, "Choose a C++ file to open it in the editor" };

    void filenameComponentChanged (FilenameComponent*) override;

    // ------------------------------------------------

    static void toggleView(Component& c) {
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
