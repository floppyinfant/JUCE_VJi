//
// based on medium.com
// https://medium.com/@Im_Jimmi/using-opengl-for-2d-graphics-in-a-juce-plug-in-24aa82f634ff
//

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include <juce_opengl/juce_opengl.h>

class OpenGLComponent : public juce::Component,
                        public juce::OpenGLRenderer
{
public:
    OpenGLComponent();
    ~OpenGLComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;

private:

    juce::OpenGLContext openGLContext;

    struct Vertex {
        float position[2];
        float color[4];
    };

    std::vector<Vertex> vertexBuffer;
    std::vector<unsigned int> indexBuffer;

    GLuint vbo;
    GLuint ibo;

    String vertexShader;
    String fragmentShader;

    std::unique_ptr<OpenGLShaderProgram> shaderProgram;

    // --- GL ---
    // juce::OpenGLContext openGLContext;
    // ----------------
    // juce::OpenGLAppComponent openGLAppComponent;  // is a OpenGLRenderer implements initialize(), render(), shutdown()
    // juce::OpenGLRenderer openGLRenderer;          // implements newOpenGLContextCreated(), renderOpenGL(), openGLContextClosing()
    //      openGLContext.setRenderer(this); openGLContext.attachTo(*this);
    // ----------------
    // --- ::newOpenGLContextCreated() ---
    // std::unique_ptr<juce::OpenGLShaderProgram> shaderProgram;
    //      shaderProgram.reset(new OpenGLShaderProgram(openGLContext));
    //      if (shaderProgram->addVertexShader(...) && shaderProgram->addFragmentShader(...) && shaderProgram->link()) { shaderProgram->use() }
    // juce::String vertexShader;
    // juce::String fragmentShader;
    // attribute
    // juce::OpenGLShaderProgram::Uniform uniform;
    // shape
    // ----------------
    // --- RAW OpenGL ---
    // std::vector<Vertex> vertexBuffer; std::vector<unsigned int> indexBuffer;
    // GLuint vbo; GLuint ibo;
    // openGLContext.extensions.glGenBuffers(1, &vbo);
    // openGLContext.extensions.glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // openGLContext.extensions.glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexBuffer.size(), vertexBuffer.data(), GL_STATIC_DRAW);
    // --- ::renderOpenGL() ---
    // OpenGLHelpers::clear(Colours::black);
    // shaderProgram->use();
    // openGLContext.extensions.glBindBuffer(..., vbo);
    // openGLContext.extensions.glBindBuffer(..., ibo);
    // openGLContext.extensions.glVertexAttribPointer(...);
    // openGLContext.extensions.glEnableVertexAttribArray(0);  // position attribute
    // openGLContext.extensions.glVertexAttribPointer(...);
    // openGLContext.extensions.glEnableVertexAttribArray(1);  // color attribute
    // glDrawElements(...);
    // openGLContext.extensions.glDisableVertexAttribArray(0);
    // openGLContext.extensions.glDisableVertexAttribArray(1);
    // ----------------
    // --- GLSL: vert, vs ---
    // position = pixelPos;
    // gl_Position = projectionMatrix * viewMatrix * position;
    // ----------------
    // --- GLSL: frag, fs ---
    // fragColor = mix(...);
    // gl_FragColor = pixelAlpha * fragColor;
    // ----------------

};
