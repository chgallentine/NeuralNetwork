#ifndef CONVERT_H
#define CONVERT_H

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<double> > Matrix;
typedef vector<double> Row;

int output_int_to_vector(int in, int size, Row **out);
int output_vector_to_int(Row& in, double *out);

#endif