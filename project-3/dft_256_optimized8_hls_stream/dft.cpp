#include<math.h>
#include "dft.h"
#include"coefficients256.h"
#include "ap_int.h"

void dft(hls::stream<transPkt> &real_sample_in, hls::stream<transPkt> &imag_sample_in,
		 hls::stream<transPkt> &real_sample_out, hls::stream<transPkt> &imag_sample_out)
{
#pragma HLS INTERFACE mode=axis port=real_sample_in,imag_sample_in,real_sample_out,imag_sample_out
#pragma HLS INTERFACE mode=s_axilite port=return
	int i, j;
	ap_uint<8> index;
	DTYPE w;
	DTYPE c, s;

	DTYPE temp_real[SIZE];
	DTYPE temp_imag[SIZE];
	DTYPE In_R[SIZE], In_I[SIZE];
	fp_int real;	// for int<->float conversion
	fp_int imag;	// for int<->float conversion
	transPkt ipkt_r;
	transPkt ipkt_i;
	transPkt opkt_r;
	transPkt opkt_i;

	for(int i=0; i<SIZE; i++)
	{
		ipkt_r = real_sample_in.read();
		ipkt_i = imag_sample_in.read();
		real.i = ipkt_r.data;
		imag.i = ipkt_i.data;
		In_R[i] = real.fp;
		In_I[i] = imag.fp;
	}


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
			// Multiply the current phasor with the appropriate input sample and keep
			// running sum
			temp_real[i] += (In_R[j] * c - In_I[j] * s);
			temp_imag[i] += (In_R[j] * s + In_I[j] * c);

		}
	}

	for (i = 0; i < SIZE; i += 1)
	{
		real.i = temp_real[i];
		imag.i = temp_imag[i];
		opkt_r.data = real.i;
		opkt_i.data = imag.i;
		real_sample_out.write(opkt_r);
		imag_sample_out.write(opkt_i);
	}
}
