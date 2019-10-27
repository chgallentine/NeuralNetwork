/*
* @Author: Charlie Gallentine
* @Date:   2019-10-11 09:33:34
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-10-27 16:59:37
*/

#include <iomanip>
#include <iostream>
#include <utility>
#include <climits>


#include "./Matrix/matrix.h"
#include "./NeuralNet/neuralnet.h"
#include "./Convert/convert.h"
#include "./Dataset/dataset.h"


using namespace std;

int main(int argc, char **argv)
{
	srand(time(NULL));

	vector<pair<int,int> > layers = { 
		make_pair(2, INPUT),
		make_pair(5, SIGMOID),
		make_pair(1, SIGMOID)
	};

	Matrix_t *err = NULL;

	vector<Matrix_t> inputs;
	vector<Matrix_t> outputs;

	double total_error;

	Matrix_t nn_input(1,2);
	Matrix_t nn_output(1,1);

	nn_input.data[0][0] = 0.0;
	nn_input.data[0][1] = 0.0;
	
	nn_output.data[0][0] = 0.1;

	inputs.push_back(nn_input);
	outputs.push_back(nn_output);


	nn_input.data[0][0] = 1.0;
	nn_input.data[0][1] = 1.0;
	
	nn_output.data[0][0] = 0.1;

	inputs.push_back(nn_input);
	outputs.push_back(nn_output);


	nn_input.data[0][0] = 1.0;
	nn_input.data[0][1] = 0.0;
	
	nn_output.data[0][0] = 0.9;

	inputs.push_back(nn_input);
	outputs.push_back(nn_output);

	nn_input.data[0][0] = 0.0;
	nn_input.data[0][1] = 1.0;
	
	nn_output.data[0][0] = 0.9;

	inputs.push_back(nn_input);
	outputs.push_back(nn_output);


	NeuralNet_t *neuralnet = neuralnet_generate(layers);

	cout << "=============================\n";
	double curr, prev;
	double lr = 0.01;

	for (int i = 0; i < 50000000; i++)
	{
		total_error = 0.0;
		for (int j = 0; j < inputs.size(); j++)
		{
			neuralnet_set_input(neuralnet, inputs[j]);
			neuralnet_feed_forward(neuralnet);
			total_error += calc_error(*neuralnet, outputs[j], &err);

			backprop(neuralnet, outputs[j], *err);
		}

		if (i % 4000 == 0)
		{
			prev = curr;
			curr = total_error;

			if (i > 20000 && curr-prev >= 0) { break; }

			if (prev - curr < 0.001 && prev - curr > 0.0001) { lr += 0.002; }
			else if (prev - curr > 0.003 && lr > 0.01) { lr -= (lr > 0 ? 0.006 : 0.0); }

			cout << i << ". TOTAL ERROR: " << setprecision(6) << total_error << endl;

			if (total_error < 0.00001) {break;}
		}

		adjust_weight(neuralnet, .8);
	} 


	cout << "\nINPUT 1,1\n";
	nn_input.data[0][0] = 1.0;
	nn_input.data[0][1] = 1.0;

	neuralnet_set_input(neuralnet, nn_input);
	neuralnet_feed_forward(neuralnet);

	mat_print((*(neuralnet->layers.end()-1))->mat);

	cout << endl;
	cout << "\nINPUT 1,0\n";
	nn_input.data[0][0] = 1.0;
	nn_input.data[0][1] = 0.0;

	neuralnet_set_input(neuralnet, nn_input);
	neuralnet_feed_forward(neuralnet);

	mat_print((*(neuralnet->layers.end()-1))->mat);
	cout << endl;

	cout << endl;
	cout << "\nINPUT 0,1\n";
	nn_input.data[0][0] = 0.0;
	nn_input.data[0][1] = 1.0;
	cout << endl << endl;
	neuralnet_set_input(neuralnet, nn_input);
	neuralnet_feed_forward(neuralnet);

	mat_print((*(neuralnet->layers.end()-1))->mat);
	cout << endl;

	cout << "\nINPUT 0,0\n";
	nn_input.data[0][0] = 0.0;
	nn_input.data[0][1] = 0.0;

	neuralnet_set_input(neuralnet, nn_input);
	neuralnet_feed_forward(neuralnet);

	mat_print((*(neuralnet->layers.end()-1))->mat);

	return 0;
}
















