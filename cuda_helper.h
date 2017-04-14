#ifndef CUDA_HELPER_H
#define CUDA_HELPER_H

#include <cuda_runtime.h>

void checkCudaErrors( cudaError_t code, int line, bool abort );

#endif // CUDA_HELPER_H
