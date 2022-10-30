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
 * 
 */

#include "BandLimitedOsc.hpp"
/**
 * @brief Set initial values, create wavetable and waveform objects
 * 
 * @param arg_sample_rate 
 */
BandLimitedOsc::BandLimitedOsc(uint32_t arg_sample_rate)
    :sample_rate(arg_sample_rate), 
     table_position(0)
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

/**
 * @brief Free waveform objects
 * 
 */
BandLimitedOsc::~BandLimitedOsc()
{
    delete triangle;
    delete sawtooth;
    delete square;
    delete sine;
}

/**
 * @brief Create the sinewave wave table
 * 
 */
void BandLimitedOsc::create_wavetable()
{
    float phase_incr = M_PI * 2 / TABLE_SIZE;
    for (int i=0; i<TABLE_SIZE; i++){
        wavetable[i] = sin(i * phase_incr);
    }
}

/**
 * @brief Update step size, advance and wrap the table postition
 * 
 * @param frequency 
 */
void BandLimitedOsc::advance(float frequency)
{
    step_size = (table_step_t)(size_ovr_srate * frequency);
    table_position += step_size;
    table_position %= TABLE_SIZE;
}

/**
 * @brief Acquire the next sample from the triangle waveform object
 * 
 * @return float - triangle sample 
 */
float BandLimitedOsc::triangle_sample()
{
    return triangle->calculate_sample(table_position, step_size);
}

/**
 * @brief Acquire the next sample from the sawtooth waveform object
 * 
 * @return float - sawtooth sample 
 */
float BandLimitedOsc::sawtooth_sample()
{
    return sawtooth->calculate_sample(table_position, step_size);
}

/**
 * @brief Acquire the next sample from the square waveform object
 * 
 * @return float - square sample 
 */
float BandLimitedOsc::square_sample()
{
    return square->calculate_sample(table_position, step_size);
}

/**
 * @brief Acquire the next sample from the sine waveform object
 * 
 * @return float - sine sample 
 */
float BandLimitedOsc::sine_sample()
{
    return sine->calculate_sample(table_position, step_size);
}


