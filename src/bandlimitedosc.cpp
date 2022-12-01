/**
 * @file BandLimitedOsc.cpp
 * @author Tom Clayton
 * @brief Band Limited Oscillator class
 * 
 * Uses additive systhesis of a wavetable sinewave to create
 * triangle, sawtooth, square and sine waveforms.
 * 
 * @version 0.1
 * @date 2022-10-25
 * 
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#include "bandlimitedosc.hpp"
/**
 * @brief Set initial values, create wavetable and waveform objects
 * 
 * @param arg_sample_rate 
 */
BandLimitedOsc::BandLimitedOsc(uint32_t arg_sample_rate)
    :sample_rate(arg_sample_rate), 
     table_position(0),
     cents(0)
{
    create_wavetable();
    size_ovr_srate = TABLE_SIZE / (float)sample_rate;
    harmonic_t max_harmonic = sample_rate / MAX_FREQ;
    step_size = (table_step_t)(size_ovr_srate * DEFAULT_FREQ);

    triangle = new Triangle(wavetable, TABLE_SIZE, max_harmonic);
    sawtooth = new Sawtooth(wavetable, TABLE_SIZE, max_harmonic);
    square = new Square(wavetable, TABLE_SIZE, max_harmonic);
    sine = new Sine(wavetable, TABLE_SIZE);  
}

BandLimitedOsc::~BandLimitedOsc()
{
    delete triangle;
    delete sawtooth;
    delete square;
    delete sine;
}

void BandLimitedOsc::create_wavetable()
{
    float phase_incr = M_PI * 2 / TABLE_SIZE;
    for (int i=0; i<TABLE_SIZE; i++){
        wavetable[i] = sin(i * phase_incr);
    }
}

void BandLimitedOsc::advance(floating_point_t frequency)
{
    step_size = (table_step_t)(size_ovr_srate * frequency);
    table_position += step_size;
    table_position %= TABLE_SIZE;
}

void BandLimitedOsc::advance(uint8_t midi_number, int8_t detune)
{
    uint16_t new_cents = midi_number * 100 + detune;
    if (new_cents != cents){
        floating_point_t new_frequency = TUNING_A4 * pow(2, (new_cents-6900)/1200);
        advance(new_frequency);
        cents = new_cents;
    }
}

audio_sample_t BandLimitedOsc::triangle_sample()
{
    return triangle->calculate_sample(table_position, step_size);
}

audio_sample_t BandLimitedOsc::sawtooth_sample()
{
    return sawtooth->calculate_sample(table_position, step_size);
}

audio_sample_t BandLimitedOsc::square_sample()
{
    return square->calculate_sample(table_position, step_size);
}

audio_sample_t BandLimitedOsc::sine_sample()
{
    return sine->calculate_sample(table_position, step_size);
}


