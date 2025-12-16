#include "ShaderEditor.h"

// ===========================================================================

ShaderEditor::ShaderEditor(PluginAudioProcessor &p)
    : juce::AudioProcessorEditor(&p), processor(p)
{
    setOpaque(true);

    if (auto *peer = getPeer())
        peer->setCurrentRenderingEngine(1);

    // --------------------------------
    // OpenGL
    // --------------------------------
    openGLContext.setOpenGLVersionRequired (OpenGLContext::openGL3_2);
    openGLContext.setSwapInterval(1);  // 1: VSync; 2: VSync / 2 (=half fps)
    openGLContext.setContinuousRepainting(true);  // should do the triggerRepaint
    openGLContext.setComponentPaintingEnabled(true);
    // openGLContext.setRenderer(this);  // must implement OpenGLRenderer
    openGLContext.attachTo(*this);

    // --------------------------------
    // statusLabel - shows shader compiler errors
    // --------------------------------
    addAndMakeVisible(statusLabel);
    statusLabel.setJustificationType(juce::Justification::topLeft);
    statusLabel.setFont(juce::FontOptions(14.0f));

    // --------------------------------
    // Presets Selector
    // --------------------------------
    auto presets = ShaderPresets::getPresets();

    for (int i = 0; i < presets.size(); ++i) {
        presetBox.addItem(presets[i].name, i + 1);
    }

    presetBox.setColour(juce::ComboBox::backgroundColourId, juce::Colours::transparentBlack);
    presetBox.setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(presetBox);
    presetBox.onChange = [this] { selectPreset(presetBox.getSelectedItemIndex()); };
    presetBox.setSelectedItemIndex(0);

    addAndMakeVisible(presetLabel);
    presetLabel.attachToComponent(&presetBox, true);

    // --------------------------------
    // Code Editor
    // --------------------------------
    codeEditorComponent.setOpaque(false);
    codeDocument.addListener(this);
    codeEditorComponent.setColour(juce::CodeEditorComponent::backgroundColourId, juce::Colours::transparentBlack);
    codeEditorComponent.setColour(juce::CodeEditorComponent::lineNumberBackgroundId, juce::Colours::transparentBlack);
    //codeEditorComponent.setColour(, juce::Colours::transparentBlack);
    codeEditorComponent.setScrollbarThickness(5);
    addAndMakeVisible(codeEditorComponent);

    // --------------------------------
    // GUI
    // --------------------------------
    uiOverlay = std::make_unique<UI>(this);
    addAndMakeVisible(*uiOverlay);
    //overlayUI->setBounds(getLocalBounds());

    // --------------------------------
    // init
    // --------------------------------
    setFramesPerSecond(fps);
    isConverted = false;
    u_startTime = juce::Time::getMillisecondCounterHiRes() * 0.001f;

    // addKeyListener(eventListener);
    // setWantsKeyboardFocus (true);
    // addMouseListener(eventListener);

    setSize(500, 500);
    setResizable(true, true);
}

ShaderEditor::~ShaderEditor() {
    openGLContext.detach();
    shader.reset();
}

// ===========================================================================

void ShaderEditor::paint(juce::Graphics &g) {

    //g.fillAll(juce::Colours::black);

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
            //g.fillCheckerBoard(getLocalBounds().toFloat(), 48.0f, 48.0f, juce::Colours::black, juce::Colours::black);

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
        // uniform vec4      iDate;                 // (year, month, day, time in seconds)
        // uniform float     iSampleRate;           // sound sample rate (i.e., 44100)

        // --------------------------------
        // TODO input channels (iChannel0..3 for each Buffer)
        // uniform float     iChannelTime[4];       // channel playback time (in seconds)
        // uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
        // uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube (sampler2D, sampler3D, samplerCube)

        // Textures (8x8 or 64x64 or 256x256 or 512x512 or 1024x1024 or 256x32, 1ch or 3ch or 4ch, uint8): 22 presets (bw, RGB, RGBA)
        // Cubemaps (64x64 or 256x256, 3ch, uint8): 6 presets
        // Volumes (32x32x32, 1ch, uint8 or 4ch, uint8): 2 presets
        // Videos (e.g. 640x320@29fps, 3ch, uint8, 29s length): 4 presets
        // Music (e.g. 44100 Hz, 2ch, sint16, 452s length): 7 presets
        // Misc:
        // Keyboard (256x3, 1ch, int8)
        // Webcam (1280x720, 4ch, int8, sRGB)
        // Microphone (512x2, 1ch, int8)
        // Soundcloud (512x2, 1ch int8): takes a URL
        // Buffer_A..D (viewport resolution, 4ch, float32, linear)
        // Cubemap_A (1024x1024, 4ch, float16, linear)

        // --------------------------------
        // ShaderToy
        // @see docs/shaders/demos/shadertoy/README.md  <==============
        // @see Editor Help (? in the bottom left)
        // https://www.shadertoy.com/howto

        // vertex shader:   ?
        // Shader Inputs:   uniform <type> <identifier>;

        // Code Buffers (3688 chars):
        // Image:           void mainImage(out vec4 fragColor, in vec2 fragCoord);
        // Common:          vec4 someFunction(vec4 a, float b);
        // Buffer A..D:     void mainImage(out vec4 fragColor, in vec2 fragCoord);
        // Cube A:          void mainCubemap(out vec4 fragColor, in vec2 fragCoord, in vec3 rayOri, in vec3 rayDir);
        // Sound:           vec2 mainSound(int samp, float time);

        // iChannel0..3 for each Buffer

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
    uiOverlay->setBounds(getLocalBounds());
}

// ===========================================================================

void ShaderEditor::selectPreset(int preset) {
    codeDocument.replaceAllContent(ShaderPresets::getPresets()[preset].fragmentShader);
    startTimer(TIMER_DOCUMENT_CHANGED, 1);
}

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

        ////////////////////////////////////
        repaint();
        //openGLContext.triggerRepaint();
        ////////////////////////////////////

        lastUpdateTime = Time::getCurrentTime();
    }
}

// ---------------------------------------------------------------------------

// AnimatedAppComponent
// https://juce.com/tutorials/tutorial_animation/
// https://docs.juce.com/master/classjuce_1_1AnimatedAppComponent.html
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

/**
 * Convert GLSL fragment shader code from other sources to run in JUCE
 * @param originalShaderCode
 * @return converted shaderCode
 */
juce::String ShaderEditor::convert(const juce::String &originalShaderCode) {

    juce::String juceShader;

    // --------------------------------

    // add Uniform Declarations (do it just once)
    if (!originalShaderCode.contains("// JUCE Uniforms")) {
        isConverted = true;

        // Add JUCE-compatible uniforms header:
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

        // OpenGL Uniforms:
        // https://learnopengl.com/Getting-started/Shaders+
        // https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
        // https://wikis.khronos.org/opengl/Uniform_(GLSL)

        // gl_Position
        // gl_FragCoord
        // gl_FragColor

        // --------------------------------

        // JUCE Uniforms:

        // --- juce_OpenGLGraphicsContext.cpp ---
        // varying vec2 pixelPos;
        // #define pixelAlpha frontColour.a

        // attribute vec2 position;
        // attribute vec4 colour;
        // uniform vec4 screenBounds;
        // varying vec4 frontColour;

        // varying vec2 texturePos;
        // vec2 adjustedPos
        // vec2 scaledPos
        // uniform sampler2D maskTexture;
        // uniform ivec4 maskBounds;
        // uniform float matrix[6];
        // uniform sampler2D gradientTexture;
        // uniform vec4 gradientInfo;
        // gradientPos
        // uniform sampler2D imageTexture;
        // uniform vec2 imageLimits;

        // --- juce_OpenGLHelpers.cpp  ---
        // if (getOpenGLVersion() >= Version (3, 2))
        // --- OpenGLHelpers::translateVertexShaderToV3 ---
        // #if JUCE_ANDROID
        // #else
        // code.replace ("attribute", "in");
        // output.replace ("varying", "out");
        // --- OpenGLHelpers::translateFragmentShaderToV3 ---
        // out vec4 fragColor;
        // code.replace ("varying", "in")
        // code.replace ("texture2D", "texture")
        // code.replace ("gl_FragColor", "fragColor");

        // --- OpenGLHelpers::getGLSLVersionString() ---
        // if (getOpenGLVersion() >= Version (3, 2))
        // { #if JUCE_OPENGL_ES return "#version 300 es"; #else return "#version 150"; }
        // else { return "#version 110"; }

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

        // p5.js (Processing)
        // https://p5js.org/tutorials/intro-to-shaders/

        // attribute vec3 aPosition;
        // attribute vec2 aTexCoord;
        // attribute vec4 aVertexColor;
        //
        // uniform mat4 uModelViewMatrix;
        // uniform mat4 uProjectionMatrix;
        // varying vec2 vTexCoord;
        // varying vec4 vVertexColor;

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
    juceShader += originalShaderCode;

    // --------------------------------

    // Check if it's a ShaderToy shader (has mainImage)
    if (originalShaderCode.contains("mainImage")
        && !originalShaderCode.contains("main()")) {
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

// ---------------------------------------------------------------------------

void ShaderEditor::toggleFullscreen() {

    isFullscreen = !isFullscreen;

    getPeer()->setFullScreen(isFullscreen);

    //if (isFullscreen) {}

    // --------------------------------

    // ResizableWindow::
    // getPeer()->setFullScreen(true);
    // getPeer()->setTitleBarHeight(0);

    // Desktop::
    // Desktop::getInstance().setKioskModeComponent(getTopLevelComponent(), false);
}



// ===========================================================================

// Event Listener, Action Listener, Mouse Listener, Key Listener; MVC: registerListener(), notify()

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
        //uiOverlay->showMenu();
        //uiOverlay->menu.showMenuAsync (PopupMenu::Options{}.withMousePosition());
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
