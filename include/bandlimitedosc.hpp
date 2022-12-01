/**
 * @file BandLimitedOsc.hpp
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

#pragma once

#include <cstdint>
#include <cmath>

#include "sampletypes.hpp"
#include "Waveforms.hpp"

#define TABLE_SIZE      65536
#define MAX_FREQ        1662.0f    // includes octave 6
#define DEFAULT_FREQ    440.0f
#define TUNING_A4       440.0f

/**
 * @brief Band Limited Oscillator
 * 
 */
class BandLimitedOsc
{
private:
    uint32_t sample_rate;
    table_step_t step_size;
    table_step_t table_position;
    uint16_t cents;

    audio_sample_t wavetable[TABLE_SIZE];
    floating_point_t size_ovr_srate;

    Triangle *triangle;
    Sawtooth *sawtooth;
    Square *square;
    Sine *sine;

    /**
     * @brief Create the sine wavetable
     * 
     */
    void create_wavetable();

public:
    /**
     * @brief Construct a new Band Limited Osc object
     * 
     * @param sample_rate 
     */
    BandLimitedOsc(uint32_t sample_rate);
    
    /**
     * @brief Destroy the Band Limited Osc object
     * 
     */
    ~BandLimitedOsc();

    /**
     * @brief Advance through wavetable, using frequency in hertz 
     * 
     * Update step size, advance and wrap the table postition 
     * 
     * @param frequency 
     */
    void advance(floating_point_t frequency);

    /**
     * @brief Calculate frequency from note midi-number and 
     *        amount to detune. Advance through wavetable
     * 
     * @param midi_number midi-number of note
     * @param detune detune in cents, from -50 to +50
     */
    void advance(uint8_t midi_number, int8_t detune);

    /**
     * @brief Calculate next triangle sample 
     * 
     * @return audio_sample_t sample
     */
    audio_sample_t triangle_sample();

    /**
     * @brief Calculate next sawtooth sample 
     * 
     * @return audio_sample_t sample
     */
    audio_sample_t sawtooth_sample();
    
    /**
     * @brief Calculate next square sample 
     * 
     * @return audio_sample_t sample
     */
    audio_sample_t square_sample();
    
    /**
     * @brief Calculate next sine sample 
     * 
     * @return audio_sample_t sample
     */
    audio_sample_t sine_sample();
};


