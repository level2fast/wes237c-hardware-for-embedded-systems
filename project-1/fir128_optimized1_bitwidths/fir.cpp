/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
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
	
	// declare registers used for holding values
	// that are shifted during the multiply
	// accumulate step. We must keep previous
	// inputs so data is stored across multiple calls
	static data_t shift_reg[N];


	acc_t acc; // accumulator used in for loop
	int i;	   // index used for input to filter
	acc = 0;
	// start with the last input, loop through all
	// coefficients of the filter
	Shift_Accum_Loop: // label multiply accumulator loop
	for (i = N - 1; i >= 0; i--) {
#pragma HLS PIPELINE off
		// check for last input to ensure
		// that filter output does not exceed
		// array bounds
		if (i == 0) {
			// last input is reached
			// so perform multiply accumulate
			// only the last input and the last
			// filter coefficient
			acc += x * c[0];

			// update shift register
			shift_reg[0] = x;
		} else {
			// perform multiply accumulate using
			// previous index
			shift_reg[i] = shift_reg[i - 1];
			acc += shift_reg[i] * c[i];
		}
	}
	*y = acc;
}


