/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay_PluginAudioProcessor::Delay_PluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  )
#endif
{
  
}

Delay_PluginAudioProcessor::~Delay_PluginAudioProcessor()
{
}

//==============================================================================
const juce::String Delay_PluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Delay_PluginAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool Delay_PluginAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool Delay_PluginAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double Delay_PluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Delay_PluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int Delay_PluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Delay_PluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Delay_PluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Delay_PluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Delay_PluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    // Do I have a memory leek if prepare to play is called more than once?
    
    for (int channel = 0; channel < 2; ++channel){
        delays[channel] = juce::dsp::DelayLine<float>(maxDelay * sampleRate);
        filters[channel] = juce::dsp::IIR::Filter<float>(juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate,700));
    }
    
    //    change delay to be one channel?
    for (int channel = 0; channel < 2; ++channel){
        delays[channel].prepare ({ sampleRate, (juce::uint32) samplesPerBlock, 1 });
        filters[channel].prepare({ sampleRate, (juce::uint32) samplesPerBlock, 1 });
    }
}

void Delay_PluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Delay_PluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void Delay_PluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int channel = 0; channel < totalNumInputChannels; ++ channel){
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample<buffer.getNumSamples(); ++sample){
            channelData[sample] += filters[channel].processSample(delays[channel].popSample(0));
            delays[channel].pushSample(0, channelData[sample] * feedback);
        }
        filters[channel].snapToZero(); // Does this help??
    }
}

//==============================================================================
bool Delay_PluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Delay_PluginAudioProcessor::createEditor()
{
    return new Delay_PluginAudioProcessorEditor (*this);
}

//==============================================================================
void Delay_PluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Delay_PluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


void Delay_PluginAudioProcessor::setDelayRight(float delay){

    delays[right].setDelay(getSampleRate() * checkDelay(delay));
}
void Delay_PluginAudioProcessor::setDelayLeft(float delay){
    delays[left].setDelay(getSampleRate() * checkDelay(delay));
}
void Delay_PluginAudioProcessor::setFilterCutoffRight(float frequency){
    filters[right] = juce::dsp::IIR::Filter<float>(juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(),  checkFilter(frequency)));
}
void Delay_PluginAudioProcessor::setFilterCutoffLeft(float frequency){
    filters[left] = juce::dsp::IIR::Filter<float>(juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), checkFilter(frequency)));
}
void Delay_PluginAudioProcessor::setFeedback(float feedback){
    if (feedback > 1) feedback = 1;
    else if (feedback < 0) feedback = 0;
    this->feedback = feedback;
}

float Delay_PluginAudioProcessor::checkDelay(float delay){
    if (delay > maxDelay) return maxDelay;
    else if (delay < 0) return 0;
    else return delay;
}

float Delay_PluginAudioProcessor::checkFilter(float cutoff){
    if (cutoff > maxFilterFreq) return maxFilterFreq;
    else if (cutoff < 0) return 0;
    else return cutoff;
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Delay_PluginAudioProcessor();
}
