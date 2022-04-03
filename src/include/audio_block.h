#ifndef AUDIO_BLOCK_H
#define AUDIO_BLOCK_H

#include "type_defaults.h"


typedef struct audio_block_t {
    sample_t samples[BLOCKSIZE];
} audio_block_t;

static audio_block_t algae__audio_block__empty() {
    audio_block_t out;
    for(size_t samp_idx=0;samp_idx<BLOCKSIZE;samp_idx++){
        out.samples[samp_idx]=0;
    }
    return out;
}

static sample_t algae__audio_block__get(audio_block_t* block, size_t index){
    return block->samples[index];
}

static audio_block_t algae__audio_block__mult(audio_block_t* lhs, audio_block_t* rhs) {
    audio_block_t output;
    for(size_t idx=0; idx<BLOCKSIZE; idx++){
        output.samples[idx] = lhs->samples[idx] * rhs->samples[idx];
    }
    return output;
}

static audio_block_t algae__audio_block__div(audio_block_t* lhs, audio_block_t* rhs) {
    audio_block_t output;
    for(size_t idx=0; idx<BLOCKSIZE; idx++){
        output.samples[idx] = lhs->samples[idx] / rhs->samples[idx];
    }
    return output;
}
            
static audio_block_t algae__audio_block__add(audio_block_t* lhs, audio_block_t* rhs) {
    audio_block_t output;
    for(size_t idx=0; idx<BLOCKSIZE; idx++){
        output.samples[idx] = lhs->samples[idx] + rhs->samples[idx];
    }
    return output;
}
           
static audio_block_t algae__audio_block__sub(audio_block_t* lhs, audio_block_t* rhs) {
    audio_block_t output;
    for(size_t idx=0; idx<BLOCKSIZE; idx++){
        output.samples[idx] = lhs->samples[idx] - rhs->samples[idx];
    }
    return output;
}

static const struct { 
  audio_block_t (* const empty)();
  sample_t (* const get)(audio_block_t* block, size_t index);
  audio_block_t (* const mult)(audio_block_t* lhs, audio_block_t* rhs);
  audio_block_t (* const div)(audio_block_t* lhs, audio_block_t* rhs);
  audio_block_t (* const add)(audio_block_t* lhs, audio_block_t* rhs);
  audio_block_t (* const sub)(audio_block_t* lhs, audio_block_t* rhs);

} algae__audio_block = {
  algae__audio_block__empty,
  algae__audio_block__get,
  algae__audio_block__mult,
  algae__audio_block__div,
  algae__audio_block__add,
  algae__audio_block__sub
};



#endif