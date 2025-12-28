#include "PluginProcessor.h"
#include "PluginEditor.h"

// -----------------------------------------------------------------------

PluginAudioProcessorEditor::PluginAudioProcessorEditor (PluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    // --------------------------------
    // CustomSlider
    // --------------------------------
    //mReleaseSlider.onValueChange = [&]() { processor.changeSamplerRelease(); };
    addAndMakeVisible(rotary);


    // --------------------------------
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 600);
    setResizable(true, true);
}

PluginAudioProcessorEditor::~PluginAudioProcessorEditor()
{
}

// -----------------------------------------------------------------------

void PluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // --------------------------------
    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

    // --------------------------------

}

void PluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // --------------------------------
    // CustomSlider
    // --------------------------------
    //rotary.setBounds(getLocalBounds());
    //rotary.setBounds(170, 255, 128, 150 + 20);
    rotary.setBounds(110, 310, 180, 180+20);
    rotary.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    rotary.setTextBoxStyle(Slider::TextBoxBelow, false, 45, 20);
    rotary.setTextValueSuffix(" s");
    rotary.setNumDecimalPlacesToDisplay(0);
    rotary.setTextBoxIsEditable(false);
    rotary.setRange(0.001, 5.0, 0.01);

    // --------------------------------

}

// -----------------------------------------------------------------------

