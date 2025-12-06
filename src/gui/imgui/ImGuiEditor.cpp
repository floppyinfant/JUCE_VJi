/*
https://github.com/Krasjet/imgui_juce
https://github.com/ocornut/imgui
https://github.com/ocornut/imgui/wiki
https://github.com/ocornut/imgui/wiki/Docking

The plugin will crash if you add multiple instances of the plugin in DAW and open two GUIs at the same time.
You need to patch ImGui and make the global state thread local

    thread_local ImGuiContext* GImGui = NULL;

in order to support multiple instances of ImGui running at the same time on different threads. See

    ./examples/sine/patches/imgui/multi_instance.patch

for details.
You need a similar patch if you want to use imnodes or ImPlot in your plugin. For a ImPlot example, see

    ./examples/scope/patches/implot/multi_instance.patch

https://github.com/ocornut/imgui/wiki/Useful-Extensions
https://github.com/epezent/implot
https://github.com/rokups/ImNodes
https://github.com/thedmd/imgui-node-editor
 */
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ImGuiEditor.h"

//#include <imgui.h>
//#include <imgui_impl_opengl3.h>
//#include <imgui_impl_juce/imgui_impl_juce.h>  // instead of "imgui_impl_glfw.h"


ImGuiEditor::ImGuiEditor (PluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    // --------------------------------
    // ImGui
    // --------------------------------
    addAndMakeVisible(imGuiComponent);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    setResizable(true, true);
}

ImGuiEditor::~ImGuiEditor()
{
}

void ImGuiEditor::paint (juce::Graphics& g)
{
    // don't use it for ImGui
    juce::ignoreUnused (g);
}

void ImGuiEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    imGuiComponent.setBounds(getLocalBounds());
}
