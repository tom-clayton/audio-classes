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
 * 
 */

#include <cstdint>
#include <cmath>
#include "Waveforms.hpp"

#define TABLE_SIZE      65536
#define MAX_FREQ        1662.0f    // includes octave 6
#define DEFAULT_FREQ    440.0f

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

    float wavetable[TABLE_SIZE];
    float size_ovr_srate;

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
     * @brief Advance through wavetable  
     * 
     * Update step size, advance and wrap the table postition 
     * 
     * @param frequency 
     */
    void advance(float frequency);

    /**
     * @brief Calculate next triangle sample 
     * 
     * @return float sample
     */
    float triangle_sample();

    /**
     * @brief Calculate next sawtooth sample 
     * 
     * @return float sample
     */
    float sawtooth_sample();
    
    /**
     * @brief Calculate next square sample 
     * 
     * @return float sample
     */
    float square_sample();
    
    /**
     * @brief Calculate next sine sample 
     * 
     * @return float sample
     */
    float sine_sample();
};


