//
// based on medium.com
// https://medium.com/@Im_Jimmi/using-opengl-for-2d-graphics-in-a-juce-plug-in-24aa82f634ff
//

#pragma once

#include <JuceHeader.h>
#include "../../PluginProcessor.h"
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

    // ===========================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenGLComponent)
};
