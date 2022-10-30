/*
    EnvGen.cpp - An ADSR Envelope Generator.
    2022 - Tom Clayton
*/

#include <cstdint>
#include <cmath>

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
    float sample_time;
    float output;
    State state;

public:
    EnvGen(uint32_t sample_rate);
    ~EnvGen() {}

    void trigger();
    void gate_release();

    float advance(
        float attack,
        float decay,
        float sustain,
        float release
    );
};