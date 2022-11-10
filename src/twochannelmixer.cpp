/**
 * @file twochannelmixer.cpp
 * @author Tom Clayton
 * @brief Two channel 'crossfader' style mixer where control signal
 *        between -0.1 and 0.1 determines ratio of two signals.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "twochannelmixer.hpp"

TwoChannelMixer::TwoChannelMixer()
{
}

TwoChannelMixer::~TwoChannelMixer()
{
}

audio_sample_t TwoChannelMixer::get_sample(
    audio_sample_t input_a,
    audio_sample_t input_b,
    control_sample_t fader
)
{
    floating_point_t pheta = (fader + 1) * QUARTER_PI;
    floating_point_t sin_pheta = sin(pheta);
    floating_point_t cos_pheta = cos(pheta);

    return (input_a * sin_pheta + input_b * cos_pheta) / (sin_pheta + cos_pheta);
    
    //linear:
    //return (fader - 1) * -0.5 * input_a + (fader + 1) * 0.5 * input_b;
}