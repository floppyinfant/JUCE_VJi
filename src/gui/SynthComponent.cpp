/*
  ==============================================================================

    SynthComponent.cpp
    Created: 1 Sep 2022 7:17:41pm
    Author:  thorsten

  ==============================================================================
*/

#include "SynthComponent.h"
#include "../../PluginProcessor.h"

/*
* https://docs.juce.com/master/tutorial_component_parents_children.html
*/
SynthComponent::SynthComponent()  //SQ251AudioProcessor& p
    //: slider ()
{
    // create objects
    // declaration, definition, initialization, instantiation, RAII ???
    

    label.setText("Hello VCO", juce::dontSendNotification);
    label.attachToComponent(&slider, true);
    //sliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "id", slider));

    // My Hierarchy
    vco.addChildComponent(slider);
    generators.addChildComponent(vco);
    this->addChildComponent(generators);
    
    //--------------------------------------------------------------------------
    // addAndMakeVisible + MUST setBounds in resized()
    addAndMakeVisible(&slider);
    addAndMakeVisible(&vco);
    addAndMakeVisible(&generators);
   
}

SynthComponent::~SynthComponent()
{
}

//------------------------------------------------------------------------------

void SynthComponent::paint(juce::Graphics&)
{
}

/*
* https://docs.juce.com/master/tutorial_rectangle_advanced.html
* https://docs.juce.com/master/tutorial_flex_box_grid.html
* https://docs.juce.com/master/tutorial_slider_values.html
*/
void SynthComponent::resized()
{
    auto bounds = getLocalBounds();

    slider.setBounds(bounds.removeFromTop(60));
    label.setBounds(bounds.removeFromTop(60));
    vco.setBounds(bounds.removeFromTop(120));
    generators.setBounds(bounds.removeFromBottom(180));
}

//------------------------------------------------------------------------------
// Listener Callbacks

void SynthComponent::sliderValueChanged(juce::Slider* slider)
{
}

void SynthComponent::buttonClicked(juce::Button* btn)
{
}

void SynthComponent::comboBoxChanged(juce::ComboBox* cb)
{
}

void SynthComponent::timerCallback()
{

}
