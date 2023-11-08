#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H

#include <ap_fixed.h>

#define DEBUG 0
#define SYNTHESIS // uncomment me for synthesis; comment me for simulation
typedef ap_fixed<12,3> data_t;     // Data type of a value in the LUT
typedef ap_fixed<12,3> data_in_t;  // Data type of inputs
typedef ap_fixed<12,3> data_out_t; // Data type of outputs

#define W			12  // Total size of fixed-point representation
#define I			2   // Number of integer bits of fixed-point representation
#define FRACTIONAL_BITS	W-I  // Number of fractional bits
#define LUT_SIZE	(1 << (W << 1)) // Size of the LUT = 2^(2*W), set's LUT size to
									// some multiple of total number of fixed point bits

extern data_t my_LUT_r[LUT_SIZE];
extern data_t my_LUT_th[LUT_SIZE];

void cordiccart2pol(data_in_t x, data_in_t y, data_out_t * r,  data_out_t * theta);
void init_cart2pol_LUTs(data_t my_LUT_th[LUT_SIZE], data_t my_LUT_r[LUT_SIZE]);

#endif // CORDICCART2POL_H
