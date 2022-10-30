/*
    LowPassFilter.hpp - A 2nd order low pass
    filter with cut-off and resonance controls.
    2022 - Tom Clayton
*/

#include <cstdint>
#include <cmath>

class LowPassFilter
{
private:
    float twopi_ovr_srate;
    float cutoff;
    float qfactor;

    float a0;
    float a1;
    float a2;
    float b1;
    float b2;

    float ff_z1;
    float ff_z2;
    float fb_z1;
    float fb_z2;

    void calculate_coeffs();

public:
    LowPassFilter(uint32_t sample_rate);
    ~LowPassFilter() {}

    float process_sample(float sample, float cutoff, float resonance);
};