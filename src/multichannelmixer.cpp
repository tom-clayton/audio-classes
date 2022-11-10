/**
 * @file multichannelmixer.cpp
 * @author Tom Clayton
 * @brief Multi channel 'upfader' style mixer where control signal
 *        of channel controls amplitude of signal.
 * @version 0.1
 * @date 2022-11-09
 * 
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#include "multichannelmixer.hpp"

MultiChannelMixer::MultiChannelMixer()
{
}

MultiChannelMixer::~MultiChannelMixer()
{
}

void MultiChannelMixer::add_input(audio_sample_t sample, control_sample_t level)
{
    total_audio += sample * level;
    total_level += level;
}

audio_sample_t MultiChannelMixer::get_sample()
{
    audio_sample_t output = total_audio / total_level;
    total_audio = total_level = 0;
    return output;
}
