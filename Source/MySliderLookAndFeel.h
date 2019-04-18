#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MySliderLookAndFeel : public LookAndFeel_V4
{
public:

	MySliderLookAndFeel()
	{
	}

	Slider::SliderLayout getSliderLayout(Slider&) override;
	void drawLinearSlider(Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider&) override;
	void drawLabel(Graphics&, Label&) override;
};