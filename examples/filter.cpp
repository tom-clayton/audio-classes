/* filter.cpp 
   Command-line filter example 
   only for 16-bit 44100Hz mono wav files
   Tom Clayton 2022
   GNU GENERAL PUBLIC LICENSE Version 3
*/

#include <cstdint>
#include <iostream>
#include <cmath>
#include "LowPassFilter.hpp"
#include <sndfile.h>

enum {
	ARG_PROGNAME,
    ARG_INFILE,
	ARG_OUTFILE,
	ARG_CUTOFF,
	ARG_RESONANCE,
	ARG_NARGS
};



#define SAMPLERATE	44100
#define FORMAT 		(SF_FORMAT_WAV | SF_FORMAT_PCM_16) // 16 bit wav
#define CHANNELS	1

#define BUFFER_SIZE 4096L

using namespace std;

int main(int argc, char** argv)
{
	if (argc != ARG_NARGS){
		cout << "Usage: filter infile outfile cutoff(Hz) resonance" << endl;
		return 1;
	}

	//uint64_t n_samples = (uint64_t)(atof(argv[ARG_LENGTH]) * SAMPLERATE);

    float buffer[BUFFER_SIZE];
    float scale = pow(10, 0.05) * 32767;
	
    LowPassFilter filter(SAMPLERATE);
	float cutoff = atof(argv[ARG_CUTOFF]);
	float resonance = atof(argv[ARG_RESONANCE]);

	SNDFILE *infile, *outfile;
	SF_INFO	info;

	info.samplerate = SAMPLERATE;
	info.format = FORMAT;
	info.channels = CHANNELS;

	infile = sf_open(argv[ARG_INFILE], SFM_READ, &info);
    outfile = sf_open(argv[ARG_OUTFILE], SFM_WRITE, &info);
    
	while(uint64_t samples = sf_readf_float(infile, buffer, BUFFER_SIZE)){
		for (uint64_t i=0; i<samples; i++){
			buffer[i] = filter.process_sample(buffer[i], cutoff, resonance);
		}
		
		if (sf_writef_float(outfile, buffer, samples) != samples){
			std::cerr << "Error: write fail\n";
			return 1;
		}
	}

	sf_close(infile);
    sf_close(outfile);

	return 0;
}