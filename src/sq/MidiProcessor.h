/*
  ==============================================================================

    MidiProcessor.h
    Created: 5 Aug 2022 8:25:13pm
    Author:  thorsten

	inspired by
	Juce Tutorial 60 - Create your first MIDI Plug-in with Eyal Amir (Xfer Records)
    11.12.2019
    https://www.youtube.com/watch?v=tgf6J8foCiw
  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
using namespace juce;

constexpr int interval = 4;


class MidiProcessor
{
public:
	void process(MidiBuffer& midiMessages)
	{
		// 1. delete old messages
		processedBuffer.clear();

		// 2. processMidiInput
		MidiBuffer::Iterator it(midiMessages);
		MidiMessage currentMessage;
		int samplePos;

		// TODO deprecated iterator
		while (it.getNextEvent(currentMessage, samplePos))
		{
			// print Debug message to console (std::cout)
			//DBG (currentMessage.getDescription());

			// switch types
			if (currentMessage.isNoteOnOrOff())
			{
				// my processing
				currentMessage.setNoteNumber(50);
			}
			processedBuffer.addEvent(currentMessage, samplePos);
		}

		// 3. send back to host
		midiMessages.swapWith(processedBuffer);
	}

	// members ---------------------------------------------------------

	MidiBuffer processedBuffer;
};
