#ifndef NOISE_H
#define NOISE_H

#include <math.h>
#include "audio_block.h"

static sample_t noise(){
    return  2.0 * (( (sample_t) rand() /  (sample_t) (RAND_MAX)) - 0.5);
}

static audio_block_t noise_block(){
    audio_block_t output;
    for(size_t idx=0; idx<BLOCKSIZE; idx++){
        output.samples[idx] = noise();
    }
    return output;
}


#endif