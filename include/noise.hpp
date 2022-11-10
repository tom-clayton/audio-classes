/**
 * @file noise.hpp
 * @author Tom Clayton
 * @brief Noise Generator class
 * 
 * @version 0.1
 * @date 2022-11-03
 * 
 * 
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#pragma once

#include<cstdlib>
#include <ctime>

#include "sampletypes.hpp"

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
     * @return audio_sample_t sample
     */
    audio_sample_t get_sample();
};