#pragma once

#include <JuceHeader.h>
#include "OpenGLUtilities.h"

// -----------------------------------------------------------------------

#define MEDIUM_COM 0
#define OPENGL_APP_DEMO 1
#define OPENGL_DEMO 0

/*
 * Read:
 *
 * Juce:
 * https://juce.com/learn/tutorials/
 * https://juce.com/tutorials/tutorial_open_gl_application/
 * https://juce.com/tutorials/tutorial_animation/
 * Demorunner (juce/examples/gui) OpenGLDemo2D, OpenGLAppDemo (3D), OpenGLDemo (complex)
 * Classes:
 * https://docs.juce.com/master/classjuce_1_1OpenGLContext.html (Context)
 * https://docs.juce.com/master/structjuce_1_1OpenGLGraphicsContextCustomShader.html (simplified, 2D)
 * https://docs.juce.com/master/classjuce_1_1OpenGLAppComponent.html (simplified, 3D)
 * https://docs.juce.com/master/classjuce_1_1OpenGLShaderProgram.html (Shader)
 * https://docs.juce.com/master/classjuce_1_1OpenGLRenderer.html (Renderer)
 * https://docs.juce.com/master/classjuce_1_1OpenGLHelpers.html
 *
 * OpenGL and Shaders:
 * https://learnopengl.com/Getting-started/Shaders+
 * https://wikis.khronos.org/opengl/Shader
 * https://wikis.khronos.org/opengl/OpenGL_Shading_Language
 *
 * https://thebookofshaders.com/
 * https://iquilezles.org/articles/distfunctions2d/
 * ShaderToy, p5, SHADERed (Editor)
 *
 * https://github.com/vanrez-nez/awesome-glsl
 * https://github.com/sudara/awesome-juce
 */

// -----------------------------------------------------------------------

class OpenGLComponent : public juce::Component, private juce::OpenGLRenderer {

public:

    OpenGLComponent();
    ~OpenGLComponent() override;

    // --------------------------------

    // Component
    void paint (Graphics&) override;
    void resized() override;

    // --------------------------------

    // OpenGLRenderer
    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;

private:

    void freeAllContextObjects();

    Matrix3D<float> getProjectionMatrix() const;

    Matrix3D<float> getViewMatrix() const;

    // --------------------------------

    // OpenGL
    OpenGLContext openGLContext;
    // OpenGLRenderer (this)

    // Vertex Struct (@see OpenGLUtilities.h)
    // Vertex Data (Vertex Buffer Object, VBO)
    std::unique_ptr<OpenGLUtils::Shape> shape;  // Mesh Data
    OpenGLTexture texture;
    //OpenGLUtils::DemoTexture* textureToUse = nullptr;
    //OpenGLUtils::DemoTexture* lastTexture  = nullptr;

    // Shaders | GLSL
    std::unique_ptr<OpenGLShaderProgram> shader;  // shaderProgram
    String vertexShader;  // Code (String)
    String fragmentShader;  // Code (String)
    String newVertexShader;
    String newFragmentShader;
    std::unique_ptr<OpenGLUtils::Attributes> attributes;
    std::unique_ptr<OpenGLUtils::Uniforms> uniforms;

    // --------------------------------

    // Medium.com
    std::vector<OpenGLUtils::Vertex> vertexBuffer;
    std::vector<unsigned int> indexBuffer;
    GLuint vbo;
    GLuint ibo;

    // --------------------------------

    // OpenGLAppDemo (juce/examples/GUI)
    Rectangle<int> bounds;
    float scale = 0.5f;
    float rotation = 0.0f;
    float rotationSpeed = 0.0f;
    Draggable3DOrientation draggableOrientation;
    //bool doBackgroundDrawing = false;
    //BouncingNumber bouncingNumber;
    CriticalSection mutex;
    CriticalSection shaderMutex;

    // --------------------------------

    // Uniforms
    int frameCounter = 0;

    // --------------------------------
    // more methods ...
    // --------------------------------

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenGLComponent)
};
