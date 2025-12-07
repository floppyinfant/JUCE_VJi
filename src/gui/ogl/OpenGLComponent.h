#pragma once

#include <JuceHeader.h>
#include "OpenGLUtilities.h"

// -----------------------------------------------------------------------

#define MEDIUM_COM 0
#define DEMORUNNER 1

// -----------------------------------------------------------------------

class OpenGLComponent : public juce::Component, private juce::OpenGLRenderer {

public:

    OpenGLComponent();
    ~OpenGLComponent() override;

    // --------------------------------

    void paint (Graphics&) override;
    void resized() override;

    // --------------------------------

    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;

private:

    void freeAllContextObjects()
    {
        shape     .reset();
        shader    .reset();
        attributes.reset();
        uniforms  .reset();
        texture   .release();
    }

    OpenGLContext openGLContext;

    std::unique_ptr<OpenGLShaderProgram> shader;  // shaderProgram
    std::unique_ptr<OpenGLUtils::Shape> shape;
    std::unique_ptr<OpenGLUtils::Attributes> attributes;
    std::unique_ptr<OpenGLUtils::Uniforms> uniforms;
    OpenGLTexture texture;

    String vertexShader;
    String fragmentShader;

    std::vector<OpenGLUtils::Vertex> vertexBuffer;
    std::vector<unsigned int> indexBuffer;
    GLuint vbo;
    GLuint ibo;

    // --------------------------------

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenGLComponent)
};
