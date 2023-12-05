/*
 This is traditional 2-radix DIT FFT algorithm implementation.
 INPUT:
 In_R, In_I[]: Real and Imag parts of Complex signal

 OUTPUT:
 Out_R, Out_I[]: Real and Imag parts of Complex signal
 */

#include "fft.h"
#include "fft.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void bit_reverse(DTYPE X_R[SIZE],
				 DTYPE X_I[SIZE]);

void fft_stages(DTYPE X_R[SIZE],
				DTYPE X_I[SIZE],
				int STAGES,
				DTYPE OUT_R[SIZE],
				DTYPE OUT_I[SIZE]);

void qpsk_decode(DTYPE R[SIZE],
				 DTYPE I[SIZE],
				 int D[SIZE]);

void demod(DTYPE X_R[SIZE], DTYPE X_I[SIZE], int D[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE])
{

	fft(X_R, X_I, OUT_R, OUT_I);
	qpsk_decode(OUT_R, OUT_I, D);

}

void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE],DTYPE OUT_I[SIZE])
{
#pragma HLS dataflow
	DTYPE IN_R_TEMP[SIZE], IN_I_TEMP[SIZE];
	DTYPE OUT_R_TEMP[SIZE], OUT_I_TEMP[SIZE];
	DTYPE Stage1_R[SIZE], Stage1_I[SIZE];
	DTYPE Stage2_R[SIZE], Stage2_I[SIZE];
	DTYPE Stage3_R[SIZE], Stage3_I[SIZE];
	DTYPE Stage4_R[SIZE], Stage4_I[SIZE];
	DTYPE Stage5_R[SIZE], Stage5_I[SIZE];
	DTYPE Stage6_R[SIZE], Stage6_I[SIZE];
	DTYPE Stage7_R[SIZE], Stage7_I[SIZE];
	DTYPE Stage8_R[SIZE], Stage8_I[SIZE];
	DTYPE Stage9_R[SIZE], Stage9_I[SIZE];
	bit_reverse(X_R, X_I,IN_R_TEMP,IN_I_TEMP);

	//Call fft


	fft_stages(IN_R_TEMP, IN_I_TEMP,1, Stage1_R, Stage1_I);
	fft_stages(Stage1_R, Stage1_I, 2, Stage2_R, Stage2_I);
	fft_stages(Stage2_R, Stage2_I, 3, Stage3_R, Stage3_I);
	fft_stages(Stage3_R, Stage3_I, 4, Stage4_R, Stage4_I);
	fft_stages(Stage4_R, Stage4_I, 5, Stage5_R, Stage5_I);
	fft_stages(Stage5_R, Stage5_I, 6, Stage6_R, Stage6_I);
	fft_stages(Stage6_R, Stage6_I, 7, Stage7_R, Stage7_I);
	fft_stages(Stage7_R, Stage7_I, 8, Stage8_R, Stage8_I);
	fft_stages(Stage8_R, Stage8_I, 9, Stage9_R, Stage9_I);
	fft_stages(Stage9_R, Stage9_I, 10, OUT_R_TEMP, OUT_I_TEMP);

	bit_reverse(OUT_R_TEMP, OUT_I_TEMP,OUT_R, OUT_I);

}


unsigned int reverse_bits(unsigned int input)
{
	int i, rev = 0;
	reverse_bits_loop:
	for (i = 0; i < M; i++)
	{
#pragma HLS UNROLL
		rev = (rev << 1) | (input & 1);
		input = input >> 1;
	}
	return rev;
}


void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE],DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE])
{
	unsigned int i;
	DTYPE temp;
	DTYPE temp_rev_R[SIZE];
	DTYPE temp_rev_I[SIZE];
	int temp_rev_idx;

	for (i = 0; i < SIZE; i++)
	{
#pragma HLS UNROLL
		temp_rev_idx = reverse_bits(i); // Find the bit reversed index

		// Swap the real values
		OUT_R[temp_rev_idx] = X_R[i];

		// Swap the imaginary values
		OUT_I[temp_rev_idx] = X_I[i];
	}
}
/*=======================BEGIN: FFT=========================*/

//stages
void fft_stages(DTYPE X_R[SIZE], DTYPE X_I[SIZE], int stage, DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
#pragma HLS array_partition variable=W_real type=complete
#pragma HLS array_partition variable=W_imag type=complete
	int DFTpts = 1 << stage; // DFT = 2^stage = points in sub DFT
	int numBF = DFTpts / 2; // Butterfly WIDTHS in sub-DFT
	int step = SIZE >> stage;
	int k = 0;
	DTYPE c = 0;
	DTYPE s = 0;
	int twiddle_index = 0;

	// Perform butterflies for j-th stage
	butterfly_loop_stages:for (int j = 0; j < numBF; j++)
	{
		// Compute butterflies that use same W**k
		dft_loop_stages:for (int i = j; i < SIZE; i += DFTpts) {
#pragma HLS pipeline
				const int e = 1024/DFTpts;
				twiddle_index = e * j;
				c = W_real[twiddle_index]; // twiddle factor
				s = W_imag[twiddle_index]; // twiddle factor

				int ilower = i + numBF; // index of lower point in butterfly

				DTYPE temp_R = X_R[ilower] * c - X_I[ilower] * s;
				DTYPE temp_I = X_I[ilower] * c + X_R[ilower] * s;

				OUT_R[ilower] = X_R[i] - temp_R;
				OUT_I[ilower] = X_I[i] - temp_I;

				OUT_R[i] = X_R[i] + temp_R;
				OUT_I[i] = X_I[i] + temp_I;
			}
		k += step;
	}
}

/*=======================END: FFT=========================*/
