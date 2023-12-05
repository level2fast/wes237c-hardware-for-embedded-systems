#include "fft.h"
#include <stdio.h>

void qpsk_decode(DTYPE R[SIZE], DTYPE I[SIZE], int D[SIZE]) {

	int quadrature;
	int in_phase;
	unsigned int i;
	qpsk_loop:
	for (i = 0; i < SIZE; i++)
	{
		in_phase   = R[i] < 0;
		quadrature = I[i] < 0;

		//takes a complex number and translates it into an integer
		D[i] = (quadrature << 1) | in_phase;
	}
}

