/**
 * @file twochannelmixer.hpp
 * @author Tom Clayton
 * @brief Two channel 'crossfader' style mixer where control signal
 *        between -0.1 and 0.1 determines ratio of two signals.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <cmath>

#include "sampletypes.hpp"

#define QUARTER_PI 0.785398163397

class TwoChannelMixer
{
private:
    /* data */
public:
    /**
     * @brief Construct a new Two Way Mixer object
     * 
     */
    TwoChannelMixer();

    /**
     * @brief Destroy the Two Way Mixer object
     * 
     */
    ~TwoChannelMixer();

    /**
     * @brief Get the mixer's output sample
     * 
     * @param input_a 
     * @param input_b 
     * @param fader 
     * @return audio_sample_t sample
     */
    audio_sample_t get_sample(
        audio_sample_t input_a,
        audio_sample_t input_b,
        control_sample_t fader
    );
};


