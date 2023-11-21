#include<math.h>
#include "dft.h"
#include"coefficients256.h"
#include "ap_int.h"
void dft(data_t real_sample[SIZE], data_t imag_sample[SIZE])
{
	int i, j;
	ap_uint<8> index;
	data_t w;
	data_t c, s;

	// Temporary arrays to hold the intermediate frequency domain results
	data_t temp_real[SIZE];
	data_t temp_imag[SIZE];

	for (i = 0; i < SIZE; i += 1)
	{
#pragma HLS PIPELINE off
		temp_real[i] = 0;
		temp_imag[i] = 0;
		for (j = 0; j < SIZE; j += 1)
		{
#pragma HLS PIPELINE off
			index = i*j;
			//printf("index: %d \n",index);
			c = cos_coefficients_table[index];
			s = sin_coefficients_table[index];
			// Multiply the current phasor with the appropriate input sample and keep
			// running sum
			temp_real[i] += (real_sample[j] * c - imag_sample[j] * s);
			temp_imag[i] += (real_sample[j] * s + imag_sample[j] * c);
		}
	}
	// Perform an in place DFT, i.e., copy result into the input arrays
	for (i = 0; i < SIZE; i += 1)
	{
		real_sample[i] = temp_real[i];
		imag_sample[i] = temp_imag[i];
	}
}
