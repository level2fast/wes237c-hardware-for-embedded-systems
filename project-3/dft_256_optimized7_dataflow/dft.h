#include "ap_int.h"
typedef float DTYPE;
#define SIZE 256 		/* SIZE OF DFT */
void dft(DTYPE XX_R_in[SIZE], DTYPE XX_I_in[SIZE],DTYPE XX_R_out[SIZE], DTYPE XX_I_out[SIZE]);
void assign_coefficients(ap_uint<8> index, DTYPE c[1], DTYPE s[1]);
void mult_accum(DTYPE real_sample_in,
		        DTYPE imag_sample_in,
				DTYPE temp_c[1],
				DTYPE temp_s[1],
				DTYPE temp_real[SIZE],
				DTYPE temp_imag[SIZE],
				int i);
