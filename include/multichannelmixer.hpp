/**
 * @file multichannelmixer.hpp
 * @author Tom Clayton
 * @brief Multi channel 'upfader' style mixer where control signal
 *        of channel controls amplitude of signal.
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "sampletypes.hpp"

class MultiChannelMixer
{
private:
    audio_sample_t total_audio;
    control_sample_t total_level;
public:
    /**
     * @brief Construct a new Multi Channel Mixer object
     * 
     */
    MultiChannelMixer();

    /**
     * @brief Destroy the Multi Channel Mixer object
     * 
     */
    ~MultiChannelMixer();

    /**
     * @brief Add an input to be summed.
     * 
     * @param sample 
     * @param level 
     */
    void add_input(audio_sample_t sample, control_sample_t level);

    /**
     * @brief Get the mixer's output sample
     * 
     * @return audio_sample_t sample
     */
    audio_sample_t get_sample();
};