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
      :AudioProcessor (BusesProperties()
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
    
    waitTokenL = new WaitableEvent();
    waitTokenR = new WaitableEvent();
    window = Window::hamming(samplesPerBlock); // / 2);
    chthL = new ChannelThread("chthL", waitTokenL, (uint)sampleRate, window);
    chthR = new ChannelThread("chthR", waitTokenR, (uint)sampleRate, window);
}

double WhammyPlugAudioProcessor::getPitchSemiTones()
{
    return currentPitch;
}

void WhammyPlugAudioProcessor::setPitchSemiTones(double pitch)
{
    currentPitch = pitch;
    chthL->setPitchSemiTones(currentPitch);
    chthR->setPitchSemiTones(currentPitch);
}

void WhammyPlugAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
    if(chthL->stopThread(10) && chthR->stopThread(10)) // 5
    {
        delete chthL;
        delete chthR;
        delete waitTokenL;
        delete waitTokenR;
        delete window;
    }
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

    if (!chthL->isConfigured() && !chthR->isConfigured())
    {
       chthL->configure(buffer.getReadPointer(0));
       chthR->configure(buffer.getReadPointer(1));

       chthL->startThread();
       chthR->startThread();
    }
    // ! notify the presence of new data
    chthL->notify();
    chthR->notify();

    // !! wait for both threads to finish
    waitTokenL->wait();
    waitTokenR->wait();

    // write to output
    // overflow in fade-out, OLA al frame successivo
    buffer.copyFrom(0, 0,
                   chthL->getReadyData()->getData(),
                   chthL->getReadyData()->getSize());
    buffer.copyFrom(1, 0,
                   chthR->getReadyData()->getData(),
                   chthR->getReadyData()->getSize());
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
