/* oscillator.cpp 
   Command-line waveform generator example 
   Tom Clayton 2022
*/

#include <cstdint>
#include <iostream>
#include <cmath>
#include "BandLimitedOsc.hpp"
#include <sndfile.h>

enum {
	ARG_PROGNAME,
	ARG_OUTFILE,
	ARG_WAVETYPE,
	ARG_FREQ,
	ARG_LENGTH,
	ARG_NARGS
};

enum {
	WAV_TRIANGLE,
	WAV_SAWTOOTH,
	WAV_SQUARE,
	WAV_SINE,
	WAV_NARGS
};

#define SAMPLERATE	44100
#define FORMAT 		(SF_FORMAT_WAV | SF_FORMAT_PCM_16) // 16 bit wav
#define CHANNELS	1
#define HEADROOM	1.0 // in dB

#define BUFFER_SIZE 4096L

using namespace std;

int main(int argc, char** argv)
{
	if (argc != ARG_NARGS){
		cout << "Usage: oscilllator filename wavetype freq(Hz) length(s)" << endl;
		cout << "Where wavetype is:" << endl;
		cout << "\t0: Triangle" << endl;
		cout << "\t1: Sawtooth" << endl;
		cout << "\t2: Square" << endl;
		cout << "\t3: Sine" << endl;
		return 1;
	}

	uint64_t n_samples = (uint64_t)(atof(argv[ARG_LENGTH]) * SAMPLERATE);
	int16_t buffer[BUFFER_SIZE];
    float scale = pow(10, (0-HEADROOM) / 20) * 32767;
	
    BandLimitedOsc osc(SAMPLERATE);
	float frequency = atof(argv[ARG_FREQ]);

	float (BandLimitedOsc::* get_sample)();

	switch (ARG_WAVETYPE){
		case WAV_TRIANGLE:
			get_sample = &BandLimitedOsc::triangle_sample;
			break;
		case WAV_SAWTOOTH:
			get_sample = &BandLimitedOsc::sawtooth_sample;
			break;
		case WAV_SQUARE:
			get_sample = &BandLimitedOsc::square_sample;
			break;
		case WAV_SINE:
			get_sample = &BandLimitedOsc::sine_sample;
			break;
	}

	SNDFILE *soundfile;
	SF_INFO	info;

	info.samplerate = SAMPLERATE;
	info.format = FORMAT;
	info.channels = CHANNELS;

	soundfile = sf_open(argv[ARG_OUTFILE], SFM_WRITE, &info);

	do{
		uint64_t b_samples = n_samples < BUFFER_SIZE ? n_samples : BUFFER_SIZE;

		for (uint64_t i=0; i<b_samples; i++){
			osc.advance(frequency);
			buffer[i] = (int16_t) ((osc.*get_sample)() * scale);
		}
		
		if (sf_writef_short(soundfile, buffer, b_samples) != b_samples){
			std::cerr << "Error: write fail\n";
			return 1;
		}
		n_samples -= b_samples;
	
	}while(n_samples);

	sf_close(soundfile);

	return 0;
}