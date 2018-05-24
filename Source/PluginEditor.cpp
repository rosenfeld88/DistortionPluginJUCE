/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionAudioProcessorEditor::DistortionAudioProcessorEditor (DistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
//    addAndMakeVisible(driveKnob = new Slider("Drive"));
//    driveKnob->setSliderStyle(Slider::Rotary);
//    driveKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
//
//    addAndMakeVisible(rangeKnob = new Slider("Range"));
//    rangeKnob->setSliderStyle(Slider::Rotary);
//    rangeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(gainKnob = new Slider("Gain"));
    gainKnob->setSliderStyle(Slider::Rotary);
    gainKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(blendKnob = new Slider("Blend"));
    blendKnob->setSliderStyle(Slider::Rotary);
    blendKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(volumeKnob = new Slider("Volume"));
    volumeKnob->setSliderStyle(Slider::Rotary);
    volumeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(toneKnob = new Slider("Tone"));
    toneKnob->setSliderStyle(Slider::Rotary);
    toneKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(clipFxnSelect = new ComboBox("Clip Type"));
    clipFxnSelect->addItem("Arc Tan", 1);
    clipFxnSelect->addItem("Tanh", 2);
    clipFxnSelect->addItem("Soft-Max", 3);
    //clipFxnSelect->setSelectedItemIndex(1);
    
//    driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "drive", *driveKnob);
//    rangeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "range", *rangeKnob);
    gainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "gain", *gainKnob);
    blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "blend", *blendKnob);
    volumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "volume", *volumeKnob);
    toneAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "tone", *toneKnob);
    clipFxnAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getState(), "clip", *clipFxnSelect);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 300);
}

DistortionAudioProcessorEditor::~DistortionAudioProcessorEditor()
{
}

//==============================================================================
void DistortionAudioProcessorEditor::paint (Graphics& g)
{
    int paramsPerRow = 2;
    int h_spacing = 25;
    int v_spacing = 30;
    int paramWidth = 100;
    int knobHeight = 100;
    int comboHeight = 25;
    int pad = (getWidth() - ((paramsPerRow + 1) * paramWidth + 10) - (paramsPerRow * h_spacing)) / 2;
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    
    g.drawText("Gain", pad, (getHeight() - v_spacing - knobHeight) / 2, paramWidth, knobHeight, Justification::centred, false);
    g.drawText("Volume", pad + 1 * (paramWidth + h_spacing), (getHeight() - v_spacing - knobHeight) / 2, paramWidth, knobHeight, Justification::centred, false);
    g.drawText("Blend", pad, (getHeight() + knobHeight + v_spacing) / 2, paramWidth, knobHeight, Justification::centred, false);
    g.drawText("Tone", pad + 1 * (paramWidth + h_spacing), (getHeight() + knobHeight + v_spacing) / 2, paramWidth, knobHeight, Justification::centred, false);
    g.drawText("Clip Type", pad + 2 * (paramWidth + h_spacing), ((getHeight() + comboHeight) / 2) + 5, paramWidth + 10, 10, Justification::centred, false);
}

void DistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int paramsPerRow = 2;
    int h_spacing = 25;
    int v_spacing = 30;
    int paramWidth = 100;
    int knobHeight = 100;
    int comboHeight = 25;
    int pad = (getWidth() - ((paramsPerRow + 1) * paramWidth + 10) - (paramsPerRow * h_spacing)) / 2;
    
    gainKnob->setBounds(pad, ((getHeight() - v_spacing) / 2) - knobHeight, paramWidth, knobHeight);
    volumeKnob->setBounds(pad + 1 * (paramWidth + h_spacing), ((getHeight() - v_spacing) / 2) - knobHeight, paramWidth, knobHeight);
    blendKnob->setBounds(pad, (getHeight() / 2) + (v_spacing / 2), paramWidth, knobHeight);
    toneKnob->setBounds(pad + 1 * (paramWidth + h_spacing), (getHeight() + v_spacing) / 2, paramWidth, knobHeight);
    clipFxnSelect->setBounds(pad + 2 * (paramWidth + h_spacing), (getHeight() - comboHeight) / 2, paramWidth + 10, comboHeight);
}
