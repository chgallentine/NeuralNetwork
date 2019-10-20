#ifndef DATASET_H
#define DATASET_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef vector<vector<double> > Matrix;
typedef vector<double> Row;

struct Data_t {
	int size;

	Matrix inputs;
	Matrix outputs;
};


struct Dataset_t {
	int input_vec_len;
	int output_vec_len;
	int total_points;

	Data_t train;
	Data_t validate;
	Data_t test;

};

void dataset_read(
	ifstream &inFile, 
	int in_length, 
	int out_length, 
	double train_percent,
	double validate_percent,
	Dataset_t **dat);

#endif