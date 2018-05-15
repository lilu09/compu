// CPU Component
#include <stdio.h>

void scale_cpu_func(float *arr, int size, float factor)
{
	/* scale the vector */
	printf("\n************* Hello in vector-scale CPU call ********************\n\n");
	unsigned i;
	for (i = 0; i < size; i++)
		arr[i] *= factor;
}





