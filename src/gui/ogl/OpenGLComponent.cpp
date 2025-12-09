//
// Created by thorsten on 07.12.2025.
//

#include <JuceHeader.h>
#include "OpenGLComponent.h"

// -----------------------------------------------------------------------

OpenGLComponent::OpenGLComponent() {
    if (auto* peer = getPeer()) {
        peer->setCurrentRenderingEngine (0);
    }

    setOpaque (true);

    openGLContext.setOpenGLVersionRequired (OpenGLContext::openGL3_2);
    openGLContext.setRenderer (this);
    openGLContext.attachTo(*this);
    openGLContext.setContinuousRepainting(true);

    //controlsOverlay.reset (new DemoControlsOverlay (*this));
    //addAndMakeVisible(controlsOverlay.get());
    //overlay->initialise();

    setSize (500, 500);
}

OpenGLComponent::~OpenGLComponent() {
    openGLContext.detach();
}

// --------------------------------

void OpenGLComponent::paint (Graphics& g) {
    juce::ignoreUnused(g);
    //g.fillAll(juce::Colours::black);

    // draw over OpenGL

}

void OpenGLComponent::resized() {
    const ScopedLock lock (mutex);

    bounds = getLocalBounds();
    //controlsOverlay->setBounds (bounds);
    draggableOrientation.setViewport (bounds);
}

// --------------------------------

void OpenGLComponent::newOpenGLContextCreated() {
    freeAllContextObjects();

    //OpenGLUtils::Vertex ;

#if MEDIUM_COM  // defined in header; set vert and frag code (strings) below
    // Medium.com
    openGLContext.extensions.glGenBuffers(1, &vbo);
    openGLContext.extensions.glGenBuffers(1, &ibo);

    vertexBuffer = {
        {{ 0.f, 0.5f, 0.f }, {}, { 1.f, 0.f, 0.f, 1.f }, {}},
        {{ 0.5f, -0.5f, 0.f }, {}, { 0.f, 1.f, 0.f, 1.f }, {}},
        {{ -0.5f, -0.5f, 0.f }, {}, { 0.f, 0.f, 1.f, 1.f }, {}}
    };
    indexBuffer = {0, 1, 2};

    openGLContext.extensions.glBindBuffer(gl::GL_ARRAY_BUFFER, vbo);
    openGLContext.extensions.glBufferData(
        gl::GL_ARRAY_BUFFER,                    // The type of data we're sending.
        sizeof(OpenGLUtils::Vertex) * vertexBuffer.size(),   // The size (in bytes) of the data.
        vertexBuffer.data(),                    // A pointer to the actual data.
        gl::GL_STATIC_DRAW                      // How we want the buffer to be drawn.
    );

    openGLContext.extensions.glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, ibo);
    openGLContext.extensions.glBufferData(
        gl::GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int) * indexBuffer.size(),
        indexBuffer.data(),
        gl::GL_STATIC_DRAW
    );

    // --------------------------------

    vertexShader = R"()";   // get the shader (default) --- read from file
    fragmentShader = R"()"; // get the shader (default)
    shader.reset(new OpenGLShaderProgram(openGLContext));
    if (shader->addVertexShader(vertexShader)
        && shader->addFragmentShader(fragmentShader)
        && shader->link())
    {
        shader->use();
    }
    else
    {
        jassertfalse;
    }
#endif
}

void OpenGLComponent::renderOpenGL() {
    OpenGLHelpers::clear(Colours::black);
    //shader->use();
    // set Uniforms

#if MEDIUM_COM
    // Medium.com
    openGLContext.extensions.glBindBuffer(gl::GL_ARRAY_BUFFER, vbo);
    openGLContext.extensions.glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Enable the position attribute.
    openGLContext.extensions.glVertexAttribPointer(
        0,              // The attribute's index (AKA location).
        2,              // How many values this attribute contains.
        gl::GL_FLOAT,   // The attribute's type (float).
        gl::GL_FALSE,   // Tells OpenGL NOT to normalise the values.
        sizeof(Vertex), // How many bytes to move to find the attribute with the same index in the next vertex.
        nullptr         // How many bytes to move from the start of this vertex to find this attribute (the default is 0 so we just pass nullptr here).
    );
    openGLContext.extensions.glEnableVertexAttribArray(0);

    // Enable to colour attribute.
    openGLContext.extensions.glVertexAttribPointer(
        1,                              // This attribute has an index of 1
        4,                              // This time we have four values for the attribute (r, g, b, a)
        gl::GL_FLOAT,
        gl::GL_FALSE,
        sizeof(Vertex),
        (GLvoid*)(sizeof(float) * 2)    // This attribute comes after the position attribute in the Vertex struct, so we need to skip over the size of the position array to find the start of this attribute.
    );
    openGLContext.extensions.glEnableVertexAttribArray(1);

    gl::glDrawElements(
        gl::GL_TRIANGLES,       // Tell OpenGL to render triangles.
        indexBuffer.size(),     // How many indices we have.
        gl::GL_UNSIGNED_INT,    // What type our indices are.
        nullptr                 // We already gave OpenGL our indices so we don't need to pass that again here, so pass nullptr.
    );

    openGLContext.extensions.glDisableVertexAttribArray(0);
    openGLContext.extensions.glDisableVertexAttribArray(1);
#endif

    // -----------------------------------------------------------------------

#if OPENGL_APP_DEMO
    using namespace ::juce::gl;
    jassert (OpenGLHelpers::isContextActive());
    OpenGLHelpers::clear (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    auto desktopScale = (float) openGLContext.getRenderingScale();

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    {
        const ScopedLock lock (mutex);
        glViewport (0, 0,
                    roundToInt (desktopScale * (float) bounds.getWidth()),
                    roundToInt (desktopScale * (float) bounds.getHeight()));
    }

    shader->use();

    if (uniforms->projectionMatrix != nullptr) {
        uniforms->projectionMatrix->setMatrix4(getProjectionMatrix().mat, 1, false);
    }

    if (uniforms->viewMatrix != nullptr) {
        uniforms->viewMatrix->setMatrix4(getViewMatrix().mat, 1, false);
    }

    shape->draw (*attributes);

    // Reset the element buffers so child Components draw correctly
    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
#endif

    // -----------------------------------------------------------------------

#if OPENGL_DEMO
    using namespace ::juce::gl;

        const ScopedLock lock (mutex);

        jassert (OpenGLHelpers::isContextActive());

        auto desktopScale = (float) openGLContext.getRenderingScale();

        OpenGLHelpers::clear (getUIColourIfAvailable (LookAndFeel_V4::ColourScheme::UIColour::windowBackground,
                                                      Colours::lightblue));

        if (textureToUse != nullptr)
            if (! textureToUse->applyTo (texture))
                textureToUse = nullptr;

        // First draw our background graphics to demonstrate the OpenGLGraphicsContext class
        if (doBackgroundDrawing)
            drawBackground2DStuff (desktopScale);

        updateShader();   // Check whether we need to compile a new shader

        if (shader.get() == nullptr)
            return;

        // Having used the juce 2D renderer, it will have messed-up a whole load of GL state, so
        // we need to initialise some important settings before doing our normal GL 3D drawing..
        glEnable (GL_DEPTH_TEST);
        glDepthFunc (GL_LESS);
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glActiveTexture (GL_TEXTURE0);

        if (! openGLContext.isCoreProfile())
            glEnable (GL_TEXTURE_2D);

        glViewport (0, 0,
                    roundToInt (desktopScale * (float) bounds.getWidth()),
                    roundToInt (desktopScale * (float) bounds.getHeight()));

        texture.bind();

        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        shader->use();

        if (uniforms->projectionMatrix != nullptr)
            uniforms->projectionMatrix->setMatrix4 (getProjectionMatrix().mat, 1, false);

        if (uniforms->viewMatrix != nullptr)
            uniforms->viewMatrix->setMatrix4 (getViewMatrix().mat, 1, false);

        if (uniforms->texture != nullptr)
            uniforms->texture->set ((GLint) 0);

        if (uniforms->lightPosition != nullptr)
            uniforms->lightPosition->set (-15.0f, 10.0f, 15.0f, 0.0f);

        if (uniforms->bouncingNumber != nullptr)
            uniforms->bouncingNumber->set (bouncingNumber.getValue());

        shape->draw (*attributes);

        // Reset the element buffers so child Components draw correctly
        glBindBuffer (GL_ARRAY_BUFFER, 0);
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);

        if (! controlsOverlay->isMouseButtonDownThreadsafe())
            rotation += (float) rotationSpeed;
#endif
}

void OpenGLComponent::openGLContextClosing() {
    freeAllContextObjects();
}

void OpenGLComponent::freeAllContextObjects()
{
    shape     .reset();
    shader    .reset();
    attributes.reset();
    uniforms  .reset();
    texture   .release();
}

// -----------------------------------------------------------------------

Matrix3D<float> OpenGLComponent::getProjectionMatrix() const
{
    const ScopedLock lock (mutex);

    auto w = 1.0f / (scale + 0.1f);
    auto h = w * bounds.toFloat().getAspectRatio (false);

    return Matrix3D<float>::fromFrustum (-w, w, -h, h, 4.0f, 30.0f);
}

Matrix3D<float> OpenGLComponent::getViewMatrix() const
{
    const ScopedLock lock (mutex);

    auto viewMatrix = Matrix3D<float>::fromTranslation ({ 0.0f, 1.0f, -10.0f }) * draggableOrientation.getRotationMatrix();
    auto rotationMatrix = Matrix3D<float>::rotation ({ rotation, rotation, -0.3f });

    return viewMatrix * rotationMatrix;
}
