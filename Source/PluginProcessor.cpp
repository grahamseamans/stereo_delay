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
    //    dsp::ProcessorChain<dsp::DelayLine<float>,dsp::Panner<float>> chain;
    //    chain.get<0>() = dsp::DelayLine<float>(10 * 44100);
    
    //    auto& delay = processorChain.get<delayIndex>();
    //    delay = juce::dsp::DelayLine<float>(4 * 44100);
    //    delay.setDelay (44100 * 0.5);
    //
    //    delayLine = juce::dsp::DelayLine<float>(4 * 44100);
    //    delayLine.setDelay (44100 * 0.5);
    //

    
//    filter.setCutoffFrequencyHz (1000.0f);
//    filter.setResonance (0.7f);
    //
    //
    //    auto& masterGain = processorChain.get<gainIndex>();
    //    masterGain.setGainLinear (0.5f);
    //
    //    auto& filter = processorChain.get<filterIndex>();
    //    filter.setCutoffFrequencyHz (1000.0f);
    //    filter.setResonance (0.7f);
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
        delays[channel] = juce::dsp::DelayLine<float>(4 * sampleRate);
        delays[channel].setDelay (sampleRate * 0.5);
        filters[channel] = juce::dsp::IIR::Filter<float>(juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate,700));
    }
    delays[right].setDelay(sampleRate * 0.75);
    
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
    
    //    float freq = 500;
    //    juce::uint32 blockSize = 512;
    //    juce::dsp::ProcessSpec spec = { sampleRate, blockSize, static_cast<juce::uint32>(readBuffer.getNumChannels()) };
    //
    //
    //    juce::dsp::AudioBlock<float> block(readBuffer);
    //    juce::dsp::ProcessContextReplacing<float> context(block);
    //
    //    juce::dsp::ProcessorDuplicator<juce::dsp::FIR::Filter<float>, juce::dsp::FIR::Coefficients<float>> fir;
    //    fir.state = juce::dsp::FilterDesign<float>::designFIRLowpassWindowMethod (freq, sampleRate, 21, juce::dsp::WindowingFunction<float>::blackman);
    //    fir.prepare (spec);
    //    fir.process (context);
    
    
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
    //    const auto numChannels = juce::jmax (totalNumInputChannels, totalNumOutputChannels);
    //
    //    auto inoutBlock = juce::dsp::AudioBlock<float> (buffer).getSubsetChannelBlock (0, (size_t) numChannels);
    //    processorChain.process (juce::dsp::ProcessContextReplacing<float> (inoutBlock));
    
    
    //    // In case we have more outputs than inputs, this code clears any output
    //    // channels that didn't contain input data, (because these aren't
    //    // guaranteed to be empty - they may contain garbage).
    //    // This is here to avoid people getting screaming feedback
    //    // when they first compile a plugin, but obviously you don't need to keep
    //    // this code if your algorithm always overwrites all the output channels.
    //    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    //        buffer.clear (i, 0, buffer.getNumSamples());
    //
    //    // This is the place where you'd normally do the guts of your plugin's
    //    // audio processing...
    //    // Make sure to reset the state if your inner loop is processing
    //    // the samples and the outer loop is handling the channels.
    //    // Alternatively, you can process the samples with the channels
    //    // interleaved by keeping the same state.
    //    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //    {
    //        auto* channelData = buffer.getWritePointer (channel);
    //
    //        // ..do something to the data...
    //    }
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
    delays[right].setDelay(getSampleRate() * delay);
}
void Delay_PluginAudioProcessor::setDelayLeft(float delay){
    delays[left].setDelay(getSampleRate() * delay);
}
void Delay_PluginAudioProcessor::setFilterCutoffRight(float frequency){
    filters[right] = juce::dsp::IIR::Filter<float>(juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(),frequency));
}
void Delay_PluginAudioProcessor::setFilterCutoffLeft(float frequency){
    filters[left] = juce::dsp::IIR::Filter<float>(juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(),frequency));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Delay_PluginAudioProcessor();
}
