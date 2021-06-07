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
    setSize (400, 300);
    
    float minDelay = 0;
    float maxDelay = 4;
    float stepDelay = 0.01;
    float minFilter = 0;
    float maxFilter = 20000;
    float stepFilter = 1;
    initSlider(feedbackSlider, feedbackLabel, "Feedback", 0, 1, 0.01);
    initSlider(rightDelaySlider, rightDelayLabel, "Right Delay", minDelay, maxDelay, stepDelay);
    initSlider(leftDelaySlider, leftDelayLabel, "Left Delay", minDelay, maxDelay, stepDelay);
    initSlider(rightFilterSlider, rightFilterLabel, "Right Filter Cutoff", minFilter, maxFilter, stepFilter);
    initSlider(leftFilterSlider, leftFilterLabel, "Left Filter Cuttoff", minFilter, maxFilter, stepFilter);

    feedbackSlider.addListener (this);

}

void Delay_PluginAudioProcessorEditor::initSlider(juce::Slider& slider, juce::Label& label, juce::String text, float min, float max, float step){
    slider.setSliderStyle (juce::Slider::LinearBarVertical);
    slider.setRange (min, max, step);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 90, 0);
    slider.setPopupDisplayEnabled (true, false, this);
    slider.setTextValueSuffix (" Feedback");
    slider.setValue((max - min)/2);
    addAndMakeVisible(slider);
    
    addAndMakeVisible (label);
    label.setText (text, juce::dontSendNotification);
    label.attachToComponent (&slider, true);
}

void Delay_PluginAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &feedbackSlider)                                                      // [3]
        audioProcessor.feedback = feedbackSlider.getValue();
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
    // fill the whole window white
    g.fillAll (juce::Colours::white);
 
    // set the current drawing colour to black
    g.setColour (juce::Colours::black);
 
    // set the font size and draw text to the screen
    g.setFont (15.0f);
 
    g.drawFittedText ("Stereo Delay", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void Delay_PluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    feedbackSlider.setBounds (40, 30, 20, getHeight() - 60);
    rightDelaySlider.setBounds (100, 30, 20, getHeight() - 60);
    leftDelaySlider.setBounds (160, 30, 20, getHeight() - 60);
    rightFilterSlider.setBounds (220, 30, 20, getHeight() - 60);
    leftFilterSlider.setBounds (280, 30, 20, getHeight() - 60);

    /*
    40 + 20 = 60
     60 + 40 = 100
     100
     */
     
}
