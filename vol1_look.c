#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "vol.h"

// Function to scale a sound sample using a volume_factor
// in the range of 0.00 to 1.00.
static inline int16_t scale_sample(int16_t sample, float volume_factor) {
	return (int16_t) (volume_factor * (float) sample);
}

int main() {
	clock_t total = clock();
	// Allocate memory for large in and out arrays
	int16_t*	in;
	int16_t*	out;
	in = (int16_t*) calloc(SAMPLES, sizeof(int16_t));
	out = (int16_t*) calloc(SAMPLES, sizeof(int16_t));
	
	int		x;
	int		ttl;
	int16_t lookup[65536];	//size based on rand % value


	// Seed the pseudo-random number generator
	srand(-1);
	
	//Lookup table for .75
	for (x=0; x<65536; x++) {
		lookup[x] = scale_sample(x-32768, 0.75);
	}

	// Fill the array with random data
	for (x = 0; x < SAMPLES; x++) {
		in[x] = (rand()%65536)-32768;
	}

	clock_t tic = clock();	//simple time calc
	// ######################################
	// This is the interesting part!
	// Scale the volume of all of the samples with lookup table
	for (x = 0; x < SAMPLES; x++) {
		out[x] = lookup[in[x]+32768];
	}
	// ######################################
 	clock_t toc =  clock();
	printf("Scaling Time: %f\n", (double)(toc-tic)/CLOCKS_PER_SEC);
	// Sum up the data
	for (x = 0; x < SAMPLES; x++) {
		ttl = (ttl+out[x])%1000;
	}

	// Print the sum
	printf("Result: %d %f\n", ttl, (double)(total)/CLOCKS_PER_SEC);

	return 0;

}

