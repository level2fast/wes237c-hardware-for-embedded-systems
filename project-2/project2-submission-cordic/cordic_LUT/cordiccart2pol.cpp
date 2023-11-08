#include "cordiccart2pol.h"
#include <math.h>

void init_cart2pol_LUTs(data_t my_LUT_th[LUT_SIZE], data_t my_LUT_r[LUT_SIZE])
{
	// Fill the LUT values with their appropriate R and theta values
	for(int i=0; i<LUT_SIZE; i++){ // loop from 0- 65,536 when W = 8, and I = 2
		ap_uint<2*W> index = i;  // init 32 bit unsigned int
		ap_fixed<W, I, AP_RND, AP_WRAP, 1> fixed_x; // create fixed point x and y with 8 bits for total variable
		ap_fixed<W, I, AP_RND, AP_WRAP, 1> fixed_y; // and 2 bits for int part, so 6 fractional bits. Set
													// to round to plus infinity with default wrap around mode
		// loop through fixed point x and y
		// index into x and y by the word length - 1 - the loop incrementer: 1st iteration [8-1-0=7]
		// index into "index" array for x by (2*word length - 1 - loop incrementor): 1st iteration
		// [2*8-1-0=15]
		// index into "index" array for y by (word length - 1 - loop incrementor): 1st iteration
		// [8-1-0=7]
		for(int j = 0; j < W; j++)
			{
				// loop through each bit of x, and y
				// starting with the MSB setting all
				// 8 bits to some offset of the index
				// variable


				// set x bits starting from the
				// 15th bit of index down to 7th bit
				fixed_x[W-1-j] = index[2*W-1-j];

				// set x bits starting from the
				// 7th bit of index down to the 0th bit
				fixed_y[W-1-j] = index[W-1-j];

			}

		float _x = fixed_x;
		float _y = fixed_y;

		if((_x == 0) & (_y == 0)){
			my_LUT_th[index] = 0;
			my_LUT_r[index]  = 0;
		}
		else{
			// calculate angle and magnitude of each vector
			my_LUT_th[index] = atan2f(_y, _x);
			my_LUT_r[index]  = sqrtf((_y*_y)+(_x*_x));
		}
	}
}

void cordiccart2pol(data_in_t x, data_in_t y, data_out_t * r,  data_out_t * theta)
{
#ifdef SYNTHESIS
	data_t my_LUT_th[LUT_SIZE] = {0}; //  use dummy values to get synthesis results (major hack). Would need to explicitly set these to pass co-sim
	data_t my_LUT_r[LUT_SIZE] = {0};  // I'm sure there is a better way to do this. 
#endif

	// Convert the inputs to internal fixed point representation
	ap_fixed<W, I, AP_RND, AP_WRAP, 1> fixed_x = x;
	ap_fixed<W, I, AP_RND, AP_WRAP, 1> fixed_y = y;

	// Build the index to find the entries in the LUT.
	ap_uint<2*W> index;

	// Concatenate x and y to create the index into the LUTs. x is upper half; y is lower half.
	for(int i = 0; i < W; i++)
	{
#pragma HLS UNROLL
		index[2*W-1-i] = fixed_x[W-1-i];
		index[W-1-i]   = fixed_y[W-1-i];
	}

	// Get the result from the LUTs and write it back to the outputs
	*r     = my_LUT_r[index];
	*theta = my_LUT_th[index];
}
