#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(DTYPE real_sample_in[SIZE], DTYPE imag_sample_in[SIZE],DTYPE real_sample_out[SIZE], DTYPE imag_sample_out[SIZE])
{
#pragma HLS dataflow

	int i, j;
	ap_uint<8> index;
	DTYPE w;
	DTYPE c, s;

	DTYPE temp_real[SIZE];
	DTYPE temp_imag[SIZE];

	DTYPE temp_c[1];
	DTYPE temp_s[1];


	for (i = 0; i < SIZE; i += 1)
	{
#pragma HLS PIPELINE on
		temp_real[i] = 0;
		temp_imag[i] = 0;
		for (j = 0; j < SIZE; j += 1)
		{
#pragma HLS PIPELINE off

			index = i*j;
			assign_coefficients(index,temp_c,temp_s);
			mult_accum(real_sample_in[j],
			           imag_sample_in[j],
					   temp_c,
					   temp_s,
					   temp_real,
					   temp_imag,
					   i);
		}
	}

	for (i = 0; i < SIZE; i += 1)
	{
		real_sample_out[i] = temp_real[i];
		imag_sample_out[i] = temp_imag[i];
	}
}

void assign_coefficients(ap_uint<8> index, DTYPE c[1], DTYPE s[1])
{
	c[0] = cos_coefficients_table[index];
	s[0] = sin_coefficients_table[index];
}
void mult_accum(DTYPE real_sample_in,
		        DTYPE imag_sample_in,
				DTYPE temp_c[1],
				DTYPE temp_s[1],
				DTYPE temp_real[SIZE],
				DTYPE temp_imag[SIZE],
				int i)
{
	temp_real[i] += (real_sample_in * temp_c[0] - imag_sample_in * temp_s[0]);
	temp_imag[i] += (real_sample_in * temp_s[0] + imag_sample_in * temp_c[0]);
}
