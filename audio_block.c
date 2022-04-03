#include "audio_block.h"



static audio_block_t empty() {
    audio_block_t out;
    for(size_t samp_idx=0;samp_idx<BLOCKSIZE;samp_idx++){
        out[samp_idx]=0;
    }
    return out;
}

static sample_t get(audio_block_t* block, int index){
    return block->samples[index];
}

// audio_block_t mult(audio_block_t* lhs, audio_block_t* rhs) const {
//     AudioBlock output;
//     for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//         output[idx] = samples[idx] * rhs[idx];
//     }
//     return output;
// }
//             inline const AudioBlock& operator*=(const AudioBlock& rhs){
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] * rhs[idx];
//                 }
//                 this->samples = output.samples;
//                 return *(this);
//             }
//             inline const AudioBlock operator*(const sample_t& rhs) const {
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] * rhs;
//                 }
//                 return output;
//             }
//             inline const AudioBlock& operator*=(const sample_t& rhs){
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] * rhs;
//                 }
//                 this->samples = output.samples;
//                 return *(this);
//             }
//             inline const AudioBlock operator/(const AudioBlock& rhs) const {
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] / rhs[idx];
//                 }
//                 return output;
//             }
//             inline const AudioBlock& operator/=(const AudioBlock& rhs){
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] / rhs[idx];
//                 }
//                 this->samples = output.samples;
//                 return *(this);
//             }
//             inline const AudioBlock operator/(const sample_t& rhs) const {
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] / rhs;
//                 }
//                 return output;
//             }
//             inline const AudioBlock& operator/=(const sample_t& rhs){
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] / rhs;
//                 }
//                 this->samples = output.samples;
//                 return *(this);
//             }
//             inline const AudioBlock operator+(const AudioBlock& rhs) const {
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] + rhs[idx];
//                 }
//                 return output;
//             }
//             inline const AudioBlock& operator+=(const AudioBlock& rhs){
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] + rhs[idx];
//                 }
//                 this->samples = output.samples;
//                 return *(this);
//             }
//             inline const AudioBlock operator+(const sample_t& rhs) const {
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] + rhs;
//                 }
//                 return output;
//             }
//             inline const AudioBlock& operator+=(const sample_t& rhs){
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] + rhs;
//                 }
//                 this->samples = output.samples;
//                 return *(this);
//             }
//             inline const AudioBlock operator-(const AudioBlock& rhs) const {
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] - rhs[idx];
//                 }
//                 return output;
//             }
//             inline const AudioBlock& operator-=(const AudioBlock& rhs){
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] - rhs[idx];
//                 }
//                 this->samples = output.samples;
//                 return *(this);
//             }
//             inline const AudioBlock operator-(const sample_t& rhs) const {
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] - rhs;
//                 }
//                 return output;
//             }
//             inline const AudioBlock& operator-=(const sample_t& rhs){
//                 AudioBlock output;
//                 for(size_t idx=0; idx<BLOCK_SIZE; idx++){
//                     output[idx] = samples[idx] - rhs;
//                 }
//                 this->samples = output.samples;
//                 return *(this);
//             }