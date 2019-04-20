#include "PluginProcessor.h"
#include "PluginEditor.h"

GainTutorialAudioProcessorEditor::GainTutorialAudioProcessorEditor (GainTutorialAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	setResizable(true, true);
	setResizeLimits(50, 50, 800, 800);
    setSize (200, 400);

	sliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, gainSlider);

	gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	gainSlider.setRange(Decibels::gainToDecibels(0.0), Decibels::gainToDecibels(1.0));
	gainSlider.setSkewFactorFromMidPoint(-20.0);
	gainSlider.setValue(Decibels::gainToDecibels(0.0));
	gainSlider.setLookAndFeel(&sliderLookAndFeel);
	addAndMakeVisible(gainSlider);
}

GainTutorialAudioProcessorEditor::~GainTutorialAudioProcessorEditor()
{
}

void GainTutorialAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
}

void GainTutorialAudioProcessorEditor::resized()
{

	gainSlider.setBounds(getLocalBounds());
}

String MySlider::getTextFromValue(double value)
{
	return Decibels::toString(value, 1);
}

double MySlider::getValueFromText(const String& text) 
{
	auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim();
	auto minusInfinitydB = -100.0;
	return decibelText.equalsIgnoreCase("-INF") ? minusInfinitydB : decibelText.getDoubleValue();
}