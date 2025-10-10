//
// Created by thorsten on 10.10.2025.
//

#include <JuceHeader.h>

// --- Helper class to handle Shader compilation and rendering ---
class ShaderRenderer : public juce::Component,
                       public juce::OpenGLRenderer,
                       public juce::Timer
{
public:
    ShaderRenderer()
    {
        // Must enable the OpenGL context for this component
        openGLContext.set
(this);
        openGLContext.setContinuousRepainting(false); // We use timer for repaint
        // Start the timer to trigger continuous repainting for animation
        startTimerHz(60);
        startTime = juce::Time::getMillisecondCounterHiRes() * 0.001;
    }

    ~ShaderRenderer() override
    {
        stopTimer();
        openGLContext.set
(nullptr);
    }

    // Pass new GLSL code from the TextEditor
    void setShaderCode(const juce::String& newCode)
    {
        // Only recompile if the code has actually changed
        if (newCode != currentShaderCode)
        {
            currentShaderCode = newCode;
            compileShader();

            // Reset time when the shader changes, so the animation starts fresh
            startTime = juce::Time::getMillisecondCounterHiRes() * 0.001;
        }
    }

    // Called by the timer to trigger a new frame
    void timerCallback() override
    {
        if (isShaderReady)
            openGLContext.triggerRepaint();
    }

    void paint(juce::Graphics& g) override
    {
        // This is primarily for drawing the error message if compilation fails
        if (!isShaderReady)
        {
            g.fillAll(juce::Colours::black);
            g.setColour(juce::Colours::red);
            g.setFont(18.0f);
            g.drawText("SHADER KOMPILIERFEHLER!\n" + lastCompileError, getLocalBounds().reduced(20), juce::Justification::centred);
        }
    }

    // --- OpenGLRenderer implementation ---

    void newOpenGLContextCreated() override
    {
        // Compile the default/current shader when the context is created
        compileShader();
    }

    void renderOpenGL() override
    {
        jassert(isShaderReady);
        if (!isShaderReady) return;

        juce::OpenGLContext::ScopedSaveAndRestore appliedState(openGLContext);

        // 1. Clear the viewport
        juce::gl::glClear(juce::gl::GL_COLOR_BUFFER_BIT | juce::gl::GL_DEPTH_BUFFER_BIT);

        // 2. Use the compiled shader program
        shaderProgram->use();

        // 3. Set the uniforms
        float iTime = (float)(juce::Time::getMillisecondCounterHiRes() * 0.001 - startTime);

        // iTime (Animation time in seconds)
        if (auto* timeUniform = shaderProgram->get </span ></ code > Uniform("iTime"))
            timeUniform->set((float)iTime);

        // iResolution (Viewport size)
        if (auto* resolutionUniform = shaderProgram->get </span ></ code > Uniform("iResolution"))
            resolutionUniform->set((float)getWidth(), (float)getHeight());

        // iMouse (Mocked mouse position - not implemented for simplicity, but available)
        if (auto* mouseUniform = shaderProgram->get </span ></ code > Uniform("iMouse"))
            mouseUniform->set(0.0f, 0.0f, 0.0f, 0.0f);

        // 4. Draw the fullscreen quad
        if (screenQuad == nullptr)
            screenQuad.reset(new ScreenQuad());

        screenQuad->draw(openGLContext, *shaderProgram);

        // 5. Check for GL errors
        openGLContext.checkError("Error in renderOpenGL");
    }

    void freeOpenGLContext() override
    {
        // Cleanup resources
        shaderProgram.reset();
        screenQuad.reset();
        isShaderReady = false;
    }

    juce::String getLastError() const { return lastCompileError; }

private:
    juce::OpenGLContext openGLContext;
    std::unique_ptr<juce::OpenGLShaderProgram> shaderProgram;
    juce::String currentShaderCode;
    juce::String lastCompileError;
    double startTime = 0.0;
    bool isShaderReady = false;

    // A helper class to draw a full-screen quad (2 triangles)
    class ScreenQuad
    {
    public:
        ScreenQuad()
        {
            // Fullscreen Quad vertices: positions for a square covering [-1, 1]
            float vertices[] = {
                -1.0f, -1.0f, 0.0f, 1.0f, // Bottom-left
                 1.0f, -1.0f, 1.0f, 1.0f, // Bottom-right
                -1.0f,  1.0f, 0.0f, 0.0f, // Top-left
                 1.0f,  1.0f, 1.0f, 0.0f  // Top-right
            };

            // Set up buffer with 4 vertices, each having 4 floats (x, y, u, v)
            vbo.loadData(vertices, 4 * 4 * sizeof(float));
        }

        void draw(juce::OpenGLContext& context, juce::OpenGLShaderProgram& shader)
        {
            // Bind the vertex buffer
            vbo.bind();

            // Setup the position attribute (x, y)
            if (auto* attribute = shader.get < / span ></ code > Attribute("position"))
            {
                juce::gl::glVertexAttribPointer(attribute->getLocation(), 2, juce::gl::GL_FLOAT, juce::gl::GL_FALSE, 4 * sizeof(float), 0);
                juce::gl::glEnableVertexAttribArray(attribute->getLocation());
            }

            // Setup the UV coordinates (u, v) - not strictly needed for Shadertoy, but good practice
            if (auto* textureCoordIn = shader.get < / span ></ code > Attribute("textureCoordIn"))
            {
                juce::gl::glVertexAttribPointer(textureCoordIn->getLocation(), 2, juce::gl::GL_FLOAT, juce::gl::GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
                juce::gl::glEnableVertexAttribArray(textureCoordIn->getLocation());
            }

            // Draw the quad as a triangle strip
            juce::gl::glDrawArrays(juce::gl::GL_TRIANGLE_STRIP, 0, 4);

            // Cleanup attributes
            if (auto* attribute = shader.get < / span ></ code > Attribute("position"))
                juce::gl::glDisableVertexAttribArray(attribute->getLocation());
            if (auto* textureCoordIn = shader.get < / span ></ code > Attribute("textureCoordIn"))
                juce::gl::glDisableVertexAttribArray(textureCoordIn->getLocation());
        }

    private:
        juce::OpenGLBuffer<float> vbo;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScreenQuad)
    };

    std::unique_ptr<ScreenQuad> screenQuad;

    // --- Core Shader Logic ---
    void compileShader()
    {
        // 1. Create the full GLSL fragment shader code
        juce::String completeFragmentShader = getFragmentShaderTemplate(currentShaderCode);

        // 2. Vertex Shader (Simple fullscreen quad setup)
        const char* vertexShader = R"glsl(
            attribute vec2 position;
            attribute vec2 textureCoordIn; // Required by JUCE helper classes
            varying vec2 textureCoordOut;
            void main()
            {
                textureCoordOut = textureCoordIn;
                gl_Position = vec4(position, 0.0, 1.0);
            }
        )glsl";

        // 3. Attempt compilation
        if (openGLContext.is              ())
        {
            shaderProgram.reset();
            isShaderReady = false;

            try
            {
                shaderProgram.reset(new juce::OpenGLShaderProgram(openGLContext));

                if (shaderProgram->addShader(juce::gl::GL_VERTEX_SHADER, vertexShader) &&
                    shaderProgram->addShader(juce::gl::GL_FRAGMENT_SHADER, completeFragmentShader) &&
                    shaderProgram->link())
                {
                    isShaderReady = true;
                    lastCompileError = "Kompilierung erfolgreich!";
                }
                else
                {
                    lastCompileError = shaderProgram->getLastError();
                    isShaderReady = false;
                }
            }
            catch (const juce::String& error)
            {
                lastCompileError = "Exception: " + error;
                isShaderReady = false;
            }
        }
        repaint(); // Show success or error message
    }

    // Wraps the user's Shadertoy 'mainImage' function into a full fragment shader
    juce::String getFragmentShaderTemplate(const juce::String& userCode)
    {
        // Shadertoy standard uniforms: iResolution, iTime, iMouse (only iResolution and iTime used here)
        juce::String shaderTemplate = R"glsl(
            // Set required GLSL version and precision
            #version 330 core
            precision highp float;

            // Shadertoy standard uniforms
            uniform vec2 iResolution;
            uniform float iTime;
            uniform vec4 iMouse;

            // Output color
            out vec4 fragColor;

            // Shadertoy mainImage function signature
            void mainImage(out vec4 fragColor, in vec2 fragCoord);

            // --- User Code from TextEditor is inserted here ---
        )glsl";

        shaderTemplate += userCode;

        // Final wrapper to call mainImage
        shaderTemplate += R"glsl(
            // JUCE/OpenGL entry point
            void main()
            {
                // Call the user's mainImage function
                mainImage(fragColor, gl_FragCoord.xy);
            }
        )glsl";

        return shaderTemplate;
    }


    // The default shader code (a simple red/blue gradient)
    const juce::String defaultShaderCode = R"glsl(
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalisierte Koordinaten von 0 bis 1
    vec2 uv = fragCoord/iResolution.xy;

    // Zeitabhängiger Faktor
    float t = iTime * 0.5;

    // Rote Komponente: steigt von links nach rechts
    float r = uv.x;

    // Blaue Komponente: steigt von unten nach oben
    float b = uv.y;

    // Grüne Komponente: pulsierend über die Zeit
    float g = 0.5 + 0.5 * sin(uv.x * 10.0 + t * 5.0);

    // Setze die Farbe
    fragColor = vec4(r, g, b, 1.0);
}
)glsl";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ShaderRenderer)
};

// --- PluginEditor Class ---

class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                         private juce::Button::Listener,
                                         private juce::TextEditor::Listener
{
public:
    AudioPluginAudioProcessorEditor (juce::AudioProcessor& p)
        : juce::AudioProcessorEditor (p),
          processor (p)
    {
        // 1. Shader Renderer
        addAndMakeVisible (shaderRenderer);

        // 2. Code Editor
        addAndMakeVisible (codeEditor);
        codeEditor.setText(shaderRenderer.defaultShaderCode);
        codeEditor.setMultiLine(true);
        codeEditor.addListener(this);
        codeEditor.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), 14.0f, juce::Font::plain));
        codeEditor.setReturnKeySendsText(false);
        codeEditor.setScrollbarThickness(12);

        // 3. Fullscreen Button
        addAndMakeVisible (fullscreenButton);
        fullscreenButton.setButtonText("Fullscreen-Modus (Toggle)");
        fullscreenButton.addListener(this);

        // 4. Initial setup
        shaderRenderer.setShaderCode(codeEditor.getText());
        setSize (800, 600);
    }

    ~AudioPluginAudioProcessorEditor() override
    {
        fullscreenButton.removeListener(this);
        codeEditor.removeListener(this);
    }

    void paint (juce::Graphics& g) override
    {
        // Background for the overall plugin editor
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    }

    void resized() override
    {
        juce::Rectangle<int> bounds = getLocalBounds();

        if (isFullscreen)
        {
            // Fullscreen: ShaderRenderer takes up the entire space
            shaderRenderer.setBounds(bounds);

            // Hide other components (only possible by moving them off-screen or setting size to zero)
            codeEditor.setBounds(0, 0, 0, 0);
            fullscreenButton.setBounds(bounds.reduced(10).withHeight(30).withY(bounds.getHeight() - 40));
            fullscreenButton.setAlpha(1.0f); // Make sure button is visible over shader
        }
        else
        {
            // Standard View: Split view for code and preview

            // Layout: 1/3 for code, 2/3 for preview
            int editorWidth = bounds.getWidth() / 3;
            juce::Rectangle<int> codeArea = bounds.removeFromLeft(editorWidth);

            // Code Editor at the top of the code area
            codeEditor.setBounds(codeArea.reduced(5).withTrimmedBottom(40));

            // Fullscreen button at the bottom of the code area
            fullscreenButton.setBounds(codeArea.withHeight(30).withY(codeArea.getHeight() - 35).reduced(5));

            // Shader Renderer takes the rest
            shaderRenderer.setBounds(bounds);

            fullscreenButton.setAlpha(1.0f); // Ensure button is visible
        }
    }

private:
    // --- Components ---
    ShaderRenderer shaderRenderer;
    juce::TextEditor codeEditor;
    juce::ToggleButton fullscreenButton;
    bool isFullscreen = false;

    // --- Listeners ---

    // 1. Button Listener for Fullscreen Toggle
    void buttonClicked (juce::Button* button) override
    {
        if (button == &fullscreenButton)
        {
            isFullscreen = fullscreenButton.getToggleState();

            // We force the component to relayout
            resized();

            // Since this is a plugin, true "OS fullscreen" is difficult.
            // We maximize the editor window size and hide other elements.
            if (juce::TopLevelWindow* tlw = findParentComponentOfClass<juce::TopLevelWindow>())
            {
                // In a host, the plugin window might not be a TopLevelWindow,
                // but if it is, this maximizes it.
                tlw->setFullScreen(isFullscreen);
                if (!isFullscreen)
                {
                    // Restore original size when exiting fullscreen
                    tlw->setSize(800, 600);
                    tlw->centreWithSize(800, 600);
                }
            }
        }
    }

    // 2. TextEditor Listener for Code Changes
    void textEditorTextChanged (juce::TextEditor& editor) override
    {
        if (editor == codeEditor)
        {
            shaderRenderer.setShaderCode(editor.getText());
        }
    }

    // --- Minimal PluginProcessor to satisfy the constructor requirement ---
    juce::AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};

// --- Minimal PluginProcessor implementation for context (assuming a basic JUCE project structure) ---
// This part is included just to show where the editor fits in.

class MyPluginProcessor  : public juce::AudioProcessor
{
public:
    MyPluginProcessor()
     : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
    {}

    // Basic required overrides
    void prepareToPlay (double, int) override {}
    void releaseResources() override {}
    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) override { buffer.clear();}

    // Plugin GUI creation
    juce::AudioProcessorEditor* createEditor() override { return new AudioPluginAudioProcessorEditor (*this); }
    bool hasEditor() const override { return true; }

    // State saving (minimal)
    const juce::String getName() const override { return "ShaderToy JUCER"; }
    void getStateInformation (juce::MemoryBlock& destData) override {}
    void setStateInformation (const void* data, int sizeInBytes) override {}

    // Other required overrides (not relevant for this task)
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override { return true; }
    double getTailLengthSeconds() const override { return 0.0; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int index) override {}
    const juce::String getProgramName (int index) override { return {}; }
    void changeProgramName (int index, const juce::String& newName) override {}
    bool isAAX () const { return false; }
    bool isVST3() const { return false; }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyPluginProcessor)
};

// JUCE macro to create the processor instance
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyPluginProcessor();
}
