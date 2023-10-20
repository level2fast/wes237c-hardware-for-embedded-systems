/*
	Filename: fir.cpp
		FIR lab written for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"

void fir (
  data_t *y,
  data_t x
  )
{

	coef_t c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
#pragma HLS bind_storage variable=c type=RAM_2P
#pragma HLS ARRAY_PARTITION variable=c type=complete
	
	// Write your code here
	static data_t shift_reg[N];
#pragma HLS bind_storage variable=shift_reg type=RAM_2P
#pragma HLS ARRAY_PARTITION variable=shift_reg type=cyclic factor=16

	acc_t acc;
	int i;
	acc = 0;

	TDL:
	for (i = N - 1; i > 0; i--) {
#pragma HLS PIPELINE on
#pragma HLS unroll factor=16
	shift_reg[i] = shift_reg[i - 1];
	}
	shift_reg[0] = x;
	acc = 0;

	MAC:
	for (i = N - 1; i >= 0; i--) {
#pragma HLS unroll factor=32
	acc += shift_reg[i] * c[i];
	}

	*y = acc;
}



