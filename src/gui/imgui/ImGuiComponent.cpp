//
// Created by thorsten on 06.12.2025.
//
#include <JuceHeader.h>
#include "ImGuiComponent.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_juce/imgui_impl_juce.h>


ImGuiComponent::ImGuiComponent()
{
    setOpaque(true);

    // set up opengl context
    glctx.setOpenGLVersionRequired(juce::OpenGLContext::openGL3_2);
    glctx.setRenderer(this);
    glctx.attachTo(*this);
    glctx.setContinuousRepainting(true);

    setSize(1000, 600);
    setWantsKeyboardFocus(true);
}

void ImGuiComponent::newOpenGLContextCreated()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplJuce_Init(*this, glctx);
    ImGui_ImplOpenGL3_Init();
}

void ImGuiComponent::renderOpenGL()
{
    using namespace juce::gl;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplJuce_NewFrame();
    ImGui::NewFrame();

    // -----------------------------------------------------------------------
    // imgui Docking
    // -----------------------------------------------------------------------

    // Create a dockspace in main viewport.
    // https://github.com/ocornut/imgui/wiki/Docking
    // enable `Demo > Configuration > Docking > io.ConfigFlags: Docking Enabled`
    ImGui::DockSpaceOverViewport();

    // -----------------------------------------------------------------------
    // imgui begin
    // -----------------------------------------------------------------------
    ImGui::Begin("Settings");
    //ImGui::Begin("window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Button("Hello");
    ImGui::Text("Hello, world");
    ImGui::ShowDemoWindow();

    ImGui::End();
    // -----------------------------------------------------------------------
    // imgui end
    // -----------------------------------------------------------------------

    ImGui::Render();

    // background begin
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    // background end

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiComponent::openGLContextClosing()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplJuce_Shutdown();
    ImGui::DestroyContext();
}

// regular ui not used
void ImGuiComponent::paint(juce::Graphics &) {}
void ImGuiComponent::resized() {}
