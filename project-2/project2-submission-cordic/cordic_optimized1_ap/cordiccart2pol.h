#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H

#define NUM_ITER 16
#define NUM_OF_QUADRANTS 5
#define NUM_GAIN_VALS 27
#include "ap_fixed.h"

typedef ap_fixed<18,3> coef_t;
typedef ap_fixed<18,3> data_t;
typedef ap_fixed<18,3> acc_t;


void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta);

#endif
