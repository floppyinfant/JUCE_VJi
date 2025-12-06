/*
https://github.com/Krasjet/imgui_juce
https://github.com/ocornut/imgui
https://github.com/ocornut/imgui/wiki


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

#include "ImGuiEditor.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_juce/imgui_impl_juce.h>  // instaed of "imgui_impl_glfw.h"

