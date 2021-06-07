/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Delay_PluginAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener

{
public:
    Delay_PluginAudioProcessorEditor (Delay_PluginAudioProcessor&);
    ~Delay_PluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    

private:
    void sliderValueChanged (juce::Slider* slider) override;
    void initSlider(juce::Slider& slider, juce::Label& label, juce::String text, float min, float max, float step);

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Delay_PluginAudioProcessor& audioProcessor;
    
    juce::Slider feedbackSlider;
    juce::Label  feedbackLabel;

    juce::Slider rightDelaySlider;
    juce::Label rightDelayLabel;

    juce::Slider leftDelaySlider;
    juce::Label leftDelayLabel;
    
    juce::Slider rightFilterSlider;
    juce::Label rightFilterLabel;

    juce::Slider leftFilterSlider;
    juce::Label leftFilterLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay_PluginAudioProcessorEditor)
};
