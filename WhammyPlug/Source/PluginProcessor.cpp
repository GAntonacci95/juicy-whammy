/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WhammyPlugAudioProcessor::WhammyPlugAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
}

WhammyPlugAudioProcessor::~WhammyPlugAudioProcessor()
{
}

//==============================================================================
const String WhammyPlugAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WhammyPlugAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WhammyPlugAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WhammyPlugAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WhammyPlugAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WhammyPlugAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WhammyPlugAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WhammyPlugAudioProcessor::setCurrentProgram (int index)
{
}

const String WhammyPlugAudioProcessor::getProgramName (int index)
{
    return {};
}

void WhammyPlugAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WhammyPlugAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    interlaced_size = -1;
    interlaced = nullptr;
    processed = nullptr;
    
    pitchShifter = new SoundTouch();
    pitchShifter->setSampleRate((uint)sampleRate);

    // HI latency? -> combo (QUICK = true, AA = false)
    pitchShifter->setSetting(SETTING_USE_QUICKSEEK, false);
    pitchShifter->setSetting(SETTING_USE_AA_FILTER, true);
}

void WhammyPlugAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    pitchShifter->clear();
    pitchShifter->flush();
    delete pitchShifter;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WhammyPlugAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void WhammyPlugAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
//     ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

//    // EXPERIMENT 1: SIMPLE TRANSCRIPTION
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        buffer.copyFrom(channel, 0, buffer.getReadPointer(channel), buffer.getNumSamples());
//    }
    if (interlaced == nullptr) // allora devo inizializzare
    {
        interlaced_size = totalNumInputChannels * buffer.getNumSamples();
        interlaced = new float[interlaced_size];
        processed = new float[interlaced_size];

        pitchShifter->setChannels(totalNumInputChannels);

        pitchShifter->setTempoChange(0);
        pitchShifter->setRateChange(0);
        // ALTER HERE, setup via SLIDER
        pitchShifter->setPitchSemiTones(+5);
    }
    // svuoto la memoria per il processing
    std::fill(interlaced, interlaced + (interlaced_size * (sizeof(float) / 4)), 0);
    std::fill(processed, processed + (interlaced_size * (sizeof(float) / 4)), 0);
    
    // dai buffer disponibili creo interlacciamento e lo scrivo in memoria interlaced
    AudioDataConverters::interleaveSamples(
       buffer.getArrayOfReadPointers(), interlaced, buffer.getNumSamples(), totalNumInputChannels);

//   // EXPERIMENT 2: ANOTHER TRANSCRIPTION (\w interlacing and deinterlacing)
//   //                     + interlaced_size * #words_per_array
//    std::copy(interlaced, interlaced + (interlaced_size * (sizeof(float) / 4)), processed);
    
    // EXPERIMENT 3: LIBRARY USAGE
    // processo memoria interlaced in memoria processed
    pitchShifter->putSamples(interlaced, interlaced_size);
    while (pitchShifter->receiveSamples(processed, interlaced_size) > 0)
    {
        // deinterlaccia processed e scrive in buffer output
        AudioDataConverters::deinterleaveSamples(
            processed, buffer.getArrayOfWritePointers(), buffer.getNumSamples(), totalNumInputChannels);
    }
}

//==============================================================================
bool WhammyPlugAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WhammyPlugAudioProcessor::createEditor()
{
    return new WhammyPlugAudioProcessorEditor (*this);
}

//==============================================================================
void WhammyPlugAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WhammyPlugAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WhammyPlugAudioProcessor();
}
