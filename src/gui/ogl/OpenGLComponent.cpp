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

void OpenGLComponent::newOpenGLContextCreated() {
    freeAllContextObjects();
}

void OpenGLComponent::renderOpenGL() {

}

void OpenGLComponent::openGLContextClosing() {
    freeAllContextObjects();
}

void paint (Graphics&) {}

void resized() {
    //Rectangle<int> bounds = getLocalBounds();
}

// -----------------------------------------------------------------------

