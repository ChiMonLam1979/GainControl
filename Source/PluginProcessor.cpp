#include "PluginProcessor.h"
#include "PluginEditor.h"


GainTutorialAudioProcessor::GainTutorialAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
	treeState(*this, nullptr, "PARAMETERS", createParameterLayout()), gainValue(*dynamic_cast<AudioParameterFloat*>(treeState.getParameter(GAIN_ID)))
#endif
{
	treeState.state = ValueTree(GAIN_ID);
}

AudioProcessorValueTreeState::ParameterLayout GainTutorialAudioProcessor::createParameterLayout()
{
	std::vector <std::unique_ptr<RangedAudioParameter>> params;

	NormalisableRange<float> range { Decibels::gainToDecibels(0.0f), Decibels::gainToDecibels(1.0f) };

	auto gainParam = std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, range, Decibels::gainToDecibels(0.0f));

	params.push_back(std::move(gainParam));

	return { params.begin(), params.end() };
}

GainTutorialAudioProcessor::~GainTutorialAudioProcessor()
{

}

const String GainTutorialAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainTutorialAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainTutorialAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainTutorialAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainTutorialAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainTutorialAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainTutorialAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainTutorialAudioProcessor::setCurrentProgram (int index)
{
}

const String GainTutorialAudioProcessor::getProgramName (int index)
{
    return {};
}

void GainTutorialAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void GainTutorialAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	previousGain = Decibels::decibelsToGain(gainValue.get());
}

void GainTutorialAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainTutorialAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GainTutorialAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	float currentGain = Decibels::decibelsToGain(gainValue.get());

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	if (currentGain == previousGain)
	{
		buffer.applyGain(currentGain);
	}
	else
	{
		buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, currentGain);
		previousGain = currentGain;
	}
}

bool GainTutorialAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GainTutorialAudioProcessor::createEditor()
{
    return new GainTutorialAudioProcessorEditor (*this);
}

void GainTutorialAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void GainTutorialAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainTutorialAudioProcessor();
}