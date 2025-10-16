#include "ShaderEditor.h"

ShaderEditor::ShaderEditor(PluginAudioProcessor& p)
    : juce::AudioProcessorEditor(&p), processor(p)
{
    setOpaque(true);
    if (auto* peer = getPeer())
        peer->setCurrentRenderingEngine(0);

    openGLContext.attachTo(*getTopLevelComponent());

    addAndMakeVisible(statusLabel);
    statusLabel.setJustificationType(juce::Justification::topLeft);
    statusLabel.setFont(juce::FontOptions (14.0f));

    auto presets = getPresets();

    for (int i = 0; i < presets.size(); ++i)
        presetBox.addItem(presets[i].name, i + 1);

    addAndMakeVisible(presetLabel);
    presetLabel.attachToComponent(&presetBox, true);

    addAndMakeVisible(presetBox);
    presetBox.onChange = [this] { selectPreset(presetBox.getSelectedItemIndex()); };

    fragmentEditorComp.setOpaque(false);
    fragmentDocument.addListener(this);
    addAndMakeVisible(fragmentEditorComp);

    presetBox.setSelectedItemIndex(0);

    setSize(500, 500);

    // fi: ShaderToy Compatibility Code
    startTime = juce::Time::getMillisecondCounterHiRes() * 0.001;
}

ShaderEditor::~ShaderEditor()
{
    openGLContext.detach();
    shader.reset();
}

void ShaderEditor::paint(juce::Graphics& g)
{
    g.fillCheckerBoard(getLocalBounds().toFloat(), 48.0f, 48.0f, juce::Colours::lightgrey, juce::Colours::white);
    //g.fillCheckerBoard (getLocalBounds().toFloat(), 48.0f, 48.0f, juce::Colours::black, juce::Colours::black);


    if (shader.get() == nullptr || shader->getFragmentShaderCode() != fragmentCode)
    {
        shader.reset();

        if (fragmentCode.isNotEmpty())
        {
            shader.reset(new juce::OpenGLGraphicsContextCustomShader(fragmentCode));

            auto result = shader->checkCompilation(g.getInternalContext());

            if (result.failed())
            {
                statusLabel.setText (result.getErrorMessage(), juce::NotificationType::dontSendNotification);
                DBG("Shader compilation error: " + result.getErrorMessage());  // ADD THIS LINE
                shader.reset();
            }
        }
    }

    if (shader.get() != nullptr)
    {
        statusLabel.setText ({}, juce::NotificationType::dontSendNotification);

        // fi: begin of ShaderToy Compatibility Code
        // Set ShaderToy-compatible uniforms
        auto& glContext = g.getInternalContext();

        if (auto* shaderProgram = shader->getProgram(glContext))
        {
            shaderProgram->use();

            // Setting Uniform Values
            //if (shaderProgram->getUniformIDFromName("iResolution") >= 0) {
                shaderProgram->setUniform("iResolution", (float)getWidth(), (float)getHeight(), 1.0f);  //  500.0f, 500.0f
                DBG("iResolution = " + std::to_string(getWidth()) +  ", " + std::to_string(getHeight()) + ", 1.0f");
            //}
            if (shaderProgram->getUniformIDFromName("iTime") >= 0)
                shaderProgram->setUniform("iTime", (float) (juce::Time::getMillisecondCounterHiRes() * 0.001));  //  - startTime (?)
            if (shaderProgram->getUniformIDFromName("iMouse") >= 0)
                shaderProgram->setUniform("iMouse", 0.0f, 0.0f, 0.0f, 0.0f);
            if (shaderProgram->getUniformIDFromName("iFrame") >= 0)
                shaderProgram->setUniform("iFrame", frameCounter++);

            DBG("set uniforms");
        }
        // end of ShaderToy Compatibility Code
        
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
    fragmentEditorComp.setBounds(area);
}

void ShaderEditor::selectPreset(int preset) {
    //fragmentDocument.replaceAllContent (getPresets()[preset].fragmentShader);
    // fi: ShaderToy Compatibility
    fragmentDocument.replaceAllContent(wrapWithUniforms(getPresets()[preset].fragmentShader));
    startTimer(1);
}

juce::Array<ShaderEditor::ShaderPreset> ShaderEditor::getPresets()
{
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

        {
            "R-String",
            JUCE_MEDIUMP
            R"(
            void main()
            {
                vec4 colour1 = vec4 (1.0, 0.4, 0.6, 1.0);
                vec4 colour2 = vec4 (0.0, 0.8, 0.6, 1.0);
                float alpha = pixelPos.x / 1000.0;
                gl_FragColor = pixelAlpha * mix (colour1, colour2, alpha);
            }
            )"
        },

        // ---------------------------------------------------------------------------

        {
            "ShaderToy Tutorial",
            JUCE_MEDIUMP
            R"(/* https://www.shadertoy.com/view/mtyGWy */

// uniform vec3      iResolution;           // viewport resolution (in pixels)
// uniform float     iTime;                 // shader playback time (in seconds)
// uniform float     iTimeDelta;            // render time (in seconds)
uniform float     iFrameRate;            // shader frame rate
// uniform int       iFrame;                // shader playback frame
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
// uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
// uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube
uniform vec4      iDate;                 // (year, month, day, time in seconds)
uniform float     iSampleRate;           // sound sample rate (i.e., 44100)

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
            "ShaderToy - Plasma",
            JUCE_MEDIUMP
            "void mainImage(out vec4 fragColor, in vec2 fragCoord)\n"
            "{\n"
            "    " JUCE_MEDIUMP "vec2 uv = fragCoord / iResolution.xy;\n"
            "    " JUCE_MEDIUMP "vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0,2,4));\n"
            "    fragColor = vec4(col, 1.0);\n"
            "}\n"
            "\n"
        } //, {/*name*/, /*fragmentShader_as_string*/} //, {}

        // ---------------------------------------------------------------------------

    };  // end presets[]
    
    return juce::Array<ShaderPreset>(presets, numElementsInArray(presets));
}  // end getPresets()

// ---------------------------------------------------------------------------

juce::String ShaderEditor::convertShaderToyToJUCE(const juce::String& shaderToyCode)
{
    juce::String juceShader;
    
    // Add JUCE-compatible uniforms header
    juceShader += "// Converted from ShaderToy\n\n";
    juceShader += "uniform " JUCE_MEDIUMP "vec3 iResolution;\n";
    juceShader += "uniform " JUCE_MEDIUMP "float iTime;\n";
    juceShader += "uniform " JUCE_MEDIUMP "vec4 iMouse;\n";
    juceShader += "uniform " JUCE_MEDIUMP "float iTimeDelta;\n";
    juceShader += "uniform " JUCE_MEDIUMP "int iFrame;\n\n";
    
    // Add the ShaderToy code (keep mainImage function)
    juceShader += shaderToyCode;
    juceShader += "\n\n";
    
    // Add JUCE main() wrapper
    juceShader += "void main()\n";
    juceShader += "{\n";
    juceShader += "    " JUCE_MEDIUMP "vec4 fragColor;\n";
    juceShader += "    mainImage(fragColor, pixelPos);\n";
    juceShader += "    gl_FragColor = pixelAlpha * fragColor;\n";
    juceShader += "}\n";
    
    return juceShader;
}

juce::String ShaderEditor::wrapWithUniforms(const juce::String& shaderCode)
{
    // Check if it's already a ShaderToy shader (has mainImage)
    if (shaderCode.contains("mainImage"))
    {
        return convertShaderToyToJUCE(shaderCode);
    }
    
    // Otherwise assume it's already JUCE-compatible
    return shaderCode;
}
