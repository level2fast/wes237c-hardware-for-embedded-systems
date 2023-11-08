/*
	Filename: fir.cpp
		Complex FIR or Match filter
		firI1 and firI2 share coef_t c[N]
		firQ1 and firQ2 share coef_t c[N]
		
	INPUT:
		I: signal for I sample
		I: signal for Q sample

	OUTPUT:
		X: filtered output
		Y: filtered output

*/

#include "fir.h"

void firI1 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {1,    -1,    1,    -1,    -1,    -1,    1,    1,    -1,    -1,    -1,    1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    1,    1,    1,    1,    -1,    -1,    1,    1,    1,    -1,    -1,    -1};
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


void firI2 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {1,    -1,    1,    -1,    -1,    -1,    1,    1,    -1,    -1,    -1,    1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    1,    1,    1,    1,    -1,    -1,    1,    1,    1,    -1,    -1,    -1};
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




void firQ1 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {-1,    -1,    1,    -1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    -1,    1,    -1,    1,    1,    -1,    1,    -1,    -1,    1,    -1,    1,    1,    1,    1,    -1,    1,    -1,    1,    1};

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

void firQ2 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {-1,    -1,    1,    -1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    -1,    1,    -1,    1,    1,    -1,    1,    -1,    -1,    1,    -1,    1,    1,    1,    1,    -1,    1,    -1,    1,    1};
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


void fir (
  data_t I,
  data_t Q,

  data_t *X,
  data_t *Y
  ) {

	data_t iValues[2];
	data_t qValues[2];

	firI1(&iValues[0],I); // i1in
	firQ1(&qValues[0],Q); // q1in

	firI2(&qValues[1],Q); // q2in
	firQ2(&iValues[1],I); // i1in

	*X = iValues[0] + qValues[0];
	*Y = qValues[1] - iValues[1];

}


