/*
* @Author: Charlie Gallentine
* @Date:   2019-10-15 20:30:14
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-10-15 22:10:01
*/

#include "dataset.h"


vector<string> *read_file(ifstream &infile);
void split_line(
	string &input, 
	Row **inputs, int in_len, 
	Row **outputs, int out_len);

void dataset_read(
	ifstream &infile, 
	int in_length, 
	int out_length, 
	double train_percent,
	double validate_percent,
	Dataset_t **data)
{
	*data = new Dataset_t;

	int index = 0;

	vector<string> *lines = read_file(infile);
	Row *inputs = new Row();
	Row *outputs = new Row();

	random_shuffle((*lines).begin(), (*lines).end());

	(*data)->total_points = (*lines).size();

	int num_train = (int) ((double) (*lines).size() * train_percent);
	int num_validate = (int) ((double) (*lines).size() * validate_percent);
	int num_test = (*lines).size() - num_train - num_validate;

	(*data)->input_vec_len = in_length;
	(*data)->output_vec_len = out_length;

	(*data)->train.size = num_train;
	(*data)->validate.size = num_validate;
	(*data)->test.size = num_test;


	for (int i = 0; i < num_train; i++)
	{
		split_line((*lines)[index++], &inputs, in_length, &outputs, out_length);
		((*data)->train.inputs).push_back(*inputs);
		((*data)->train.outputs).push_back(*outputs);
		inputs->clear();
		outputs->clear();
	}

	for (int i = 0; i < num_validate; i++)
	{
		split_line((*lines)[index++], &inputs, in_length, &outputs, out_length);
		(*data)->validate.inputs.push_back(*inputs);
		(*data)->validate.outputs.push_back(*outputs);
		inputs->clear();
		outputs->clear();	
	}

	for (int i = 0; i < num_test; i++)
	{
		split_line((*lines)[index++], &inputs, in_length, &outputs, out_length);
		(*data)->test.inputs.push_back(*inputs);
		(*data)->test.outputs.push_back(*outputs);
		inputs->clear();
		outputs->clear();	
	}

}


vector<string> *read_file(ifstream &infile)
{
	int i = 0;
	int res = 10;
	vector<string> *out = new vector<string>();
	string tmp = "";
	out->reserve(res);

	while (getline(infile, tmp))
	{
		out->push_back(tmp);
		if (i++ == res)
		{
			res *= 2;
			out->reserve(res);
		}
		tmp = "";
	}
	return out;
}


void split_line(string &input, Row **inputs, int in_len, Row **outputs, int out_len)
{
	stringstream str_stream(input);

	(*inputs)->reserve(in_len);
	(*outputs)->reserve(out_len);

	string tmp = "";
	double tmp_d = 0.0;

	for (int i = 0; i < in_len; i++)
	{
		str_stream >> tmp;
		tmp_d = stod(tmp);
		(*inputs)->push_back(tmp_d);
	}

	for (int i = 0; i < out_len; i++)
	{
		str_stream >> tmp;
		tmp_d = stod(tmp);
		(*outputs)->push_back(tmp_d);
	}
}









