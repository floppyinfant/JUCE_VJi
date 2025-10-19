/**
 * Audio Effect (DSP Fx)
 * @name floppyinfant
 * @date 19.10.2025
 * inspired by WavetableSynth
 * https://www.youtube.com/watch?v=Ah4P-zOfdYc&t=1032s
 */

#include "DspProcessor.h"

void DspProcessor::prepareToPlay(double sampleRate) {
    this->mSampleRate = sampleRate;
}

void DspProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    auto currentSample = 0;

    for (const auto midiMessage : midiMessages) {
        const auto midiEvent = midiMessage.getMessage();
        const auto midiEventSample = static_cast<int>(midiEvent.getTimeStamp());

        render(buffer, currentSample, midiEventSample);
        handleMidiEvent(midiEvent);
        currentSample = midiEventSample;
    }
    render(buffer, currentSample, buffer.getNumSamples());
}

void DspProcessor::handleMidiEvent(const juce::MidiMessage& midiEvent) {
    if (midiEvent.isNoteOn()) {
        const auto note = midiEvent.getNoteNumber();
        juce::ignoreUnused(note);
        // TODO handleMidiEvent do something

    } else if (midiEvent.isNoteOff()) {

    } else if (midiEvent.isAllNotesOff()) {

    }
}

void DspProcessor::render(juce::AudioBuffer<float>& buffer, int startSample, int endSample) {
    juce::ignoreUnused(buffer, startSample, endSample);
    // TODO synth
}
