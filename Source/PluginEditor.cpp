/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTutorialAudioProcessorEditor::GainTutorialAudioProcessorEditor (GainTutorialAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setResizable(true, true);
	setResizeLimits(50, 50, 800, 800);
    setSize (200, 400);

	gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	gainSlider.setRange(0.0, 1.0);
	gainSlider.setValue(0.5);
	gainSlider.setLookAndFeel(&sliderLookAndFeel);
	gainSlider.addListener(this);

	addAndMakeVisible(gainSlider);
}

GainTutorialAudioProcessorEditor::~GainTutorialAudioProcessorEditor()
{
}

//==============================================================================
void GainTutorialAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);
}

void GainTutorialAudioProcessorEditor::resized()
{

	gainSlider.setBounds(getLocalBounds());
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void GainTutorialAudioProcessorEditor::sliderValueChanged(Slider* slider)
{

	if(slider == &gainSlider)
	{
		processor.rawVolume = slider->getValue();
	}
}

String MySlider::getTextFromValue(double value)
{
	String newValue(value, 1);
	return newValue;
}

double MySlider::getValueFromText(const String& text)
{
	auto newValue = text.getDoubleValue();
	return newValue;
}