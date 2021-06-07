/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 */
class Delay_PluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Delay_PluginAudioProcessor();
    ~Delay_PluginAudioProcessor() override;
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const juce::String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void setFeedback(float feedback);
    void setDelayRight(float delay);
    void setDelayLeft(float delay);
    void setFilterCutoffRight(float frequency);
    void setFilterCutoffLeft(float frequency);

private:
    float feedback;
    float checkDelay(float delay);
    float checkFilter(float cutoff);


    enum
    {
        left,
        right
    };
    float maxDelay = 4;
    float maxFilterFreq = 20000;
    // maybe try different interpolation types
    // https://docs.juce.com/master/namespacedsp_1_1DelayLineInterpolationTypes.html
    // https://docs.juce.com/master/classdsp_1_1DelayLine.html
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delays[2];
    juce::dsp::IIR::Filter<float> filters[2];

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay_PluginAudioProcessor)
};
