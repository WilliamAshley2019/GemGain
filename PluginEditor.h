#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class GemGainAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    GemGainAudioProcessorEditor(GemGainAudioProcessor&);
    ~GemGainAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    GemGainAudioProcessor& audioProcessor;

    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GemGainAudioProcessorEditor)
};
