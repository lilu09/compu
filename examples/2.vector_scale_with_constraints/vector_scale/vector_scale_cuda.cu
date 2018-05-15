// CUDA component
#include <stdio.h>

static __global__ void vector_mult_cuda(float *val, unsigned n, float factor)
{
        unsigned i;
        for(i = 0 ; i < n ; i++)
               val[i] *= factor;
}



void scale_cuda_func(float *arr, int size, float factor)
{
  
    printf("\n************* Hello in vector-scale CUDA call ********************\n\n"); 
    
    vector_mult_cuda<<<1,1>>>(arr, size, factor);

	cudaThreadSynchronize();
}
