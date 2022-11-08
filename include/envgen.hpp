/**
 * @file EnvGen.hpp
 * @author Tom Clayton
 * @brief An exponential ADSR Envelope Generator.
 * @version 0.1
 * @date 2022-10-31
 *
 * GNU GENERAL PUBLIC LICENSE Version 3 
 */

#pragma once

#include <cstdint>
#include <cmath>

#include "sampletypes.hpp"

#define LEVEL 1.0f
#define THRESHOLD 0.001f

typedef enum {
    STATE_IDLE,
    STATE_ATTACK,
    STATE_DECAY,
    STATE_SUSTAIN,
    STATE_RELEASE,
    STATE_NSTATES
} State;

class EnvGen
{
private:
    control_sample_t sample_time;
    control_sample_t output;
    State state;

public:
    /**
     * @brief Construct a new Env Gen object
     * 
     * @param sample_rate 
     */
    EnvGen(uint32_t sample_rate);

    /**
     * @brief Destroy the Env Gen object
     * 
     */
    ~EnvGen() {}

    /**
     * @brief Start from zero in the attack phase. 
     * 
     */
    void trigger();

    /**
     * @brief Move to the release phase.
     * 
     */
    void gate_release();

    /**
     * @brief Advance forward one time division and return the output sample.
     * 
     * @param attack 
     * @param decay 
     * @param sustain 
     * @param release 
     * @return control_sample_t - sample 
     */
    control_sample_t advance(
        delta_time_t attack,
        delta_time_t decay,
        delta_time_t sustain,
        delta_time_t release
    );
};