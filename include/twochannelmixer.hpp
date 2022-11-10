/**
 * @file twochannelmixer.hpp
 * @author Tom Clayton
 * @brief Two channel 'crossfader' style mixer where control signal
 *        between -0.1 and 0.1 determines ratio of two signals.
 *        Rise/fall is exponential.
 * @version 0.1
 * @date 2022-11-09
 * 
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#pragma once

#include <cmath>

#include "sampletypes.hpp"

#define QUARTER_PI 0.785398163397

/**
 * @brief Mix two samples according to crossfader position and return
 *        output sample.
 * 
 * @param input_a 
 * @param input_b 
 * @param fader 
 * @return audio_sample_t sample
 */
audio_sample_t mix(
    audio_sample_t input_a,
    audio_sample_t input_b,
    control_sample_t fader
);



