/**
 * @file bnn.h
 * @author Steven Daniels
 * @brief This file defines methods used to implement a binary neural network
 *        using bitwise operations.
 *
 * 	This implementation of a BNN is optimized to perform classification of
 * 	of the MNIST data set of handwritten digits.
 *
 * 	@NOTE MNIST: https://ieeexplore.ieee.org/document/726791
 *
 */
#ifndef __BNN_HEADER_
#define __BNN_HEADER_

#include <iostream>

using namespace std;

#include "ap_int.h"
#define DEBUG 1 
#define DATA_BIT_SIZE 32
//You can change SIZE and function prototype if needed.
typedef  const unsigned int DTYPE; // used as an input type
typedef  int ITYPE;                // used as an output type


const unsigned int SIZE = 25;
const unsigned int OUT_SIZE = 10;

// size of weights
const unsigned int W1_SIZE = 3200;
const unsigned int W2_SIZE = 256;
const unsigned int W3_SIZE = 20;

// input sizes for each layer
const unsigned int INPUT_SIZE  = 800;
const unsigned int INPUT_SIZE_NO_PAD = 784;
const unsigned int LAYER1_SIZE = 128;
const unsigned int LAYER2_SIZE = 64;
const unsigned int LAYER3_SIZE = 10;

// output size of each layer
const unsigned int LAYER1_OUT_SIZE = 4;
const unsigned int LAYER2_OUT_SIZE = 2;





void bnn(DTYPE IN[SIZE], ITYPE OUT[OUT_SIZE]);
int  matrix_multiplier(DTYPE vec1, DTYPE vec2, ITYPE N);
void matrix_mult(DTYPE* LAYER_IN,
					  const unsigned* WEIGHT_IN,
					  ITYPE* LAYER_OUT,
					  const unsigned inner_dim,
				      const unsigned output_dim);
//void layer_preprocessing(ITYPE* IN, unsigned int* LAYER_OUT, DTYPE LAYER_IN_SIZE, DTYPE LAYER_OUT_SIZE,DTYPE DATA_SIZE, DTYPE ZERO_PAD);
void layer1_preprocessing(ITYPE* IN, unsigned int* LAYER_OUT, DTYPE DATA_SIZE, DTYPE ZERO_PAD);
void layer2_preprocessing(ITYPE* IN, unsigned int* LAYER_OUT, DTYPE DATA_SIZE, DTYPE ZERO_PAD);
void sign(ITYPE* IN, ITYPE* SIGN_OUT, DTYPE LEN);
void quantize(ITYPE* IN, ITYPE* QUANTIZE_OUT, DTYPE LEN);
void pack(ITYPE* LAYER_IN, unsigned int* LAYER_OUT, DTYPE LAYER_SIZE_OUT);
int pop_cnt(unsigned x);
static inline unsigned int xnor(DTYPE a, DTYPE b)
{
	return ~(a^b);
}

#endif
