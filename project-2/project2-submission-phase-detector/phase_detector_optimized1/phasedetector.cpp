/*
	Filename: phasedetector.cpp
		Phase detector

	INPUT:
		I: signal for I sample
		Q: signal for Q sample
		length: array size

	OUTPUT:
		R: Radius
		Theta: Angle

*/

#include "phasedetector.h"

void phasedetector (
  data_t *I,
  data_t *Q,

  data_t *R,
  data_t *Theta,

  int length
  ){
  int i;
  const int SAMPLES = 1024;
  data_t coor_X[SAMPLES];
  data_t coor_Y[SAMPLES];

	for (i = 0; i < length ;i++)
	{

		fir(I[i],Q[i],&coor_X[i],&coor_Y[i]);
		cordiccart2pol(coor_X[i],coor_Y[i],&R[i],&Theta[i]);
	}

}




