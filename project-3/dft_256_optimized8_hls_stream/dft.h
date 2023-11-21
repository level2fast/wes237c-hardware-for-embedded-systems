#include "hls_stream.h"
#include "ap_axi_sdata.h"
typedef float DTYPE;
#define SIZE 256 		/* SIZE OF DFT */
typedef ap_axis<32,2,5,6> transPkt;
union fp_int
{
	int i;
	float fp;
};
void dft(hls::stream<transPkt> &real_sample_in, hls::stream<transPkt> &imag_sample_in,
		 hls::stream<transPkt> &real_sample_out, hls::stream<transPkt> &imag_sample_out);
