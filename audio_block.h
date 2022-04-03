#ifndef AUDIO_BLOCK_H
#define AUDIO_BLOCK_H

#define BLOCKSIZE = 64

typedef struct audio_block_t {
    sample_t[BLOCKSIZE] samples;
};

typedef struct { 
  audio_block_t (* const empty)();
  audio_block_t (* const get)(audio_block_t* block, int index);
//   int (* const empty)(int, char *);
//   void (* const baz)(void);
} audio_block;
// extern audio_block const algaec__audio_block;

audio_block const algaec__audio_block = { empty, get }



#endif