/*
* @Author: Charlie Gallentine
* @Date:   2019-10-11 09:33:34
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-10-20 15:31:34
*/

#include <iostream>
#include <utility>


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
		make_pair(2, SIGMOID),
		make_pair(5, SIGMOID),
		make_pair(7, SIGMOID), 
		make_pair(5, SIGMOID),
		make_pair(2, SIGMOID)
	};

	Matrix_t *err = NULL;

	vector<Matrix_t> inputs;
	vector<Matrix_t> outputs;

	double errors[4];

	Matrix_t nn_input(1,2);
	Matrix_t nn_output(1,2);
	

	nn_input.data[0][0] = 1.0;
	nn_input.data[0][1] = 1.0;
	
	nn_output.data[0][0] = 0.0;
	nn_output.data[0][1] = 0.0;

	inputs.push_back(nn_input);
	outputs.push_back(nn_output);

	nn_input.data[0][0] = 1.0;
	nn_input.data[0][1] = 0.0;
	
	nn_output.data[0][0] = 0.0;
	nn_output.data[0][1] = 1.0;

	inputs.push_back(nn_input);
	outputs.push_back(nn_output);

	nn_input.data[0][0] = 0.0;
	nn_input.data[0][1] = 1.0;
	
	nn_output.data[0][0] = 1.0;
	nn_output.data[0][1] = 0.0;

	inputs.push_back(nn_input);
	outputs.push_back(nn_output);

	nn_input.data[0][0] = 0.0;
	nn_input.data[0][1] = 0.0;
	
	nn_output.data[0][0] = 1.0;
	nn_output.data[0][1] = 1.0;

	inputs.push_back(nn_input);
	outputs.push_back(nn_output);

	NeuralNet_t *neuralnet = neuralnet_generate(layers);

	cout << "=============================\n";
	int i = 0, j = 0;
	while (true)
	{
		i++;

		neuralnet_set_input(neuralnet, inputs[i % 4]);

		neuralnet_feed_forward(neuralnet);

		// neuralnet_print(neuralnet, true);
		errors[i % 4] = calc_error(*neuralnet, outputs[i % 4], &err);

		if (i % 1000 == 0)
		{
			cout << "EPOCH[" << j<< ":" << i << "] ERROR: ";
			for (int t = 0; t < 4; t++) { cout << "\t" << errors[t];}
			cout << endl;
			if (i == 1000000) { i = 0; j++; }
		}	

		backprop(neuralnet, nn_output, *err);
		adjust_weight(neuralnet, 0.005);
	}

	return 0;
}
















