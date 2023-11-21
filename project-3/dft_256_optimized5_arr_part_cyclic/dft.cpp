#include<math.h>
#include "dft.h"
#include"coefficients256.h"
#include "ap_int.h"
void dft(DTYPE real_sample_in[SIZE], DTYPE imag_sample_in[SIZE],DTYPE real_sample_out[SIZE], DTYPE imag_sample_out[SIZE])
{
#pragma HLS array_partition variable=real_sample_in type=cyclic factor=16
#pragma HLS array_partition variable=imag_sample_in type=cyclic factor=16

#pragma HLS array_partition variable=real_sample_out type=complete
#pragma HLS array_partition variable=imag_sample_out type=complete

#pragma HLS array_partition variable=cos_coefficients_table type=complete
#pragma HLS array_partition variable=sin_coefficients_table type=complete

	int i, j;
	ap_uint<8> index;
	DTYPE w;
	DTYPE c, s;
	DTYPE temp_real[SIZE];
	DTYPE temp_imag[SIZE];
#pragma HLS array_partition variable=temp_real type=cyclic factor=16
#pragma HLS array_partition variable=temp_imag type=cyclic factor=16
	for (i = 0; i < SIZE; i += 1)
	{
#pragma HLS PIPELINE off
		temp_real[i] = 0;
		temp_imag[i] = 0;
		for (j = 0; j < SIZE; j += 1)
		{
#pragma HLS PIPELINE off
			index = i*j;

			c = cos_coefficients_table[index];
			s = sin_coefficients_table[index];

			temp_real[i] += (real_sample_in[j] * c - imag_sample_in[j] * s);
			temp_imag[i] += (real_sample_in[j] * s + imag_sample_in[j] * c);
		}
	}

	for (i = 0; i < SIZE; i += 1)
	{
		real_sample_out[i] = temp_real[i];
		imag_sample_out[i] = temp_imag[i];
	}
}
