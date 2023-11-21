#include<math.h>
#include "dft.h"
#include"coefficients256.h"

void dft(data_t real_sample[SIZE], data_t imag_sample[SIZE])
{
	int i, j;
	data_t w;
	data_t c, s;

	data_t temp_real[SIZE];
	data_t temp_imag[SIZE];

	for (i = 0; i < SIZE; i += 1) {
#pragma HLS PIPELINE off
	temp_real[i] = 0;
	temp_imag[i] = 0;

	w = (2.0 * 3.141592653589 / SIZE) * (data_t)i;

	for (j = 0; j < SIZE; j += 1) {
#pragma HLS PIPELINE off
		c = cos(j * w);
		s = -sin(j * w);

		temp_real[i] += (real_sample[j] * c - imag_sample[j] * s);
		temp_imag[i] += (real_sample[j] * s + imag_sample[j] * c);
	}
	}

	for (i = 0; i < SIZE; i += 1)
	{
		real_sample[i] = temp_real[i];
		imag_sample[i] = temp_imag[i];
	}
}
