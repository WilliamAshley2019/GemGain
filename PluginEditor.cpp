#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GemGainAudioProcessorEditor::GemGainAudioProcessorEditor(GemGainAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(200, 200);

    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "gain", gainSlider
    );
}

GemGainAudioProcessorEditor::~GemGainAudioProcessorEditor() {}

//==============================================================================
void GemGainAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("GemGain", getLocalBounds(), juce::Justification::centredTop, 1);
}

void GemGainAudioProcessorEditor::resized()
{
    gainSlider.setBounds(getLocalBounds().reduced(20));
}
