#include "cordiccart2pol.h"
#include <math.h>
#include "hls_print.h"
#include <stdio.h>

data_t Kvalues[NUM_ITER] =
{
		1,
		0.500000000000000,
		0.250000000000000,
		0.125000000000000,
		0.0625000000000000,
		0.0312500000000000,
		0.0156250000000000,
		0.00781250000000000,
		0.00390625000000000,
		0.00195312500000000,
		0.000976562500000000,
		0.000488281250000000,
		0.000244140625000000,
		0.000122070312500000,
		6.10351562500000e-05,
		3.05175781250000e-05
};

data_t angles[NUM_ITER] =
{
		0.785398163397448,
		0.463647609000806,
		0.244978663126864,
		0.124354994546761,
		0.0624188099959574,
		0.0312398334302683,
		0.0156237286204768,
		0.00781234106010111,
		0.00390623013196697,
		0.00195312251647882,
		0.000976562189559320,
		0.000488281211194898,
		0.000244140620149362,
		0.000122070311893670,
		6.10351561742088e-05,
		3.05175781155261e-05
};
data_t cordic_gain[NUM_GAIN_VALS]=
{
		0.7071067811865476,
		0.6324555320336759,
		0.6135719910778964,
		0.6088339125177524,
		0.6076482562561683,
		0.607351770141296,
		0.6072776440935261,
		0.6072591122988928,
		0.6072544793325625,
		0.6072533210898753,
		0.6072530315291345,
		0.607252959138945,
		0.6072529410413973,
		0.6072529365170104,
		0.6072529353859136,
		0.6072529351031395,
		0.6072529350324459,
		0.6072529350147725,
		0.6072529350103542,
		0.6072529350092496,
		0.6072529350089735,
		0.6072529350089044,
		0.6072529350088872,
		0.6072529350088829,
		0.6072529350088818,
		0.6072529350088816,
		0.6072529350088814
};

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
#pragma HLS INTERFACE mode=s_axilite port=return

	data_t two_multiplier  = 2;

	if (x == 1 && y == 0)
	{
		*r=1;
		*theta=0;
		return;
	}
	data_t cur_x = 0;
	data_t cur_y = 0;
	// Use the sign bit of x and y to determine which quadrant the vector is in

	if(x < 0 && y >= 0.0)
	{
    	cur_x =  y;
    	cur_y = -x;
    	*theta = -(angles[0] + angles[0]);
	}
	else if(x < 0 && y < 0)
	{
    	cur_x = -y;
    	cur_y = x;
    	*theta = angles[0] + angles[0];
	}
	else if(x >= 0 && y < 0)
	{
		cur_x = -y;
    	cur_y = x;
    	*theta = angles[0] + angles[0];
	}
	else
	{
    	cur_x = y;
		cur_y = -x;
		*theta = -(angles[0] + angles[0]);
	}

	data_t sigma = 1;
	data_t tempx = 0;
	data_t tempy = 0;
	data_t y_to_shift = 0;
	data_t x_to_shift = 0;
	for (int i = 0; i < NUM_ITER; i++)
	{
#pragma HLS PIPELINE off
		if(cur_y>0)
		{
			y_to_shift = -(cur_y >> i);
			x_to_shift = -(cur_x >> i);

			*theta = (*theta - angles[i]);
		}
		else
		{
			y_to_shift = (cur_y >> i);
			x_to_shift = (cur_x >> i);
			*theta = *theta + angles[i];
		}

		// perform rotation/transformation
		tempx = cur_x;
		tempy = cur_y;
		cur_x = tempx - (y_to_shift);
		cur_y = tempy + (x_to_shift);

	}


	// Set the final radians and phase
	*r = cur_x*cordic_gain[NUM_ITER-1]; *theta = -(*theta);
}
