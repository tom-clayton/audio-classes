/**
 * @file noise.cpp
 * @author Tom Clayton
 * @brief Noise Generator class
 * 
 * @version 0.1
 * @date 2022-11-03
 * 
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#include "noise.hpp"

Noise::Noise()
{
    srand(time(0));
}

audio_sample_t Noise::get_sample()
{
    return rand();
}