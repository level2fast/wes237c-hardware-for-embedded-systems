#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H

#define NUM_ITER 11
#define LUT_SIZE 20
#define NUM_OF_QUADRANTS 5
#define NUM_GAIN_VALS 27

typedef int   coef_t;
typedef float data_t;
typedef float acc_t;

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta);

#endif
