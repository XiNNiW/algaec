#ifndef BIQUAD_H
#define BIQUAD_H


#define TWO_PI 6.28318530718

typedef float sample_t;
typedef float frequency_t;

typedef struct biquad_t {
    sample_t b0, b1, b2, a1, a2;
    sample_t y1, y2, x1, x2;
} biquad_t;

static biquad_t algae__biquad_lowpass(
    frequency_t cutoff,
    sample_t q,
    frequency_t sampleRate
) {
    biquad_t filter;
    q = q<=0?0.01:q;
    const frequency_t w0 = cutoff * TWO_PI / sampleRate;
    const frequency_t a  = fabs(sin(w0) / (2 * q));
    const frequency_t c  = cos(w0);
    const frequency_t b0 = (1 - c) / 2, b1 = 1 - c, b2 = (1 - c) / 2;
    const frequency_t a0 = 1 + a, a1 = -2 * c, a2 = 1 - a;

    filter.b0 = b0 / a0;
    filter.b1 = b1 / a0;
    filter.b2 = b2 / a0;
    filter.a1 = a1 / a0;
    filter.a2 = a2 / a0;

    return filter;
}

static void algae__biquad_process(
    biquad_t* state_out, 
    biquad_t* state_in, 
    sample_t input
){
    const sample_t b0 = state_in->b0;
    const sample_t b1 = state_in->b1;
    const sample_t b2 = state_in->b2;
    const sample_t a1 = state_in->a1;
    const sample_t a2 = state_in->a2;
    const sample_t x0 = input;
    const sample_t x1 = state_in->x1;
    const sample_t x2 = state_in->x2;
    const sample_t y1 = state_in->y1;
    const sample_t y2 = state_in->y2;
    const sample_t y0 = b0 * x0 + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
    state_out->y1 = y0;
    state_out->y2 = y1;
    state_out->x1 = x0;
    state_out->x2 = x1;
}

static const struct {
    biquad_t (* const lowpass)(
        frequency_t cutoff,
        sample_t q,
        frequency_t sampleRate
    );
    void (* const process)(
        biquad_t* state_out, 
        biquad_t* state_in, 
        sample_t input
    );
} algae__biquad = {
    algae__biquad_lowpass, algae__biquad_process
};


#endif