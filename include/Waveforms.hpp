/**
 * @file Waveforms.hpp
 * @author Tom Clayton
 * @brief Waveform classes used by BandLimitedOsc class
 * @version 0.1
 * @date 2022-10-31
 * 
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#pragma once

#include <cstdint>

#include "sampletypes.hpp"

typedef uint16_t harmonic_t;
typedef uint32_t table_step_t;
typedef float amplitude_t;

/**
 * @brief Waveform abstract class.
 * 
 */
class Waveform
{
private:
    audio_sample_t *wavetable;
    table_step_t table_size;
    table_step_t master_position;
    table_step_t step_size;
    
    /**
     * @brief Create the waveform's harmonics table.
     * 
     */
    virtual void create_harmonics() = 0;

protected:
    harmonic_t n_harmonics;
    harmonic_t *harmonics;
    amplitude_t *amplitudes;
    table_step_t *table_positions;
    table_step_t phase_offset;
    
    /**
     * @brief Create empty arrays for the harmonics.
     * 
     */
    void create_arrays();

public:
    /**
     * @brief Construct a new Waveform object.
     * 
     * @param wavetable
     * @param table_size
     */
    Waveform(audio_sample_t* wavetable, table_step_t table_size);

    /**
     * @brief Destroy the Waveform object.
     * 
     */
    virtual ~Waveform();

    /**
     * @brief Calculate the next sample.
     * 
     * @param new_master_position 
     * @param step_size 
     * @return audio_sample_t sample  
     */
    audio_sample_t calculate_sample(
                            table_step_t new_master_position, 
                            table_step_t step_size
                        );
};

/**
 * @brief Triangle wavefrom class.
 * 
 */
class Triangle : public Waveform
{
public:
    /**
     * @brief Construct a new Triangle object.
     * 
     * @param wavetable 
     * @param table_size 
     * @param max_harmonic 
     */
    Triangle(
        audio_sample_t* wavetable, 
        table_step_t table_size, 
        harmonic_t max_harmonic
    );
    
    /**
     * @brief Destroy the Triangle object.
     * 
     */
    virtual ~Triangle(){}

private:
    /**
     * @brief Create the waveform's harmonics table.
     * 
     */
    void create_harmonics() override;
};

/**
 * @brief Sawtooth waveform class.
 * 
 */
class Sawtooth : public Waveform
{
public:
    /**
     * @brief Construct a new Sawtooth object.
     * 
     * @param wavetable 
     * @param table_size 
     * @param max_harmonic 
     */
    Sawtooth(
        audio_sample_t* wavetable, 
        table_step_t table_size, 
        harmonic_t max_harmonic
    );

    /**
     * @brief Destroy the Sawtooth object.
     * 
     */
    virtual ~Sawtooth(){}

private:
    /**
     * @brief Create the waveform's harmonics table.
     * 
     */
    void create_harmonics() override;
};

/**
 * @brief Square waveform class.
 * 
 */
class Square : public Waveform
{
public:
    /**
     * @brief Construct a new Square object.
     * 
     * @param wavetable 
     * @param table_size 
     * @param max_harmonic 
     */
    Square(
        audio_sample_t* wavetable, 
        table_step_t table_size, 
        harmonic_t max_harmonic
    );

    /**
     * @brief Destroy the Square object.
     * 
     */
    virtual ~Square(){}

private:
    /**
     * @brief Create the waveform's harmonics table.
     * 
     */
    void create_harmonics() override;
};

/**
 * @brief Sine waveform class.
 * 
 */
class Sine : public Waveform
{
public:
    /**
     * @brief Construct a new Sine object.
     * 
     * @param wavetable 
     * @param table_size 
     * @param max_harmonic 
     */
    Sine(audio_sample_t* wavetable, table_step_t table_size);
    
    /**
     * @brief Destroy the Sine object.
     * 
     */
    virtual ~Sine(){}

private:
    /**
     * @brief Create the waveform's harmonics table.
     * 
     */
    void create_harmonics() override;
};

