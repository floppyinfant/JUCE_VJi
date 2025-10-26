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

    // --------------------------------

    void paint(juce::Graphics& g) override;
    void resized() override;

    // -----------------------------------------------------------------------

    // AnimatedAppComponent - as a Plugin (AudioProcessorEditor) it is not possible to inherit from this class

    /**
     * start a timer running which will call update() and repaint the component at the given frequency.
    */
    void setFramesPerSecond (int framesPerSecond);

    /** You can use this function to synchronise animation updates with the current display's vblank
        events. When this mode is enabled the value passed to setFramesPerSecond() is ignored.
    */
    void setSynchroniseToVBlank (bool syncToVBlank);

    /** Called periodically, at the frequency specified by setFramesPerSecond().
        This is a the best place to do things like advancing animation parameters,
        checking the mouse position, etc.
    */
    void update();

    /** Returns the number of times that update() has been called since the component
        started running.
    */
    int getFrameCounter() const noexcept { return totalUpdates; }

    /** When called from update(), this returns the number of milliseconds since the
        last update call.
        This might be useful for accurately timing animations, etc.
    */
    int getMillisecondsSinceLastUpdate() const noexcept;

    // -----------------------------------------------------------------------

    void mouseEnter(const MouseEvent &event) override;

    void mouseExit(const MouseEvent &event) override;

    void mouseMove(const MouseEvent &event) override;

    void mouseDown(const MouseEvent &event) override;

    void mouseUp(const MouseEvent &event) override;

    void mouseDrag(const MouseEvent &event) override;

    void mouseDoubleClick(const MouseEvent &event) override;

    void mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) override;

    void mouseMagnify(const MouseEvent &event, float scaleFactor) override;

    // --------------------------------

    bool keyPressed(const KeyPress &key) override;

    bool keyStateChanged(bool isKeyDown) override;

    void modifierKeysChanged(const ModifierKeys &modifiers) override;

    // -----------------------------------------------------------------------

    void selectPreset(int preset);

    juce::Label statusLabel, presetLabel  {{}, "Shader Preset:"};
    juce::ComboBox presetBox;
    juce::CodeDocument fragmentDocument;
    juce::CodeEditorComponent fragmentEditorComp  {fragmentDocument, nullptr};

    // --------------------------------

    // GL
    juce::String fragmentCode;
    std::unique_ptr<juce::OpenGLGraphicsContextCustomShader> shader;

private:
    PluginAudioProcessor& processor;

    // -----------------------------------------------------------------------

    // GL
    juce::OpenGLContext openGLContext;

    //std::unique_ptr<juce::OpenGLGraphicsContextCustomShader::Uniform> iResolutionUniform;
    //std::unique_ptr<juce::OpenGLGraphicsContextCustomShader::Uniform> iTimeUniform;

    // fi:
    bool isShaderToyCode = false;
    int frameCounter = 0;              // use to set up Uniforms
    double startTime = 0.0;            // use to set up Uniforms

    juce::String convert(const juce::String& shaderCode);
    juce::String convertShadertoy(const juce::String& shaderToyCode);

    // -----------------------------------------------------------------------

    enum {shaderLinkDelay = 500};

    void codeDocumentTextInserted(const juce::String& /*newText*/, int /*insertIndex*/) override
    {
        startTimer (shaderLinkDelay);
    }

    void codeDocumentTextDeleted(int /*startIndex*/, int /*endIndex*/) override
    {
        startTimer(shaderLinkDelay);
    }

    void timerCallback() override;

    struct ShaderPreset
    {
        const char* name;
        const char* fragmentShader;
    };

    static juce::Array<ShaderPreset> getPresets();

    // -----------------------------------------------------------------------

    // AnimatedAppComponent

    void updateSync();

    Time lastUpdateTime = Time::getCurrentTime();
    int totalUpdates = 0;
    int framesPerSecond = 60;
    bool useVBlank = false;
    VBlankAttachment vBlankAttachment;

    // -----------------------------------------------------------------------

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShaderEditor)
};
