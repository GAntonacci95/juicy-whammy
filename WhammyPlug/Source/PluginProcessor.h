/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SoundTouch.h"

using namespace soundtouch;

//==============================================================================
/**
*/
class WhammyPlugAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    WhammyPlugAudioProcessor();
    ~WhammyPlugAudioProcessor();
    
    // the next two variables are introduced in order to listen to the sliders' values
/*    double pitch_value = 0; // takes vertical slider value - controls the actual pitch shifting
    double knob_value = 0; // takes knob value - controls the choice of the max number of semitones for the pitch shift
  */  
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    SoundTouch* shifterL;
    SoundTouch* shifterR;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WhammyPlugAudioProcessor)
};
