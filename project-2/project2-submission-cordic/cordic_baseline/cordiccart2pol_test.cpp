#include "cordiccart2pol.h"
#include <math.h>
#include <stdio.h>


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


Rmse rmse_theta;
Rmse rmse_r;


void run_test(data_t x, data_t y, double golden_r, double golden_theta)
{
	data_t r;
	data_t theta;

	cordiccart2pol(x, y, &r,  &theta);

	printf("Test: x=%.4f, y=%.4f, golden theta=%.4f, golden r=%.4f, your theta=%.4f, your r=%.4f\n\n",
			(double)x, (double)y, golden_theta, golden_r, (double)theta, (double)r);

	rmse_theta.add_value((float)theta - golden_theta);
	rmse_r.add_value((float)r - golden_r);
}


int main()
{
	data_t x;
	data_t y;
	data_t r;
	data_t theta;


	printf("---Testing results----------------------------------\n");
	//      ( x       y               r               theta      )
	// 270
	run_test(0.0,    -1.0,           1.0,           -1.570796326794897);
	// 315
	run_test(1.0,    -1.0,           1.4142,        -0.785398163397449);
	// 225
	run_test(-1.0,   -1.0,           1.4142,        -2.356194490192345);

	// deg: 90
	run_test(0.0,     1.0,              1.0,         1.570796326794897);

	// deg: 180
	run_test(-1.0,    0.0,              1.0,         3.141592653589793);

	//      ( x       y               r               theta      )
	// deg: 30
	run_test(0.8660,  0.5,              1.0,         0.523598775598299);

	// deg: 45
	run_test(0.7071,  0.7071,           1.0,         0.785398163397448);

	// deg: 60
	run_test(0.5,     0.8660,           1.0,         1.047197551196598);

	//      ( x       y               r               theta      )
	// deg: 120
	run_test(-0.5,    0.8660,        1.0,            2.094395102393196);

	// deg: 135
	run_test(-0.7071, 0.7071,        1.0,            2.356194490192345);

	// deg: 150
	run_test(-0.8660, 0.4999,        1.0,            2.617993877991494);

	//      ( x       y               r               theta      )
	// deg: 210
	run_test(-0.8660, -0.5000,        1.0,          -2.617993877991494);

	// deg: 225
	run_test(-0.7071, -0.7071,        1.0,          -2.356194490192345);

	// deg: 240
	run_test(-0.5000, -0.8660,        1.0,          -2.094395102393196);



	// Test1
	run_test(0.8147, 0.1269, 0.824523923242982, 0.154521173805634);

	// Test 2
	run_test(0.6323, -0.2785, 0.690916449362729, -0.414888412375609);

	// Test 3
	run_test(-0.5469, -0.9575,1.102681214132172, -2.089751217098013);

	// Test 4
	run_test(-0.4854, 0.7003,0.852075847562880, 2.176897679895152);


	printf("---RMS error----------------------------------\n");
	printf("----------------------------------------------\n");
	printf("   RMSE(R)           RMSE(Theta)\n");
	printf("%0.15f %0.15f\n", rmse_r.error, rmse_theta.error);
	printf("----------------------------------------------\n");


	float error_threshold = 0.001;

    int success = (rmse_r.error < error_threshold) && (rmse_theta.error < error_threshold);

    if (success) return 0;
    else return 1;

}
