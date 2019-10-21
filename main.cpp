/*
* @Author: Charlie Gallentine
* @Date:   2019-10-11 09:33:34
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-10-21 11:10:31
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
		make_pair(5, RELU),
		make_pair(7, RELU), 
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
	double prev = (double) INT_MAX; 
	double avg_train = 0.0;
	int count = 0;

	while (true)
	{
		i++;

		neuralnet_set_input(neuralnet, inputs[i % inputs.size()]);

		neuralnet_feed_forward(neuralnet);

		// neuralnet_print(neuralnet, true);
		errors[i % inputs.size()] = calc_error(*neuralnet, outputs[i % inputs.size()], &err);


		if (i % 2000 == 0)
		{
			prev = avg_train;
			avg_train = 0.0;

			cout << "EPOCH[" << j<< ":" << i << "] ERROR: ";
			for (int t = 0; t < inputs.size(); t++) 
			{ 
				cout << "\t" << errors[t];

				avg_train += errors[t];
			}
			avg_train /= inputs.size();

			if (i > 4000 && prev - avg_train <= 0) { 
				count++;
			}

			if (count > 10)
			{
				cout << "\n\nDONE TRAINING\n"; 
				cout << "PREV: " <<  prev << " CURR: " << avg_train << endl;
				break; 
			}
			cout << endl;
			if (i == 1000000) { i = 0; j++; }

		}	

		backprop(neuralnet, nn_output, *err);
		adjust_weight(neuralnet, 0.2);
	}

	cout << "INPUT 1,1\n";
	nn_input.data[0][0] = 1.0;
	nn_input.data[0][1] = 1.0;

	neuralnet_set_input(neuralnet, nn_input);
	neuralnet_feed_forward(neuralnet);

	mat_print((*(neuralnet->layers.end()-1))->mat);

	cout << "INPUT 1,0\n";
	nn_input.data[0][0] = 1.0;
	nn_input.data[0][1] = 0.0;

	neuralnet_set_input(neuralnet, nn_input);
	neuralnet_feed_forward(neuralnet);

	mat_print((*(neuralnet->layers.end()-1))->mat);

	cout << "INPUT 0,1\n";
	nn_input.data[0][0] = 0.0;
	nn_input.data[0][1] = 1.0;

	neuralnet_set_input(neuralnet, nn_input);
	neuralnet_feed_forward(neuralnet);

	mat_print((*(neuralnet->layers.end()-1))->mat);

	cout << "INPUT 0,0\n";
	nn_input.data[0][0] = 0.0;
	nn_input.data[0][1] = 0.0;

	neuralnet_set_input(neuralnet, nn_input);
	neuralnet_feed_forward(neuralnet);

	mat_print((*(neuralnet->layers.end()-1))->mat);

	return 0;
}
















