//
// Created by thorsten on 30.10.2025.
//

#include "UI.h"

UI::UI()
{
    setOpaque(false);  // Make transparent so layers below show through
    setInterceptsMouseClicks(false, true);
}

UI::~UI() {

}

void UI::paint(juce::Graphics &g) {
    // Example: semi-transparent overlay
    //g.fillAll(juce::Colours::black.withAlpha(0.7f));

    // remove (only debugging purposes)
    // Draw custom text or shapes on top
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Overlay Layer", getLocalBounds(), juce::Justification::centred);

    // TODO: GUI
    // Layout Manager --> resized()
    // - header, footer: mouseEnter(), mouseExit()

    // Menu Bar

    // Popup Menu
    addAndMakeVisible(menuButton);
    makeMenu();

    // View Settings
    // - set Visibility
    // - set Alpha (Transparency)
    // - toggle codeEditor visibility
    // - set FPS
    // - load / save files (see Demo codeEditor)

    // View playlist (sidepanel transparent)
    // View parameters

    // View help (sidepanel transparent)
    // View about (Alert Window)
}

void UI::resized() {

    // Layout Manager
    // from WidgetsDemo/MenuPage
    FlexBox box;
    box.flexDirection = FlexBox::Direction::column;
    box.items = {
        // Header --------------
        // MenuBar
        // Toolbar with Icons, PresetsBox, Settings
        // Main ----------------
        // Widgets (with Transparency)
        FlexItem { menuButton }.withWidth (200).withHeight (24).withMargin ({ 4 })
        // GLSL (in the background)
        // Popup-Menu
        // Sidebar
        // Footer --------------
        // codeEditor
    };

    box.performLayout (getLocalBounds());
}

void UI::makeMenu() {
    // lambda Button Listener
    menuButton.onClick = [&]
    {
        // create menu
        PopupMenu menu;

        // ------------------------------------------------

        //->Submenu
        PopupMenu subMenuFile;
        subMenuFile.addItem ("New", nullptr);  // new [Ctrl+N]
        subMenuFile.addItem ("Open File", nullptr);  // open [Ctrl+O]
        subMenuFile.addItem ("Save Preset", nullptr);  // save [Ctrl+S]
        subMenuFile.addItem ("Export File", nullptr);  //
        // print [Ctrl+P]
        // close [Ctrl+W]
        // quit [Ctrl+Q]

        // ------------------------------------------------

        //->Submenu
        PopupMenu subMenuEdit;
        // undo [Ctrl+Z]
        // redo [Ctrl+Y]
        // separator
        // cut [Ctrl+X]
        subMenuEdit.addItem ("Copy Shader Code", nullptr);  // copy [Ctrl+C]
        subMenuEdit.addItem ("Paste Shader Code", nullptr);  // paste [Ctrl+V]
        // select all [Ctrl+A]
        // search | find [Ctrl+F]

        // ------------------------------------------------

        //->Submenu
        PopupMenu subMenuView;
        subMenuView.addItem ("Fullscreen", nullptr);  // fullscreen toggle [F11]
        subMenuView.addSeparator();
        // toggle menuBar, toolBar, sideBar [Ctrl+B,D], widgets (Main Settings)
        subMenuView.addSeparator();
        // zoom: everything (GUI) or font (codeEditor) ?
        subMenuView.addItem ("Zoom In", nullptr);  // [Ctrl++]
        subMenuView.addItem ("Zoom out", nullptr);  // [Ctrl+-]
        subMenuView.addSeparator();
        // toggle
        subMenuView.addItem ("Shader", nullptr);
        subMenuView.addItem ("Parameter", nullptr);
        subMenuView.addItem ("Playlist", nullptr);
        subMenuView.addItem ("Settings", nullptr);
        subMenuView.addSeparator();
        subMenuView.addItem ("MIDI-Processor", nullptr);
        subMenuView.addItem ("DSP-Processor", nullptr);


        // ------------------------------------------------

        //->Submenu
        PopupMenu subMenuHelp;
        subMenuHelp.addItem ("On Screen Help", nullptr);  // Transparent Overlay [F1]
        subMenuHelp.addSeparator();
        subMenuHelp.addItem ("GLSL Help (Web)", nullptr);  // OpenGL Wiki
        subMenuHelp.addItem ("Documentation (Web)", nullptr);
        subMenuHelp.addItem ("Documentation (PDF)", nullptr);
        subMenuHelp.addSeparator();
        subMenuHelp.addItem ("about", nullptr);

        // ------------------------------------------------

        // Menu
        menu.addSubMenu ("File", subMenuFile);
        menu.addSubMenu ("Edit", subMenuEdit);
        menu.addSubMenu ("View", subMenuView);
        //menu.addSubMenu ("Commands", subMenu);
        menu.addSubMenu ("Help", subMenuHelp);  // help [F1]
        menu.addItem ("Settings", nullptr);  // settings [Ctrl+Alt+S]
        menu.addSeparator();
        menu.addItem ("Quit", nullptr);  // [Ctrl+W], [Ctrl+Q], [Ctrl+Shift+Q]
        // Standalone: Exit; Plugin: leave ShaderEditor && load PluginEditor

        // more Shortcuts | Hotkeys:
        // [Ctrl+Shift+...]
        // [Shift+F...]

        // finally show menu
        menu.showMenuAsync (PopupMenu::Options{}.withTargetComponent (menuButton));
    };
}