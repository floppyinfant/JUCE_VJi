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
    //g.drawText("Overlay Layer", getLocalBounds(), juce::Justification::centred);

    // TODO: GUI
    // Layout Manager --> resized()
    // - header, footer: mouseEnter(), mouseExit()

    // Menu Bar

    // Popup Menu
    /*
    addAndMakeVisible(menuButton);
    menuButton.setAlpha(0.5f);
    menuButton.changeWidthToFitText();
    makeMenu(menuButton);
    */

    makeBurgerButton();
    addAndMakeVisible (burgerButton);
    makeMenu(burgerButton);

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
        //FlexItem { menuButton }.withWidth (100).withHeight (24).withMargin ({ 4 }),
        FlexItem { burgerButton }.withWidth (100).withHeight (24).withMargin ({ 4 })
        // GLSL (in the background)
        // Popup-Menu
        // Sidebar
        // Footer --------------
        // codeEditor
    };

    box.performLayout (getLocalBounds());
}

void UI::makeBurgerButton() {
    static const unsigned char burgerMenuPathData[]
            = { 110,109,0,0,128,64,0,0,32,65,108,0,0,224,65,0,0,32,65,98,254,212,232,65,0,0,32,65,0,0,240,65,252,
                169,17,65,0,0,240,65,0,0,0,65,98,0,0,240,65,8,172,220,64,254,212,232,65,0,0,192,64,0,0,224,65,0,0,
                192,64,108,0,0,128,64,0,0,192,64,98,16,88,57,64,0,0,192,64,0,0,0,64,8,172,220,64,0,0,0,64,0,0,0,65,
                98,0,0,0,64,252,169,17,65,16,88,57,64,0,0,32,65,0,0,128,64,0,0,32,65,99,109,0,0,224,65,0,0,96,65,108,
                0,0,128,64,0,0,96,65,98,16,88,57,64,0,0,96,65,0,0,0,64,4,86,110,65,0,0,0,64,0,0,128,65,98,0,0,0,64,
                254,212,136,65,16,88,57,64,0,0,144,65,0,0,128,64,0,0,144,65,108,0,0,224,65,0,0,144,65,98,254,212,232,
                65,0,0,144,65,0,0,240,65,254,212,136,65,0,0,240,65,0,0,128,65,98,0,0,240,65,4,86,110,65,254,212,232,
                65,0,0,96,65,0,0,224,65,0,0,96,65,99,109,0,0,224,65,0,0,176,65,108,0,0,128,64,0,0,176,65,98,16,88,57,
                64,0,0,176,65,0,0,0,64,2,43,183,65,0,0,0,64,0,0,192,65,98,0,0,0,64,254,212,200,65,16,88,57,64,0,0,208,
                65,0,0,128,64,0,0,208,65,108,0,0,224,65,0,0,208,65,98,254,212,232,65,0,0,208,65,0,0,240,65,254,212,
                200,65,0,0,240,65,0,0,192,65,98,0,0,240,65,2,43,183,65,254,212,232,65,0,0,176,65,0,0,224,65,0,0,176,
                65,99,101,0,0 };

    Path p;
    p.loadPathFromData (burgerMenuPathData, sizeof (burgerMenuPathData));
    burgerButton.setShape (p, true, true, false);
}

void UI::makeMenu(Button& b) {
    // lambda Button Listener
    b.onClick = [&]
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
        subMenuView.addItem ("Code Editor", nullptr);
        subMenuView.addItem ("Parameters", nullptr);
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
        subMenuHelp.addItem ("about", [this]{ alert("VJi", "A Music Visualizer Plugin for DAWs using GLSL Shaders\n\nhttp://www.floppyinfant.com/vji"); });

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
        menu.showMenuAsync (PopupMenu::Options{}.withTargetComponent (b));
    };
}

void UI::alert(const juce::String& title, const juce::String& message) {
    MessageBoxIconType icon = MessageBoxIconType::InfoIcon;
    auto options = MessageBoxOptions::makeOptionsOk (icon, title, message);
    messageBox = AlertWindow::showScopedAsync (options, nullptr);
    //juce::AlertWindow::showMessageBoxAsync (s);
}

void UI::filenameComponentChanged (FilenameComponent*)
{
    //editor->loadContent (fileChooser.getCurrentFile().loadFileAsString());
}
