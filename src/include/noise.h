#ifndef NOISE_H
#define NOISE_H

#include <math.h>
#include "audio_block.h"

static sample_t algae__rand(){
    return  2.0 * (( (sample_t) rand() /  (sample_t) (RAND_MAX)) - 0.5);
}

static audio_block_t algae__rand_block(){
    audio_block_t output;
    for(size_t idx=0; idx<BLOCKSIZE; idx++){
        output.samples[idx] = algae__rand();
    }
    return output;
}

static const struct {
    sample_t (* const noise)();
    audio_block_t (* const noise_block)();
} algae__noise = {algae__rand,algae__rand_block};


#endif