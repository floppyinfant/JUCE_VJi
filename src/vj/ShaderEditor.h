#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include <juce_opengl/juce_opengl.h>
#include <juce_gui_extra/juce_gui_extra.h>

class ShaderEditor final : public juce::AudioProcessorEditor,
                           private juce::CodeDocument::Listener,
                           private juce::Timer
{
public:
    explicit ShaderEditor(PluginAudioProcessor& processor);
    ~ShaderEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void selectPreset(int preset);

    std::unique_ptr<juce::OpenGLGraphicsContextCustomShader> shader;

    juce::Label statusLabel, presetLabel  {{}, "Shader Preset:"};
    juce::ComboBox presetBox;
    juce::CodeDocument fragmentDocument;
    juce::CodeEditorComponent fragmentEditorComp  {fragmentDocument, nullptr};
    juce::String fragmentCode;

private:
    PluginAudioProcessor& processor;
    juce::OpenGLContext openGLContext;

    //std::unique_ptr<juce::OpenGLGraphicsContextCustomShader::Uniform> iResolutionUniform;
    //std::unique_ptr<juce::OpenGLGraphicsContextCustomShader::Uniform> iTimeUniform;

    enum {shaderLinkDelay = 500};

    void codeDocumentTextInserted(const juce::String& /*newText*/, int /*insertIndex*/) override
    {
        startTimer (shaderLinkDelay);
    }

    void codeDocumentTextDeleted(int /*startIndex*/, int /*endIndex*/) override
    {
        startTimer(shaderLinkDelay);
    }

    void timerCallback() override
    {
        stopTimer();
        fragmentCode = fragmentDocument.getAllContent();
        repaint();
    }

    struct ShaderPreset
    {
        const char* name;
        const char* fragmentShader;
    };

    static juce::Array<ShaderPreset> getPresets();


    // fi:
    bool isShaderToyCode = false;
    int frameCounter = 0;
    double startTime = 0.0;

    // Add method to convert ShaderToy code
    juce::String convertShaderToyToJUCE(const juce::String& shaderToyCode);

    // Add method to create wrapper with uniforms
    juce::String wrapWithUniforms(const juce::String& shaderCode);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShaderEditor)
};
