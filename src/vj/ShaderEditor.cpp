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

    auto presets = getPresets();

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
}

// ===========================================================================

void ShaderEditor::paint(juce::Graphics &g) {
    //g.fillCheckerBoard(getLocalBounds().toFloat(), 48.0f, 48.0f, juce::Colours::lightgrey, juce::Colours::white);
    g.fillCheckerBoard(getLocalBounds().toFloat(), 48.0f, 48.0f, juce::Colours::black, juce::Colours::black);

    // TODO hide uniforms ?: add them to the shader, but dont display them in the codeEditor / shaderCode (String)

    // no shader set OR new shader code in editor
    if (shader == nullptr || shader->getFragmentShaderCode() != shaderCode) {
        shader.reset();

        if (shaderCode.isNotEmpty()) {
            // create shader
            shader.reset(new juce::OpenGLGraphicsContextCustomShader(shaderCode));

            auto result = shader->checkCompilation(g.getInternalContext());

            if (result.failed()) {
                // compilation failed
                statusLabel.setText(result.getErrorMessage(), juce::NotificationType::dontSendNotification);
                DBG("Shader compilation error: " + result.getErrorMessage());
                shader.reset();
            }
        }
    }

    // -----------------------------------------------------------------------

    if (shader != nullptr) {
        statusLabel.setText({}, juce::NotificationType::dontSendNotification);

        // -------------------------------------------------------------------

        if (auto *shaderProgram = shader->getProgram(g.getInternalContext())) {
            shaderProgram->use();

            // -------------------------------------------------------------------

            // Set Uniforms:

            DBG("GLSL version: " + juce::OpenGLHelpers::getGLSLVersionString());
            DBG("Uniforms set in paint():");

            // uniform vec3      iResolution;           // viewport resolution (in pixels)
            //if (shaderProgram->getUniformIDFromName("iResolution") >= 0) {
            shaderProgram->setUniform("iResolution", (float) getWidth(), (float) getHeight(), 1.0f);
            DBG("iResolution = " + std::to_string(getWidth()) + ", " + std::to_string(getHeight()) + ", 1.0f");
            //}

            // uniform float     iTime;                 // shader playback time (in seconds)
            shaderProgram->setUniform("iTime", (float) (juce::Time::getMillisecondCounterHiRes() * 0.001f - u_startTime));
            DBG("iTime = " + std::to_string(juce::Time::getMillisecondCounterHiRes() * 0.001f - u_startTime));

            // TODO uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
            shaderProgram->setUniform("iMouse", (float)u_mouseX, (float)u_mouseY, (float)u_mouseZ, (float)u_mouseW);
            DBG("iMouse: ");

            // uniform int       iFrame;                // shader playback frame
            shaderProgram->setUniform("iFrame", u_frameCounter++);
            DBG("iFrame = " + std::to_string(u_frameCounter));

            // TODO uniforms
            // uniform float     iTimeDelta;            // render time (in seconds)
            // uniform float     iFrameRate;            // shader frame rate
            // uniform float     iChannelTime[4];       // channel playback time (in seconds)
            // uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
            // uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube
            // uniform vec4      iDate;                 // (year, month, day, time in seconds)
            // uniform float     iSampleRate;           // sound sample rate (i.e., 44100)

            // -------------------------------------------------------------------
        }

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

// ===========================================================================

void ShaderEditor::selectPreset(int preset) {
    codeDocument.replaceAllContent(getPresets()[preset].fragmentShader);
    startTimer(TIMER_DOCUMENT_CHANGED, 1);
}

juce::Array<ShaderEditor::ShaderPreset> ShaderEditor::getPresets() {
#define SHADER_2DDEMO_HEADER \
    "/*  This demo shows the use of the OpenGLGraphicsContextCustomShader,\n" \
    "    which allows a 2D area to be filled using a GL shader program.\n" \
    "\n" \
    "    Edit the shader program below and it will be \n" \
    "    recompiled in real-time!\n" \
    "*/\n\n"

    ShaderPreset presets[] =
    {
        {
            "Simple Gradient",

            SHADER_2DDEMO_HEADER
            "void main()\n"
            "{\n"
            "    " JUCE_MEDIUMP " vec4 colour1 = vec4 (1.0, 0.4, 0.6, 1.0);\n"
            "    " JUCE_MEDIUMP " vec4 colour2 = vec4 (0.0, 0.8, 0.6, 1.0);\n"
            "    " JUCE_MEDIUMP " float alpha = pixelPos.x / 1000.0;\n"
            "    gl_FragColor = pixelAlpha * mix (colour1, colour2, alpha);\n"
            "}\n"
        },

        {
            "Circular Gradient",

            SHADER_2DDEMO_HEADER
            "void main()\n"
            "{\n"
            "    " JUCE_MEDIUMP " vec4 colour1 = vec4 (1.0, 0.4, 0.6, 1.0);\n"
            "    " JUCE_MEDIUMP " vec4 colour2 = vec4 (0.3, 0.4, 0.4, 1.0);\n"
            "    " JUCE_MEDIUMP " float alpha = distance (pixelPos, vec2 (600.0, 500.0)) / 400.0;\n"
            "    gl_FragColor = pixelAlpha * mix (colour1, colour2, alpha);\n"
            "}\n"
        },

        // ---------------------------------------------------------------------------

        {
            "ShaderToy - Plasma",

            "void mainImage(out vec4 fragColor, in vec2 fragCoord)\n"
            "{\n"
#if JUCER_OPENGL_ES
            "    " JUCE_MEDIUMP " vec2 uv = fragCoord / iResolution.xy;\n"
            "    " JUCE_MEDIUMP " vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0,2,4));\n"
#else
            "    vec2 uv = fragCoord / iResolution.xy;\n"
            "    vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0,2,4));\n"
#endif
            "    fragColor = vec4(col, 1.0);\n"
            "}\n"
            "\n"
        },

        // ---------------------------------------------------------------------------

        {
            "ShaderToy Tutorial",

            R"(/* https://www.shadertoy.com/view/mtyGWy */

vec3 palette( float t ) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263,0.416,0.557);

    return a + b*cos( 6.28318*(c*t+d) );
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);

    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;
        float d = length(uv) * exp(-length(uv0));
        vec3 col = palette(length(uv0) + i*.4 + iTime*.4);

        d = sin(d*8. + iTime)/8.;
        d = abs(d);
        d = pow(0.01 / d, 1.2);
        finalColor += col * d;
    }
    fragColor = vec4(finalColor, 1.0);
}
            )"
        },

        // ---------------------------------------------------------------------------

        {
            "Raymarching Tutorial",

            R"(// This scene is taken from my second tutorial about shader coding,
// which introduces the concept of raymarching as well as some useful
// transforms and space-bending techniques.
//
//     Mouse interactive!
//                            Video URL: https://youtu.be/khblXafu7iA

// 2D rotation function
mat2 rot2D(float a) {
    return mat2(cos(a), -sin(a), sin(a), cos(a));
}

// Custom gradient - https://iquilezles.org/articles/palettes/
vec3 palette(float t) {
    return .5+.5*cos(6.28318*(t+vec3(.3,.416,.557)));
}

// Octahedron SDF - https://iquilezles.org/articles/distfunctions/
float sdOctahedron(vec3 p, float s) {
    p = abs(p);
    return (p.x+p.y+p.z-s)*0.57735027;
}

// Scene distance
float map(vec3 p) {
    p.z += iTime * .4; // Forward movement

    // Space repetition
    p.xy = fract(p.xy) - .5;     // spacing: 1
    p.z =  mod(p.z, .25) - .125; // spacing: .25

    return sdOctahedron(p, .15); // Octahedron
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    vec2 uv = (fragCoord * 2. - iResolution.xy) / iResolution.y;
    vec2  m = (iMouse.xy * 2. - iResolution.xy) / iResolution.y;

    // Default circular motion if mouse not clicked
    if (iMouse.z <= 0.) m = vec2(cos(iTime*.2), sin(iTime*.2));

    // Initialization
    vec3 ro = vec3(0, 0, -3);         // ray origin
    vec3 rd = normalize(vec3(uv, 1)); // ray direction
    vec3 col = vec3(0);               // final pixel color

    float t = 0.; // total distance travelled

    int i; // Raymarching
    for (i = 0; i < 80; i++) {
        vec3 p = ro + rd * t; // position along the ray

        p.xy *= rot2D(t*.15 * m.x);     // rotate ray around z-axis

        p.y += sin(t*(m.y+1.)*.5)*.35;  // wiggle ray

        float d = map(p);     // current distance to the scene

        t += d;               // "march" the ray

        if (d < .001 || t > 100.) break; // early stop
    }

    // Coloring
    col = palette(t*.04 + float(i)*.005);

    fragColor = vec4(col, 1);
}
)"
        },

        // ---------------------------------------------------------------------------

        {
            "Print Text in Shaders",

            "// to be done!" //examples.getExample(1)
        }

        // ---------------------------------------------------------------------------

    }; // end presets[]

    return juce::Array<ShaderPreset>(presets, numElementsInArray(presets));
} // end getPresets()

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
        juceShader += "// JUCE Uniforms\n";
        juceShader += "uniform " JUCE_MEDIUMP " vec3  iResolution;\n";
        juceShader += "uniform " JUCE_MEDIUMP " float iTime;\n";
        juceShader += "uniform " JUCE_MEDIUMP " vec4  iMouse;\n";
        juceShader += "uniform " JUCE_MEDIUMP " float iTimeDelta;\n";
        juceShader += "uniform " JUCE_MEDIUMP " int   iFrame;\n\n";

        // ShaderToy Uniforms
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

        // ISF Uniforms
        // to be done

        // --------------------------------
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
        //juceShader += "    " JUCE_MEDIUMP " vec4 fragColor;\n";  // this caused error (black screen)
        juceShader += "    mainImage(fragColor, pos);\n";
        juceShader += "    gl_FragColor = pixelAlpha * fragColor;\n";
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
// https://docs.juce.com/master/classjuce_1_1MouseListener.html
// https://docs.juce.com/master/classjuce_1_1MouseEvent.html

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
