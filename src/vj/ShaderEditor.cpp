#include "ShaderEditor.h"

// ===========================================================================

ShaderEditor::ShaderEditor(PluginAudioProcessor &p)
    : juce::AudioProcessorEditor(&p), processor(p) {
    setOpaque(true);

    if (auto *peer = getPeer())
        peer->setCurrentRenderingEngine(1);

    //openGLContext.attachTo(*getTopLevelComponent());
    openGLContext.attachTo(*this);

    // --------------------------------

    // Presets Selector
    addAndMakeVisible(statusLabel);
    statusLabel.setJustificationType(juce::Justification::topLeft);
    statusLabel.setFont(juce::FontOptions(14.0f));

    auto presets = ShaderPresets::getPresets();

    for (int i = 0; i < presets.size(); ++i) {
        presetBox.addItem(presets[i].name, i + 1);
    }

    addAndMakeVisible(presetLabel);
    presetLabel.attachToComponent(&presetBox, true);

    addAndMakeVisible(presetBox);
    presetBox.onChange = [this] { selectPreset(presetBox.getSelectedItemIndex()); };

    // --------------------------------

    // Code Editor
    codeEditorComponent.setOpaque(false);
    codeDocument.addListener(this);
    addAndMakeVisible(codeEditorComponent);
    //codeEditorComponent.

    presetBox.setSelectedItemIndex(0);

    // --------------------------------

    // init
    setFramesPerSecond(fps);
    isConverted = false;
    u_startTime = juce::Time::getMillisecondCounterHiRes() * 0.001f;

    // GUI
    overlayUI = std::make_unique<UI>();
    addAndMakeVisible(*overlayUI);
    //overlayUI->setBounds(getLocalBounds());
    // catches all Mouse clicks !?

    // --------------------------------

    // Component (AudioProcessorEditor)
    setSize(500, 500);
    setResizable(true, true);
}

ShaderEditor::~ShaderEditor() {
    openGLContext.detach();
    shader.reset();
    delete shaderProgram;
}

// ===========================================================================

// OpenGL
// https://docs.juce.com/master/classes.html#letter_O
// https://docs.juce.com/master/classjuce_1_1OpenGLAppComponent.html
// https://docs.juce.com/master/classjuce_1_1OpenGLHelpers.html
// https://docs.juce.com/master/classjuce_1_1OpenGLContext.html
// https://docs.juce.com/master/classjuce_1_1OpenGLRenderer.html
// https://docs.juce.com/master/structjuce_1_1OpenGLGraphicsContextCustomShader.html
// https://docs.juce.com/master/classjuce_1_1OpenGLShaderProgram.html
// https://docs.juce.com/master/classjuce_1_1OpenGLFrameBuffer.html
// https://docs.juce.com/master/classjuce_1_1OpenGLTexture.html
// https://docs.juce.com/master/classjuce_1_1OpenGLImageType.html
// https://docs.juce.com/master/classjuce_1_1OpenGLPixelFormat.html

/*
juce::OpenGLContext openGLContext;
juce::String shaderCode;
std::unique_ptr<juce::OpenGLGraphicsContextCustomShader> shader;
juce::OpenGLShaderProgram* shaderProgram;

codeDocument.replaceAllContent(ShaderPresets::getPresets()[preset].fragmentShader);  // selectPreset()
shaderCode = convert(codeDocument.getAllContent());                                  // timerCallback()
codeDocument.replaceAllContent(shaderCode);

// paint(Graphics& g)
shader.reset(new juce::OpenGLGraphicsContextCustomShader(shaderCode));
auto result = shader->checkCompilation(g.getInternalContext());
shaderProgram = shader->getProgram(g.getInternalContext());
shaderProgram->use();

shaderProgram->setUniform("iResolution", (float) getWidth(), (float) getHeight(), 1.0f);
shader->fillRect(g.getInternalContext(), getLocalBounds());
 */

void ShaderEditor::paint(juce::Graphics &g) {

    // -----------------------------------------------------------------------
    // shader is not set OR new shader code in editor
    // -----------------------------------------------------------------------

    if (shader.get() == nullptr || shader->getFragmentShaderCode() != shaderCode) {
        shader.reset();

        if (shaderCode.isNotEmpty()) {
            // -----------------------------
            // create shader
            // -----------------------------
            shader.reset(new juce::OpenGLGraphicsContextCustomShader(shaderCode));

            auto result = shader->checkCompilation(g.getInternalContext());

            if (result.failed()) {
                // compilation failed
                statusLabel.setText(result.getErrorMessage(), juce::NotificationType::dontSendNotification);
                DBG("Shader compilation error: " + result.getErrorMessage());
                shader.reset();
            }

            // -----------------------------
            // do once (not @60 fps)
            // -----------------------------
            g.fillCheckerBoard(getLocalBounds().toFloat(), 48.0f, 48.0f, juce::Colours::black, juce::Colours::darkgrey);
            statusLabel.setText({}, juce::NotificationType::dontSendNotification);

            shaderProgram = shader->getProgram(g.getInternalContext());
            shaderProgram->use();
        }
    }

    // -----------------------------------------------------------------------
    // paint the shader
    // -----------------------------------------------------------------------

    if (shader.get() != nullptr) {

        // --------------------------------
        // Set Uniforms:
        // --------------------------------

        //DBG("GLSL version: " + juce::OpenGLHelpers::getGLSLVersionString());  // GLSL version: #version 150
        //DBG("Uniforms set in paint():");

        // uniform vec3      iResolution;           // viewport resolution (in pixels)
        //if (shaderProgram->getUniformIDFromName("iResolution") >= 0) {
        shaderProgram->setUniform("iResolution", (float) getWidth(), (float) getHeight(), 1.0f);
        //DBG("iResolution = " + std::to_string(getWidth()) + ", " + std::to_string(getHeight()) + ", 1.0f");
        //}

        // uniform float     iTime;                 // shader playback time (in seconds)
        shaderProgram->setUniform("iTime", (float) (juce::Time::getMillisecondCounterHiRes() * 0.001f - u_startTime));
        //DBG("iTime = " + std::to_string(juce::Time::getMillisecondCounterHiRes() * 0.001f - u_startTime));

        // uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
        shaderProgram->setUniform("iMouse", (float)u_mouseX, (float)u_mouseY, (float)u_mouseZ, (float)u_mouseW);
        //DBG("iMouse: X: " + std::to_string(u_mouseX) + ", Y: " + std::to_string(u_mouseY) + ", Z: " + std::to_string(u_mouseZ) + ", W: " + std::to_string(u_mouseW) );

        // uniform int       iFrame;                // shader playback frame
        shaderProgram->setUniform("iFrame", u_frameCounter++);
        //DBG("iFrame = " + std::to_string(u_frameCounter));

        // TODO uniforms
        // uniform float     iTimeDelta;            // render time (in seconds)
        // uniform float     iFrameRate;            // shader frame rate
        // uniform float     iChannelTime[4];       // channel playback time (in seconds)
        // uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
        // uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube
        // uniform vec4      iDate;                 // (year, month, day, time in seconds)
        // uniform float     iSampleRate;           // sound sample rate (i.e., 44100)

        // -------------------------------------------------------------------

        shader->fillRect(g.getInternalContext(), getLocalBounds());
    }
}

void ShaderEditor::resized() {
    auto area = getLocalBounds().reduced(4);

    statusLabel.setBounds(area.removeFromTop(75));

    area.removeFromTop(area.getHeight() / 2);

    auto presets = area.removeFromTop(25);
    presets.removeFromLeft(100);
    presetBox.setBounds(presets.removeFromLeft(150));

    area.removeFromTop(4);
    codeEditorComponent.setBounds(area);

    // to be done: smaller bounds: only header or footer
    overlayUI->setBounds(getLocalBounds());
}

void ShaderEditor::setFullscreen() {

    // code snippets:
    // ResizableWindow::setFullScreen()
    // Desktop::setKioskModeComponent
    // MainWnd->setFullScreen(true);
    // MainWnd->setTitleBarHeight(0);
    /*
    void MainComponent::onFullScreenModeItemTriggered()
    {
        getPeer()->setFullScreen(true);
        Desktop::getInstance().setKioskModeComponent(getTopLevelComponent(), false);
        // --- other source ---
        // https://juce.com/tutorials/tutorial_android_studio/
        setUsingNativeTitleBar (true);
        setContentOwned (new MainContentComponent(), true);
        setFullScreen (true); // set to fullscreen rather than call centreWithSize()
        setVisible (true);
    }
     */
}

// ===========================================================================

void ShaderEditor::selectPreset(int preset) {
    codeDocument.replaceAllContent(ShaderPresets::getPresets()[preset].fragmentShader);
    startTimer(TIMER_DOCUMENT_CHANGED, 1);
}

// ---------------------------------------------------------------------------

/**
 * Convert GLSL fragment shader code from other sources to run in JUCE
 * @param _shaderCode
 * @return converted shaderCode
 */
juce::String ShaderEditor::convert(const juce::String &_shaderCode) {

    juce::String juceShader;

    // add Uniforms (do it just once)
    if (!_shaderCode.contains("// JUCE Uniforms")) {
        isConverted = true;

        // Add JUCE-compatible uniforms header
        //juceShader += "#version 150\n";
        juceShader += "#ifdef GL_ES\nprecision mediump float;\n#endif\n\n";  // from Kodelife > Help > Examples > Templates > The Book of Shaders
        //juceShader += "out vec4 fragColor;\n\n";  // from Kodelife > Help > Examples > Templates > Shadertoy
        juceShader += "// JUCE Uniforms\n";
        juceShader += "uniform vec3  iResolution;\n";
        juceShader += "uniform float iTime;\n";
        juceShader += "uniform vec4  iMouse;\n";
        juceShader += "uniform float iTimeDelta;\n";
        juceShader += "uniform int   iFrame;\n\n";

        // ShaderToy Uniforms:
        // https://www.shadertoy.com/howto

        // uniform vec3      iResolution;           // viewport resolution (in pixels)
        // uniform float     iTime;                 // shader playback time (in seconds)
        // uniform float     iTimeDelta;            // render time (in seconds)
        // uniform float     iFrameRate;            // shader frame rate
        // uniform int       iFrame;                // shader playback frame
        // uniform float     iChannelTime[4];       // channel playback time (in seconds)
        // uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
        // uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
        // uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube
        // uniform vec4      iDate;                 // (year, month, day, time in seconds)
        // uniform float     iSampleRate;           // sound sample rate (i.e., 44100)

        // --------------------------------

        // The Book of Shaders Uniforms:
        // https://thebookofshaders.com/03/
        // https://github.com/patriciogonzalezvivo/ofxshader

        // uniform vec2 u_resolution;   // Canvas size (width,height) || viewport resolution (in pixels)
        // uniform vec2 u_mouse;        // mouse position in screen pixels || mouse pixel coords
        // uniform float u_time;        // Time in seconds since load || shader playback time (in seconds)

        // uniform float u_delta;       // delta time between frames (in seconds)
        // uniform vec4 u_date;         // year, month, day and seconds

        // --------------------------------

        // ISF Uniforms
        // https://docs.isf.video/quickstart.html#automatically-created-uniforms-and-variables-in-isf
        // https://docs.isf.video/ref_variables.html

        // isf_FragNormCoord    // which contains the normalized (0.0 to 1.0) coordinate
        // TIME
        // TIMEDELTA
        // FRAMEINDEX           // which can be used to animate compositions over time
        // RENDERSIZE           // which contains the pixel dimensions of the output being rendered
        // PASSINDEX
        // DATE
        // gl_FragCoord

        // --------------------------------

        // https://glslsandbox.com/
        // https://github.com/mrdoob/glsl-sandbox/blob/master/static/index.html

        // uniform float time;
        // uniform vec2 mouse;
        // uniform vec2 resolution;
        // uniform vec2 surfaceSize;
        // varying vec2 surfacePosition;
        // uniform sampler2D texture;
        // backbuffer

    }

    // after the uniforms are declared, add the original code
    juceShader += _shaderCode;

    // --------------------------------

    // Check if it's a ShaderToy shader (has mainImage)
    if (_shaderCode.contains("mainImage")
        && !_shaderCode.contains("main()")) {
        isConverted = true;

        // Add JUCE main() wrapper
        juceShader += "\n// ShaderToy compatibility\n";
        juceShader += "void main()\n";
        juceShader += "{\n";
        juceShader += "    vec2 pos = vec2(pixelPos.x, iResolution.y - pixelPos.y);  // flip y\n";
        juceShader += "    " JUCE_MEDIUMP " vec4 _fragColor;\n";  // this caused error (black screen)
        juceShader += "    mainImage(_fragColor, pos);\n";
        juceShader += "    gl_FragColor = pixelAlpha * _fragColor;\n";
        juceShader += "}\n";
    }
    // else if ()

    // --------------------------------

    return juceShader;
}

// ===========================================================================

void ShaderEditor::codeDocumentTextInserted(const juce::String & /* newText */, int /* insertIndex */) {
    startTimer(TIMER_DOCUMENT_CHANGED, shaderLinkDelay);
}

void ShaderEditor::codeDocumentTextDeleted(int /* startIndex */, int /* endIndex */) {
    startTimer(TIMER_DOCUMENT_CHANGED, shaderLinkDelay);
}

void ShaderEditor::timerCallback(int id) {
    if (id == TIMER_DOCUMENT_CHANGED) {
        // OpenGL 2D Demo App
        shaderCode = convert(codeDocument.getAllContent()); // <======== convert()
        if (isConverted) {
            // update the editor only, if the String was changed by convert()
            codeDocument.replaceAllContent(shaderCode);
            isConverted = false;
        }
        stopTimer(TIMER_DOCUMENT_CHANGED);
        repaint();
    } else if (id == TIMER_ANIMATION) {
        // AnimatedAppComponent
        ++totalUpdates;
        update();
        repaint();
        lastUpdateTime = Time::getCurrentTime();
    }
}

// ---------------------------------------------------------------------------

// AnimatedAppComponent
// juce_gui_extra/misc/juce_AnimatedAppComponent.h

// Timer | MultiTimer
// https://docs.juce.com/master/classjuce_1_1Timer.html

void ShaderEditor::setFramesPerSecond(int framesPerSecondIn) {
    jassert(0 < framesPerSecond && framesPerSecond < 1000);
    framesPerSecond = framesPerSecondIn;
    updateSync();
}

void ShaderEditor::updateSync() {
    if (useVBlank) {
        stopTimer(TIMER_ANIMATION);

        if (vBlankAttachment.isEmpty())
            vBlankAttachment = {this, [this] { timerCallback(TIMER_ANIMATION); }};
    } else {
        vBlankAttachment = {};

        const auto timerInterval = 1000 / framesPerSecond;

        if (getTimerInterval(TIMER_ANIMATION) != timerInterval)
            startTimer(TIMER_ANIMATION, timerInterval);
    }
}

void ShaderEditor::setSynchroniseToVBlank(bool syncToVBlank) {
    useVBlank = syncToVBlank;
    updateSync();
}

int ShaderEditor::getMillisecondsSinceLastUpdate() const noexcept {
    return (int) (Time::getCurrentTime() - lastUpdateTime).inMilliseconds();
}

void ShaderEditor::update() {
}

// ===========================================================================

// juce::MouseListener
// https://docs.juce.com/master/classjuce_1_1MouseEvent.html
// https://docs.juce.com/master/classjuce_1_1ModifierKeys.html (LMB, RMB)
// https://docs.juce.com/master/structjuce_1_1MouseWheelDetails.html
// https://docs.juce.com/master/classjuce_1_1MouseInputSource.html  (Muti-Touch)

void ShaderEditor::mouseEnter(const MouseEvent &event) {
    AudioProcessorEditor::mouseEnter(event);
}

void ShaderEditor::mouseExit(const MouseEvent &event) {
    AudioProcessorEditor::mouseExit(event);
}

void ShaderEditor::mouseMove(const MouseEvent &event) {
    AudioProcessorEditor::mouseMove(event);
}

void ShaderEditor::mouseDown(const MouseEvent &event) {
    u_mouseX = event.getMouseDownX();
    u_mouseY = event.getMouseDownY();
    u_mouseZ = 1;  // LMB clicked

    // RMB
    //const auto& modifiers = ModifierKeys::getCurrentModifiers();
    if (ModifierKeys::getCurrentModifiers().isRightButtonDown()) {
        // show menu
    }

    AudioProcessorEditor::mouseDown(event);
}

void ShaderEditor::mouseUp(const MouseEvent &event) {
    u_mouseX = event.x;
    u_mouseY = event.y;
    u_mouseZ = 1;  // LMB clicked

    AudioProcessorEditor::mouseUp(event);
}

void ShaderEditor::mouseDrag(const MouseEvent &event) {
    u_mouseX = event.x;
    u_mouseY = event.y;
    u_mouseZ = 1;  // LMB clicked

    AudioProcessorEditor::mouseDrag(event);
}

void ShaderEditor::mouseDoubleClick(const MouseEvent &event) {
    AudioProcessorEditor::mouseDoubleClick(event);
}

void ShaderEditor::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    AudioProcessorEditor::mouseWheelMove(event, wheel);
}

void ShaderEditor::mouseMagnify(const MouseEvent &event, float scaleFactor) {
    AudioProcessorEditor::mouseMagnify(event, scaleFactor);
}

// -----------------------------------------------------------------------

// juce::KeyListener
// https://docs.juce.com/master/classjuce_1_1KeyListener.html
// https://docs.juce.com/master/classjuce_1_1KeyPress.html
// https://docs.juce.com/master/classjuce_1_1ModifierKeys.html

// keyPressed is called from the ComponentPeer (the actual OS window)
// keyPressed requires that you setWantsKeyboardFocus(true) on the component
// or manually grab focus with grabKeyboardFocus
// https://melatonin.dev/blog/juce-component-mouse-and-keyboard/

bool ShaderEditor::keyPressed(const KeyPress &key) {
    return AudioProcessorEditor::keyPressed(key);
}

bool ShaderEditor::keyStateChanged(bool isKeyDown) {
    return AudioProcessorEditor::keyStateChanged(isKeyDown);
}

void ShaderEditor::modifierKeysChanged(const ModifierKeys &modifiers) {
    AudioProcessorEditor::modifierKeysChanged(modifiers);
}

// ===========================================================================
