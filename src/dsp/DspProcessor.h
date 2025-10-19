#pragma once

#include <JuceHeader.h>
//#include <juce_audio_processors/juce_audio_processors.h>

class DspProcessor {
public:
    void prepareToPlay (double);
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&);

private:
    void handleMidiEvent(const juce::MidiMessage&);

    void render(juce::AudioBuffer<float>&, int, int);
    double mSampleRate = 0;
};
