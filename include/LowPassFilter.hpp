/**
 * @file LowPassFilter.hpp
 * @author Tom Clayton
 * @brief A 2nd order low pass filter with cut-off and 
 *        resonance controls.
 * 
 * @version 0.1
 * @date 2022-10-31
 * 
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
     * @return sample 
     */
    float process_sample(float sample, float cutoff, float resonance);
};