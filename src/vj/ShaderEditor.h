#pragma once

#include <JuceHeader.h>
#include <juce_opengl/juce_opengl.h>
#include <juce_gui_extra/juce_gui_extra.h>

#include "../PluginProcessor.h"
#include "../gui/UI.h"
#include "shaders/Presets.h"

class ShaderEditor final : public juce::AudioProcessorEditor,
                           private juce::CodeDocument::Listener,
                           private juce::MultiTimer
{
public:
    explicit ShaderEditor(PluginAudioProcessor& processor);
    ~ShaderEditor() override;

    // --------------------------------

    void paint(juce::Graphics& g) override;
    void resized() override;

    // -----------------------------------------------------------------------

    // AnimatedAppComponent - as a Plugin (AudioProcessorEditor) it is not possible to inherit from this class
    // https://docs.juce.com/master/classjuce_1_1AnimatedAppComponent.html

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

    // Listener Callbacks

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

    juce::CodeDocument codeDocument;
    juce::CodeEditorComponent codeEditorComponent  {codeDocument, nullptr};
    juce::String shaderCode;
    std::unique_ptr<juce::OpenGLGraphicsContextCustomShader> shader;

    // GUI
    std::unique_ptr<UI> overlayUI;
    void setFullscreen();

private:
    PluginAudioProcessor& processor;
    juce::OpenGLContext openGLContext;
    //std::unique_ptr<juce::OpenGLShaderProgram> shaderProgram;
    juce::OpenGLShaderProgram* shaderProgram;

    //std::unique_ptr<juce::OpenGLGraphicsContextCustomShader::Uniform> iResolutionUniform;
    //std::unique_ptr<juce::OpenGLGraphicsContextCustomShader::Uniform> iTimeUniform;

    // Uniform variables
    int u_frameCounter = 0;
    double u_startTime = 0.0;
    int u_mouseX = 0;
    int u_mouseY = 0;
    int u_mouseZ = 0;       // LMB clicked
    int u_mouseW = 0;       // RMB clicked

    bool isConverted;
    juce::String convert(const juce::String& shaderCode);

    // -----------------------------------------------------------------------

    // OpenGLDemo2D

    const int TIMER_DOCUMENT_CHANGED = 1;

    enum {shaderLinkDelay = 500};

    void codeDocumentTextInserted(const juce::String& /*newText*/, int /*insertIndex*/) override;
    void codeDocumentTextDeleted(int /*startIndex*/, int /*endIndex*/) override;

    void timerCallback(int) override;

    // moved to shaders/Presets.h
    //static juce::Array<ShaderPreset> getPresets();

    // -----------------------------------------------------------------------

    // AnimatedAppComponent

    const int TIMER_ANIMATION = 2;

    int fps = 60;

    void updateSync();

    Time lastUpdateTime = Time::getCurrentTime();
    int totalUpdates = 0;
    int framesPerSecond = 60;
    bool useVBlank = false;
    VBlankAttachment vBlankAttachment;

    // -----------------------------------------------------------------------

    // -----------------------------------------------------------------------

    // palette;
    // rainbow;
    // lookAndFeel;
    // apvts; parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShaderEditor)
};
