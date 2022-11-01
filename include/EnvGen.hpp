/**
 * @file EnvGen.hpp
 * @author Tom Clayton
 * @brief An exponential ADSR Envelope Generator.
 * @version 0.1
 * @date 2022-10-31
 *
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
     * @return sample 
     */
    float advance(
        float attack,
        float decay,
        float sustain,
        float release
    );
};