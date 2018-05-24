/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define ATAN 1
#define TANH 2
#define SOFTMAX 3

//==============================================================================
DistortionAudioProcessor::DistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))
#endif
{
    state = new AudioProcessorValueTreeState(*this, nullptr);
    
//    state->createAndAddParameter("drive", "Drive", "Drive", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.f, nullptr, nullptr);
//
//    state->createAndAddParameter("range", "Range", "Range", NormalisableRange<float>(0.f, 3000.f, 0.0001), 1.f, nullptr, nullptr);
    
    state->createAndAddParameter("gain", "Gain", "Gain", NormalisableRange<float>(0.f, 3000.f, 0.0001), 10.f, nullptr, nullptr);
    
    state->createAndAddParameter("blend", "Blend", "Blend", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.f, nullptr, nullptr);
    
    state->createAndAddParameter("volume", "Volume", "Volume", NormalisableRange<float>(0.f, 10.f, 0.0001), 1.f, nullptr, nullptr);
    
    state->createAndAddParameter("tone", "Tone", "Tone", NormalisableRange<float>(1000.f, 20000.f, 1.f), 20000.f, nullptr, nullptr);
    
    state->createAndAddParameter("clip", "Clip Type", "Clip Type", NormalisableRange<float>(1.f, 3.f, 1.f), 3.f, nullptr, nullptr);
    
    
//    state->state = ValueTree("drive");
//    state->state = ValueTree("range");
    state->state = ValueTree("gain");
    state->state = ValueTree("blend");
    state->state = ValueTree("volume");
    state->state = ValueTree("tone");
    state->state = ValueTree("clip");
    
    desc = new PluginDescription();
    desc->manufacturerName = "Rosenfeld Audio";
    
}

DistortionAudioProcessor::~DistortionAudioProcessor()
{
}

//==============================================================================
const String DistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionAudioProcessor::setCurrentProgram (int index)
{
}

const String DistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
}

void DistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void DistortionAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    dsp::AudioBlock<float> block(buffer);
//    float drive = *state->getRawParameterValue("drive");
//    float range = *state->getRawParameterValue("range");
    float gain = *state->getRawParameterValue("gain");
    float blend = *state->getRawParameterValue("blend");
    float volume = *state->getRawParameterValue("volume");
    //float hard_thresh = 0.75f;
    int clipFxn = (int) *state->getRawParameterValue("clip");
    std::cout << clipFxn;
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for(int sample = 0; sample < buffer.getNumSamples(); sample++){
            
            float clean = *channelData;
            
            *channelData *= gain;
            
            switch(clipFxn){
                case ATAN:
                    *channelData = (2.f / float_Pi) * atan(*channelData);
                case TANH:
                    *channelData = tanh(*channelData * 0.5f);
                case SOFTMAX:
                    *channelData = (2.f / (1.f + exp(-1.f * (*channelData))) - 1.f) / 30;
            }

            *channelData = volume * (((blend * (*channelData)) + (clean * (1.f - blend))) / 2.f);
            channelData++;
        }
    }
    updateParameters();
    lowPassFilter.process(dsp::ProcessContextReplacing<float> (block));
}

AudioProcessorValueTreeState& DistortionAudioProcessor::getState(){
    return *state;
}

void DistortionAudioProcessor::updateParameters(){
    float cutoff = *state->getRawParameterValue("tone");
    *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), cutoff, 0.1f);
}



//==============================================================================
bool DistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DistortionAudioProcessor::createEditor()
{
    return new DistortionAudioProcessorEditor (*this);
}

//==============================================================================
void DistortionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);
}

void DistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    
    if(tree.isValid()){
        state->state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionAudioProcessor();
}
