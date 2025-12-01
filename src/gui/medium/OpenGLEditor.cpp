//
// Created by thorsten on 26.10.2025.
//

#include "OpenGLEditor.h"

OpenGLEditor::OpenGLEditor(PluginAudioProcessor &p)
    : juce::AudioProcessorEditor(&p), processor(p)
{
    setOpaque(true);

    // --------------------------------

    addAndMakeVisible(openGLComponent);
    openGLComponent.setBounds(0,0,800,600);

    // --------------------------------

    setSize(800, 600);
}

OpenGLEditor::~OpenGLEditor() {

}

void OpenGLEditor::paint(juce::Graphics &g) {
    AudioProcessorEditor::paint(g);
}

void OpenGLEditor::resized() {
    AudioProcessorEditor::resized();
}

