/* envelope.cpp 
   Command-line envelope example 
   creates text file to test EnvGen class
   Tom Clayton 2022
*/

#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "EnvGen.hpp"

enum {
	ARG_PROGNAME,
	ARG_FILENAME,
    ARG_LENGTH,
	ARG_ATTACK,
	ARG_DECAY,
	ARG_SUSTAIN,
	ARG_RELEASE,
	ARG_NARGS
};

#define SAMPLERATE	100

using namespace std;

int main(int argc, char** argv)
{
	if (argc != ARG_NARGS){
		cout << "Usage: envelope filename keypress(s) attack(s) decay(s) sustain(0-1) release(s)" << endl;
		return 1;
	}
	
    EnvGen envelope(SAMPLERATE);
	float attack = atof(argv[ARG_ATTACK]);
	float decay = atof(argv[ARG_DECAY]);
	float sustain = atof(argv[ARG_SUSTAIN]);
	float release = atof(argv[ARG_RELEASE]);
    uint64_t length = atof(argv[ARG_LENGTH]) * SAMPLERATE;

	ofstream file;
    file.open(argv[ARG_FILENAME]);
	
	float output;
    
    uint64_t samples = 0;
    bool key_released = false;
    envelope.trigger();
    
    while(true){
        output = envelope.advance(attack, decay, sustain, release);
        file << setprecision(3) << output << endl;
        if (!key_released){
            if (++samples == length){
                envelope.gate_release();
                key_released = true;
            }
        } else if(output <= 0.0f){
            break;
        }
    }

	file.close();

	return 0;
}