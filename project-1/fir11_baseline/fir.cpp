/*
	Filename: fir.cpp
		FIR lab written for WES/CSE237C class at UCSD.

	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"

/** @brief Performs the convolution of an 11 point input
 *         signal using pre-defined filter coefficients.
 *
 *  This function must be called multiple times to compute
 *  an entire output signal, since each time that we execute
 *  the function we provide one input sample and receive
 *  one output sample.
 *
 *  @param y filter output.
 *  @param x filter input 1 sample
 *
 *  @return Void.
 */
void fir (
  data_t *y,
  data_t x
  )
{
#pragma HLS INTERFACE mode=s_axilite port=y
#pragma HLS INTERFACE mode=s_axilite port=x
	coef_t c[N] = {
	53, 0, -91, 0, 313, 500, 313, 0, -91, 0, 53
	};
#pragma HLS BIND_STORAGE variable=c type=ram_1p
	// declare registers used for holding values
	// that are shifted during the multiply
	// accumulate step. We must keep previous
	// inputs so data is stored across multiple calls
	static data_t shift_reg[N];


	acc_t acc; // accumulator used in for loop
	int i;	   // index used for input to filter
	acc = 0;

	Shift_Accum_Loop: // label multiply accumulator loop
	// start with the last input, loop through all
	// coefficients of the filter
	for (i = N - 1; i >= 0; i--) {
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


