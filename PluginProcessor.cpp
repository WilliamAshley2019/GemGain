#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GemGainAudioProcessor::GemGainAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
}

GemGainAudioProcessor::~GemGainAudioProcessor() {}

//==============================================================================
void GemGainAudioProcessor::prepareToPlay(double sampleRate, int)
{
    // Initialize gain values from parameter using .load() for std::atomic<float>
    currentGain = targetGain = juce::Decibels::decibelsToGain(apvts.getRawParameterValue("gain")->load());
}

void GemGainAudioProcessor::releaseResources() {}

void GemGainAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto numChannels = getTotalNumInputChannels();
    auto numSamples = buffer.getNumSamples();

    // Get target gain from slider using .load()
    targetGain = juce::Decibels::decibelsToGain(apvts.getRawParameterValue("gain")->load());

    // Simple one-pole smoothing
    float smoothingFactor = 0.001f; // click-free smoothing
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for (int i = 0; i < numSamples; ++i)
        {
            currentGain += (targetGain - currentGain) * smoothingFactor;
            channelData[i] *= currentGain;
        }
    }

    // Clear unused output channels
    for (int i = numChannels; i < getTotalNumOutputChannels(); ++i)
        buffer.clear(i, 0, numSamples);
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout GemGainAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID("gain", 1),
        "Gain",
        juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f), // -24dB to +24dB
        0.0f, // default
        "dB"
    ));
    return layout;
}

//==============================================================================
bool GemGainAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* GemGainAudioProcessor::createEditor() { return new GemGainAudioProcessorEditor(*this); }

//==============================================================================
const juce::String GemGainAudioProcessor::getName() const { return JucePlugin_Name; }
bool GemGainAudioProcessor::acceptsMidi() const { return false; }
bool GemGainAudioProcessor::producesMidi() const { return false; }
bool GemGainAudioProcessor::isMidiEffect() const { return false; }
double GemGainAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int GemGainAudioProcessor::getNumPrograms() { return 1; }
int GemGainAudioProcessor::getCurrentProgram() { return 0; }
void GemGainAudioProcessor::setCurrentProgram(int) {}
const juce::String GemGainAudioProcessor::getProgramName(int) { return {}; }
void GemGainAudioProcessor::changeProgramName(int, const juce::String&) {}

//==============================================================================
void GemGainAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void GemGainAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState && xmlState->hasTagName(apvts.state.getType()))
        apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new GemGainAudioProcessor(); }
