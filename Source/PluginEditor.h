#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "MySliderLookAndFeel.h"

class MySlider : public Slider
{
public:
	MySlider()
	{}

	String getTextFromValue(double value) override;
	double getValueFromText(const String& text) override;
private:
};

class GainTutorialAudioProcessorEditor  : public AudioProcessorEditor
{
public:

    GainTutorialAudioProcessorEditor (GainTutorialAudioProcessor&);
    ~GainTutorialAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;


private:

    GainTutorialAudioProcessor& processor;

	MySliderLookAndFeel sliderLookAndFeel;

	MySlider gainSlider;

public:

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainTutorialAudioProcessorEditor)
};
