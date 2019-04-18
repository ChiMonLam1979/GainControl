/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "../../MidiDataProject/Source/LookAndFeel/MySliderLookAndFeel.h"


class MySlider : public Slider
{
public:
	MySlider()
	{
		
	}
     String getTextFromValue(double value) override;
	 double getValueFromText(const String& text) override;

private:

};
//==============================================================================
/**
*/
class GainTutorialAudioProcessorEditor  : public AudioProcessorEditor, Slider::Listener
{
public:
    GainTutorialAudioProcessorEditor (GainTutorialAudioProcessor&);
    ~GainTutorialAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider* slider) override;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sliderAttach;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainTutorialAudioProcessor& processor;

	MySliderLookAndFeel sliderLookAndFeel;
	MySlider gainSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainTutorialAudioProcessorEditor)
};
