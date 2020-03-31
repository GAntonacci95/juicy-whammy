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
    // dimensione = #canali_in * samplesPerBlock (dimensione_blocco_standard)
    int interlaced_size;
    // numero campioni processati sull'intero blocco
    int tmp_processed_len;
    // vettori che servono per il processing
    float* interlaced;
    float* processed;
    
    // dimensione perchè la libreria vuole uno stream interlacciato, cioè:
    // usa un solo vettore di dimensione superiore che alterna i campioni di ogni ch
    SoundTouch* pitchShifter;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WhammyPlugAudioProcessor)
};
