#ifndef BIQUAD_H
#define BIQUAD_H

#include "audio_block.h"

typedef struct biquad_t {
    SAMPLE b0, b1, b2, a1, a2;
    SAMPLE y1, y2, x1, x2;
} biquad_t;

static biquad_t algae__biquad_lowpass(
    FREQUENCY cutoff,
    SAMPLE q,
    FREQUENCY sampleRate
) {
    biquad_t filter;
    q = q<=0?0.01:q;
    const FREQUENCY w0 = cutoff * TWO_PI / sampleRate;
    const FREQUENCY a  = fabs(sin(w0) / (2 * q));
    const FREQUENCY c  = cos(w0);
    const FREQUENCY b0 = (1 - c) / 2, b1 = 1 - c, b2 = (1 - c) / 2;
    const FREQUENCY a0 = 1 + a, a1 = -2 * c, a2 = 1 - a;

    filter.b0 = b0 / a0;
    filter.b1 = b1 / a0;
    filter.b2 = b2 / a0;
    filter.a1 = a1 / a0;
    filter.a2 = a2 / a0;

    return filter;
}

static SAMPLE algae__biquad_process(
    biquad_t* state_out, 
    biquad_t* state_in, 
    SAMPLE input
){
    const SAMPLE b0 = state_in->b0;
    const SAMPLE b1 = state_in->b1;
    const SAMPLE b2 = state_in->b2;
    const SAMPLE a1 = state_in->a1;
    const SAMPLE a2 = state_in->a2;
    const SAMPLE x0 = input;
    const SAMPLE x1 = state_in->x1;
    const SAMPLE x2 = state_in->x2;
    const SAMPLE y1 = state_in->y1;
    const SAMPLE y2 = state_in->y2;
    const SAMPLE y0 = (b0 * x0) + (b1 * x1) + (b2 * x2) - (a1 * y1) - (a2 * y2);
    state_out->y1 = y0;
    state_out->y2 = y1;
    state_out->x1 = x0;
    state_out->x2 = x1;

    return y0;
}


static void algae__biquad__process_block(
    biquad_t* state_out, 
    biquad_t* state_in, 
    audio_block_t* output, 
    audio_block_t* input
){

    for(size_t idx=0; idx<BLOCKSIZE; idx++){
        output->samples[idx] = algae__biquad_process(state_out, state_in, input->samples[idx]);
    }
}

static const struct {
    biquad_t (* const lowpass)(
        FREQUENCY cutoff,
        SAMPLE q,
        FREQUENCY sampleRate
    );
    SAMPLE (* const process)(
        biquad_t* state_out, 
        biquad_t* state_in, 
        SAMPLE input
    );
    void (* const process_block)(
        biquad_t* state_out, 
        biquad_t* state_in, 
        audio_block_t* output, 
        audio_block_t* input
    );
} algae__biquad = {
    algae__biquad_lowpass, algae__biquad_process, algae__biquad__process_block
};


#endif