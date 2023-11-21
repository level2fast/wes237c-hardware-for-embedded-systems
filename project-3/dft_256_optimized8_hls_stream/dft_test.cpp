/*
This is DFT computation using matrix vector multiplication form.
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal in time domain.
OUTPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal in frequency domain.

*/

#include<stdio.h>
#include <stdlib.h>
#include<iostream>
#include <math.h>
#include "dft.h"

struct Rmse
{
	int num_sq;
	float sum_sq;
	float error;

	Rmse(){ num_sq = 0; sum_sq = 0; error = 0; }

	float add_value(float d_n)
	{
		num_sq++;
		sum_sq += (d_n*d_n);
		error = sqrtf(sum_sq / num_sq);
		return error;
	}

};


Rmse rmse_R,  rmse_I;

hls::stream<transPkt> In_R, In_I;
hls::stream<transPkt> Out_R, Out_I;

int main()
{
	int index;
	DTYPE gold_R, gold_I;
	fp_int real;	// for int<->float conversion
	fp_int imag;	// for int<->float conversion
	transPkt ipkt_r;
	transPkt ipkt_i;
	transPkt opkt_r;
	transPkt opkt_i;
	FILE * fp = fopen("out.gold.dat","r");
	// generate inputs and reference data
	for (int i = 0; i < SIZE; i++)
	{

		real.fp = i;				// prepare for "conversion"
		ipkt_r.data = real.i;		// pass bit-pattern *as-is*

		imag.fp = 0.0;				// prepare for "conversion"
		ipkt_i.data = imag.i;		// pass bit-pattern *as-is*

		In_R.write(ipkt_r);			// write data to stream
		In_I.write(ipkt_i);			// write data to stream
	}


	// DFT
	dft(In_R, In_I, Out_R, Out_I);

	// comparing with golden output
	for(int i=0; i<SIZE; i++)
	{

		opkt_r = Out_R.read();
		opkt_i = Out_I.read();
		real.i = opkt_r.data;
		imag.i = opkt_i.data;
		//printf("real.fp: %f \n",real.fp);
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R.add_value(real.fp - gold_R);
		rmse_I.add_value(imag.fp - gold_I);

	}
	fclose(fp);


	// printing error results
	printf("----------------------------------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R.error, rmse_I.error);
	printf("----------------------------------------------\n");

	if (rmse_R.error > 0.1 || rmse_I.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
		fprintf(stdout, "*******************************************\n");
	    return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "PASS: The output matches the golden output!\n");
		fprintf(stdout, "*******************************************\n");
	    return 0;
	}

}
