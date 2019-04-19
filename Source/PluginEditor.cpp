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
	gainSlider.setRange(-52.0, 0.0); // set for decibels where 0 is max volume - fixed in getTextFromVlaue and getValueFromText
	gainSlider.setValue(-52.0);
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
	return String(value, 1);
}

double MySlider::getValueFromText(const String& text) 
{
	return text.getDoubleValue();
}