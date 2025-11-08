//
// Created by thorsten on 07.11.2025.
//

#pragma once

#include <JuceHeader.h>

class Parameters {
public:
    Parameters();
    ~Parameters();

    // https://www.youtube.com/watch?v=K2PCQjbcVmo (Beats Basteln)
    //juce::ParameterLayout
    //juce::RangedAudioParameter
    //juce::AudioProcessorParameter
    //juce::AudioParameterFloat
    std::unique_ptr<juce::RangedAudioParameter> RAP;
    //std::vector<RAP> RAPVector;

    //inline Layout createParameterLayout() {}

private:

};
