/**
 * @file Waveforms.cpp
 * @author Tom Clayton
 * @brief Waveform classes used by BandLimitedOsc class
 * @version 0.1
 * @date 2022-10-31
 * 
 */
#include "Waveforms.hpp"

Waveform::Waveform(float *arg_wavetable, table_step_t arg_table_size)
    :wavetable(arg_wavetable),
     table_size(arg_table_size),
     master_position(0),
     step_size(0)
{

}

Waveform::~Waveform()
{
    delete [] harmonics;
    delete [] amplitudes;
    delete [] table_positions;
}

void Waveform::create_arrays()
{
    harmonics = new harmonic_t[n_harmonics];
    amplitudes = new amplitude_t[n_harmonics];
    table_positions = new table_step_t[n_harmonics];
}

float Waveform::calculate_sample(table_step_t new_master_position, table_step_t step_size)
{
    float sample = 0.0f;

    // If master position isn't where expected, restart from new master position.
    if (new_master_position != master_position + step_size + phase_offset){
        for(harmonic_t i=0; i<n_harmonics; i++){
            table_positions[i] = new_master_position * harmonics[i] + phase_offset;
            table_positions[i] %= table_size;
            sample += wavetable[table_positions[i]] * amplitudes[i];
        }

    } else {
        for(harmonic_t i=0; i<n_harmonics; i++){
            table_positions[i] += step_size * harmonics[i];
            table_positions[i] %= table_size;
            sample += wavetable[table_positions[i]] * amplitudes[i];
        }
    }
    master_position = new_master_position;
    return sample;
}

Triangle::Triangle(float *arg_wavetable, table_step_t arg_table_size, harmonic_t max_harmonic) 
        : Waveform(arg_wavetable, arg_table_size)
{
    n_harmonics = max_harmonic / 2;
    phase_offset = arg_table_size / 4;
    create_harmonics();
}

void Triangle::create_harmonics()
{    
    create_arrays();

    harmonic_t harmonic = 1; 
    amplitude_t amp_factor = 0.0f;

    for (harmonic_t i=0; i<n_harmonics; i++){
        harmonics[i] = harmonic;
        amplitudes[i] = 1.0f / (harmonic * harmonic);
        amp_factor += amplitudes[i];
        table_positions[i] = phase_offset;
        harmonic += 2;
    }

    for (harmonic_t i=0; i<n_harmonics; i++){
        amplitudes[i] /= amp_factor;
    }
}

Sawtooth::Sawtooth(float *arg_wavetable, table_step_t arg_table_size, harmonic_t max_harmonic) 
        : Waveform(arg_wavetable, arg_table_size)
{
    n_harmonics = max_harmonic;
    phase_offset = 0;
    create_harmonics();
}

void Sawtooth::create_harmonics()
{    
    create_arrays();
    
    harmonic_t harmonic = 1;
    amplitude_t amp_factor = 0.0f;

    for (harmonic_t i=0; i<n_harmonics; i++){
        harmonics[i] = harmonic;
        amplitudes[i] = 1.0f / harmonic;
        amp_factor += amplitudes[i];
        table_positions[i] = 0;
        harmonic++;
    }
    amp_factor *= 0.5;

    for (harmonic_t i=0; i<n_harmonics; i++){
        amplitudes[i] /= amp_factor;
    }
}

Square::Square(float *arg_wavetable, table_step_t arg_table_size, harmonic_t max_harmonic) 
        : Waveform(arg_wavetable, arg_table_size)
{
    n_harmonics = max_harmonic / 2;
    phase_offset = 0;
    create_harmonics();
}

void Square::create_harmonics()
{   
    create_arrays(); 

    harmonic_t harmonic = 1;
    amplitude_t amp_factor = 0.0f;

    for (harmonic_t i=0; i<n_harmonics; i++){
        harmonics[i] = harmonic;
        amplitudes[i] = 1.0f / harmonic;
        amp_factor += amplitudes[i];
        table_positions[i] = 0;
        harmonic += 2;
    }

    amp_factor *= 0.5;

    for (harmonic_t i=0; i<n_harmonics; i++){
        amplitudes[i] /= amp_factor;
    }
}

Sine::Sine(float *arg_wavetable, table_step_t arg_table_size) 
        : Waveform(arg_wavetable, arg_table_size)
{
    n_harmonics = 1;
    phase_offset = 0;
    create_harmonics();
}

void Sine::create_harmonics()
{
    harmonics = new harmonic_t(1);
    amplitudes = new amplitude_t(1);
    table_positions = new table_step_t(0);
}