/**
 * @file LowPassFilter.cpp
 * @author Tom Clayton
 * @brief A 2nd order low pass filter with cut-off and 
 *        resonance controls.
 * 
 * @version 0.1
 * @date 2022-10-31
 * 
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#include "lowpassfilter.hpp"

LowPassFilter::LowPassFilter(uint32_t sample_rate)
    :ff_z1(0),
    ff_z2(0),
    fb_z1(0),
    fb_z2(0)
{
    twopi_ovr_srate = (2 * M_PI) / sample_rate;
}

audio_sample_t LowPassFilter::get_sample(
    audio_sample_t input, 
    frequency_t arg_cutoff, 
    control_sample_t arg_qfactor
)
{
    if (cutoff != arg_cutoff || qfactor != arg_qfactor){
        cutoff = arg_cutoff;
        qfactor = arg_qfactor;
        calculate_coeffs();
    }
    audio_sample_t output = (a0 * input)\
                    + (a1 * ff_z1)\
                    + (a2 * ff_z2)\
                    - (b1 * fb_z1)\
                    - (b2 * fb_z2);

    ff_z2 = ff_z1;
    fb_z2 = fb_z1;
    ff_z1 = input;
    fb_z1 = output;
    return output;
}

void LowPassFilter::calculate_coeffs()
{
    filter_coef_t theta = twopi_ovr_srate * cutoff;
    filter_coef_t d;
    if (qfactor){
        d = 1.0f / qfactor;
    } else {
        d = 1.0f / 0.00001f;
    }
    filter_coef_t beta = 0.5f * (1.0f - ((d / 2.0f) * sin(theta)))\
                         / (1.0f + ((d/ 2.0f) * sin(theta)));
    filter_coef_t gamma = (0.5f + beta) * cos(theta);

    a1 = 0.5f + beta - gamma;
    a0 = a2 = a1 / 2.0f;
    b1 = -2.0f * gamma;
    b2 = 2.0f * beta;
}