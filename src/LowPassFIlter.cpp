/**
 * @file LowPassFilter.cpp
 * @author Tom Clayton
 * @brief A 2nd order low pass filter with cut-off and 
 *        resonance controls.
 * 
 * @version 0.1
 * @date 2022-10-31
 * 
 */
#include "LowPassFilter.hpp"

LowPassFilter::LowPassFilter(uint32_t sample_rate)
    :ff_z1(0),
    ff_z2(0),
    fb_z1(0),
    fb_z2(0)
{
    twopi_ovr_srate = (2 * M_PI) / sample_rate;
}

float LowPassFilter::process_sample(
    float sample, 
    float arg_cutoff, 
    float arg_qfactor
)
{
    if (cutoff != arg_cutoff || qfactor != arg_qfactor){
        cutoff = arg_cutoff;
        qfactor = arg_qfactor;
        calculate_coeffs();
    }
    float output = (a0 * sample)\
                    + (a1 * ff_z1)\
                    + (a2 * ff_z2)\
                    - (b1 * fb_z1)\
                    - (b2 * fb_z2);

    ff_z2 = ff_z1;
    fb_z2 = fb_z1;
    ff_z1 = sample;
    fb_z1 = output;
    return output;
}

void LowPassFilter::calculate_coeffs()
{
    float theta = twopi_ovr_srate * cutoff;
    float d;
    if (qfactor){
        d = 1.0f / qfactor;
    } else {
        d = 1.0f / 0.00001f;
    }
    float beta = 0.5f * (1.0f - ((d / 2.0f) * sin(theta)))\
                         / (1.0f + ((d/ 2.0f) * sin(theta)));
    float gamma = (0.5f + beta) * cos(theta);

    a1 = 0.5f + beta - gamma;
    a0 = a2 = a1 / 2.0f;
    b1 = -2.0f * gamma;
    b2 = 2.0f * beta;
}