/**
 * @file noise.cpp
 * @author Tom Clayton
 * @brief Noise Generator class
 * 
 * @version 0.1
 * @date 2022-11-03
 * 
 * 
 */

#include "Noise.hpp"

Noise::Noise()
{
    srand(time(0));
}

float Noise::get_sample()
{
    return rand();
}