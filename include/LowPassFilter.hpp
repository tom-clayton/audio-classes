/**
 * @file LowPassFilter.hpp
 * @author Tom Clayton
 * @brief A 2nd order low pass filter with cut-off and 
 *        resonance controls.
 * 
 * @version 0.1
 * @date 2022-10-31
 * 
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#pragma once

#include <cstdint>
#include <cmath>

#include "sampletypes.hpp"

class LowPassFilter
{
private:
    filter_coef_t twopi_ovr_srate;
    frequency_t cutoff;
    control_sample_t qfactor;

    filter_coef_t a0;
    filter_coef_t a1;
    filter_coef_t a2;
    filter_coef_t b1;
    filter_coef_t b2;

    audio_sample_t ff_z1;
    audio_sample_t ff_z2;
    audio_sample_t fb_z1;
    audio_sample_t fb_z2;

    /**
     * @brief caluclate the filter's coefficients
     * 
     */
    void calculate_coeffs();

public:
    /**
     * @brief Construct a new Low Pass Filter object
     * 
     * @param sample_rate 
     */
    LowPassFilter(uint32_t sample_rate);

    /**
     * @brief Destroy the Low Pass Filter object
     * 
     */
    ~LowPassFilter() {}

    /**
     * @brief Feed one sample through the filter and return calulated
     *        output sample.
     * 
     * @param sample 
     * @param cutoff 
     * @param resonance 
     * @return audio_sample_t sample 
     */
    audio_sample_t get_sample(
        audio_sample_t sample, 
        frequency_t cutoff, 
        control_sample_t resonance
    );
};