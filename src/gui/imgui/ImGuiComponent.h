//
// Created by thorsten on 06.12.2025.
//
#pragma once

class ImGuiComponent : public juce::Component, public juce::OpenGLRenderer
{
public:
    ImGuiComponent();

    void newOpenGLContextCreated() override;

    void renderOpenGL() override;

    void openGLContextClosing() override;

    // regular ui not used
    void paint(juce::Graphics &) override;
    void resized() override;

private:
    juce::OpenGLContext glctx;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImGuiComponent)
  };
