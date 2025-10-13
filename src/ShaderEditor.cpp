#include "ShaderEditor.h"

ShaderEditor::ShaderEditor(PluginAudioProcessor& p)
    : juce::AudioProcessorEditor(&p), processor(p)
{
    setOpaque(true);
    if (auto* peer = getPeer())
        peer->setCurrentRenderingEngine (0);

    openGLContext.attachTo (*getTopLevelComponent());

    addAndMakeVisible (statusLabel);
    statusLabel.setJustificationType (juce::Justification::topLeft);
    statusLabel.setFont (juce::FontOptions (14.0f));

    auto presets = getPresets();

    for (int i = 0; i < presets.size(); ++i)
        presetBox.addItem (presets[i].name, i + 1);

    addAndMakeVisible (presetLabel);
    presetLabel.attachToComponent (&presetBox, true);

    addAndMakeVisible (presetBox);
    presetBox.onChange = [this] { selectPreset (presetBox.getSelectedItemIndex()); };

    fragmentEditorComp.setOpaque (false);
    fragmentDocument.addListener (this);
    addAndMakeVisible (fragmentEditorComp);

    presetBox.setSelectedItemIndex (0);

    setSize (500, 500);
}

ShaderEditor::~ShaderEditor()
{
    openGLContext.detach();
    shader.reset();
}

void ShaderEditor::paint(juce::Graphics& g)
{
    g.fillCheckerBoard (getLocalBounds().toFloat(), 48.0f, 48.0f, juce::Colours::lightgrey, juce::Colours::white);

    if (shader.get() == nullptr || shader->getFragmentShaderCode() != fragmentCode)
    {
        shader.reset();

        if (fragmentCode.isNotEmpty())
        {
            shader.reset (new juce::OpenGLGraphicsContextCustomShader (fragmentCode));

            auto result = shader->checkCompilation (g.getInternalContext());

            if (result.failed())
            {
                statusLabel.setText (result.getErrorMessage(), juce::NotificationType::dontSendNotification);
                shader.reset();
            }
        }
    }

    if (shader.get() != nullptr)
    {
        statusLabel.setText ({}, juce::NotificationType::dontSendNotification);

        shader->fillRect (g.getInternalContext(), getLocalBounds());
    }
}

void ShaderEditor::resized() {
    auto area = getLocalBounds().reduced (4);

    statusLabel.setBounds (area.removeFromTop (75));

    area.removeFromTop (area.getHeight() / 2);

    auto presets = area.removeFromTop (25);
    presets.removeFromLeft (100);
    presetBox.setBounds (presets.removeFromLeft (150));

    area.removeFromTop (4);
    fragmentEditorComp.setBounds (area);
}

void ShaderEditor::selectPreset(int preset) {
    fragmentDocument.replaceAllContent (getPresets()[preset].fragmentShader);
    startTimer (1);
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
        }
    };
    return juce::Array<ShaderPreset>(presets, numElementsInArray(presets));
}

