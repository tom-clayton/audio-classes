/**
 * @file EnvGen.cpp
 * @author Tom Clayton
 * @brief An exponential ADSR Envelope Generator.
 * @version 0.1
 * @date 2022-10-31
 *
 * GNU GENERAL PUBLIC LICENSE Version 3
 */

#include "envgen.hpp"
    
EnvGen::EnvGen(uint32_t sample_rate)
    :output(0.0f),
     state(STATE_IDLE)
{
    sample_time = 1.0f / sample_rate;
}

void EnvGen::trigger()
{
    state = STATE_ATTACK;
    output = 0.0f;
}

void EnvGen::gate_release()
{
    state = STATE_RELEASE;
}

control_sample_t EnvGen::get_sample(
    delta_time_t attack,
    delta_time_t decay,
    delta_time_t sustain,
    delta_time_t release
)
{
    switch(state){
        case STATE_ATTACK:
            if (attack == 0.0f){
                output = LEVEL;
                state = STATE_DECAY;
            } else {
                delta_time_t a = attack / (attack + sample_time);
                output = a * output + (1.0f-a) * LEVEL * 1.5;
                if (output >= (LEVEL - THRESHOLD)){
                    state = STATE_DECAY;
                }
            }
            break;
        case STATE_DECAY:
            if (decay == 0.0f){
                output = sustain;
                state = STATE_SUSTAIN;
            } else {
                delta_time_t a = decay / (decay + sample_time);
                output = a * output + (1.0f-a) * (sustain - (LEVEL - sustain) * 0.5f);
                if (output <= sustain + THRESHOLD){
                    state = STATE_SUSTAIN;
                    output = sustain;
                }
            }
            break;
        case STATE_RELEASE:
            if (release == 0.0f){
                output = 0.0f;
                state = STATE_IDLE;
            } else {
                delta_time_t a = release / (release + sample_time);
                output = a * output + (1.0f-a) * (sustain * -0.5f);
                if (output <= THRESHOLD){
                    state = STATE_IDLE;
                    output =  0.0f;
                }
            }
            break;
    }

    return output;
}