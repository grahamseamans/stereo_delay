/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay_PluginAudioProcessorEditor::Delay_PluginAudioProcessorEditor (Delay_PluginAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 200);
    
    float minDelay = 0;
    float maxDelay = 4;
    float stepDelay = 0.01;
    float minFilter = 50 ;
    float maxFilter = 20000;
    float stepFilter = 1;
    initSlider(feedbackSlider, feedbackLabel, "Feedback", 0, 1, 0.01);
    initSlider(rightDelaySlider, rightDelayLabel, "Right Delay", minDelay, maxDelay, stepDelay);
    initSlider(leftDelaySlider, leftDelayLabel, "Left Delay", minDelay, maxDelay, stepDelay);
    initSlider(rightFilterSlider, rightFilterLabel, "Right Filter Cutoff", minFilter, maxFilter, stepFilter);
    initSlider(leftFilterSlider, leftFilterLabel, "Left Filter Cuttoff", minFilter, maxFilter, stepFilter);
    
    rightFilterSlider.setSkewFactorFromMidPoint (400);
    leftFilterSlider.setSkewFactorFromMidPoint (400);

    
    
    
}

void Delay_PluginAudioProcessorEditor::initSlider(juce::Slider& slider, juce::Label& label, juce::String text, float min, float max, float step){
    addAndMakeVisible(slider);
    slider.addListener(this);
    slider.setRange (min, max, step);
    slider.setTextValueSuffix (" " + text);
    slider.setValue((max - min)/4);
    slider.setTextBoxStyle (juce::Slider::TextBoxLeft, false, 160, slider .getTextBoxHeight());
    
    addAndMakeVisible (label);
    label.setText (text, juce::dontSendNotification);
    label.attachToComponent (&slider, true);
    
    
}

void Delay_PluginAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    
    if (slider == &feedbackSlider)
        audioProcessor.setFeedback(feedbackSlider.getValue());
    else if (slider == &rightDelaySlider)
        audioProcessor.setDelayRight(rightDelaySlider.getValue());
    else if (slider == &leftDelaySlider)
        audioProcessor.setDelayLeft(leftDelaySlider.getValue());
    else if (slider == &rightFilterSlider)
        audioProcessor.setFilterCutoffRight(rightFilterSlider.getValue());
    else if (slider == &leftFilterSlider)
        audioProcessor.setFilterCutoffLeft(leftFilterSlider.getValue());
    
}

Delay_PluginAudioProcessorEditor::~Delay_PluginAudioProcessorEditor()
{
}

//==============================================================================
void Delay_PluginAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll (juce::Colours::grey);
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Stereo Delay", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void Delay_PluginAudioProcessorEditor::resized()
{
    // https://docs.juce.com/master/tutorial_slider_values.html
    auto sliderLeft = 120;
    feedbackSlider.setBounds (sliderLeft, 30, getWidth() - sliderLeft - 10, 20);
    rightDelaySlider.setBounds (sliderLeft, 60, getWidth() - sliderLeft - 10, 20);
    leftDelaySlider.setBounds (sliderLeft, 90, getWidth() - sliderLeft - 10, 20);
    rightFilterSlider.setBounds (sliderLeft, 120, getWidth() - sliderLeft - 10, 20);
    leftFilterSlider.setBounds (sliderLeft, 150, getWidth() - sliderLeft - 10, 20);
}
