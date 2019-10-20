/*
* @Author: Charlie Gallentine
* @Date:   2019-10-13 18:10:19
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-10-15 19:56:10
*/

#include "convert.h"

int output_int_to_vector(int index, int size, vector<double> **out)
{
	*out = new vector<double>();

	for (int i = 0; i < size; i++)
	{
		if (i == index-1) { (*out)->push_back(1.0); }
		else { (*out)->push_back(0.0); }
	}

	return 0;
}

int output_vector_to_int(vector<double> &in, double *out)
{	
	for (int i = in.size()-1; i >= 0; i--)
	{
		if (fabs(in[i] - 1.0) < 0.001)
		{
			*out = (double) i + 1;
		}
	}

	return 0;
}

