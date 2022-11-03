/**
 * @file noise.hpp
 * @author Tom Clayton
 * @brief Noise Generator class
 * 
 * @version 0.1
 * @date 2022-11-03
 * 
 * 
 */

#include<cstdlib>
#include <ctime>

class Noise
{
public:
    /**
     * @brief Construct a new Noise object
     * 
     */
    Noise();

    /**
     * @brief Destroy the Noise object
     * 
     */
    ~Noise() {}

    /**
     * @brief Get the next noise sample
     * 
     */
    float get_sample();
};