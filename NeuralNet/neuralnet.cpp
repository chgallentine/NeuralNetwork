/*
* @Author: Charlie Gallentine
* @Date:   2019-10-15 21:57:03
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-10-20 15:10:28
*/

#include "neuralnet.h"
#include "../Matrix/matrix.h"

double frand(double rmax);

NeuralNet_t *neuralnet_generate(vector<pair<int, int> >& l_size_type)
{
	NeuralNet_t *nn = new NeuralNet_t();
	nn->layers.reserve(l_size_type.size() + l_size_type.size()-1);

	for (int i = 0; i < l_size_type.size(); i++)
	{
		if (i == 0)
		{
			nn->layers.push_back(
				new Layer_t(
					l_size_type[i].second, i,
					NULL, NULL, 
					make_pair(1,l_size_type[i].first)));
		}
		else
		{
			nn->layers.push_back(
				new Layer_t(
					l_size_type[i].second, i,
					*(nn->layers.end()-1), NULL, 
					make_pair(1,l_size_type[i].first)));
		}

		if (i < l_size_type.size()-1)
		{
			nn->layers.push_back(
				new Layer_t(
					WEIGHT, -1,
					*(nn->layers.end()-1), NULL));

			(*(nn->layers.end()-1))->mat = init_weight_matrix(
				(*(nn->layers.end()-2))->mat->col,l_size_type[i+1].first, 3.0);
		}
	}

	return nn;
}

void neuralnet_set_input(NeuralNet_t *nn, Matrix_t &in)
{
	mat_free((*(nn->layers.begin()))->mat);
	(*(nn->layers.begin()))->mat = mat_copy(in);
}

Layer_t::Layer_t(int _act, int _id, Layer_t *_prev, Layer_t *_next)
{
	id = _id;
	activation = _act;
	prev = _prev;
	next = _next;
	if (_prev)
	{
		_prev->next = this;
	}
}

Layer_t::Layer_t(int _act, int _id, Layer_t *_prev, Layer_t *_next, pair<int, int> size) : Layer_t(_act, _id, _prev, _next)
{
	mat = new Matrix_t(size.first,size.second);
	d_mat = new Matrix_t(size.first, size.second);
	if (_id >= 0)
	{
		bias = init_bias_matrix(1, size.second);
	}
	else
	{
		bias = NULL;
	}
}



void neuralnet_feed_forward(NeuralNet_t *nn)
{
	Matrix_t *bias = NULL;
	Matrix_t *activated = NULL;
	Matrix_t *mult = NULL;

	for (auto it = nn->layers.begin(); it != nn->layers.end() - 1; it++)
	{
		if ((*it)->activation != 5)
		{	
			// A(*it)
			activate((*it)->mat, (*it)->activation, &activated);
			
			// A(*it) * W(*(it+1))
			mat_mult(activated, (*(it+1))->mat, &mult);

			init_bias_matrix(1, mult->col, &bias);

			// A(*it) * W(*(it+1)) + 1.0
			(*(it+2))->mat = mat_add(mult, bias);

			mat_free(bias);
			mat_free(activated);
			mat_free(mult);
		}
	}
}


void init_weight_matrix(int rows, int cols, double wrange, Matrix_t **W)
{
	(*W) = new Matrix_t(rows, cols);

	for (auto row = (*W)->data.begin(); row != (*W)->data.end(); row++)
	{
		for (auto val = row->begin(); val != row->end(); val++)
		{
			*val = frand(wrange);
		}
	}
}

Matrix_t *init_weight_matrix(int rows, int cols, double wrange)
{
	Matrix_t *W = new Matrix_t(rows, cols);

	for (auto row = W->data.begin(); row != W->data.end(); row++)
	{
		for (auto val = row->begin(); val != row->end(); val++)
		{
			*val = frand(wrange);
		}
	}

	return W;
}

void init_bias_matrix(int rows, int cols, Matrix_t **B)
{
	(*B) = new Matrix_t(rows, cols);

	for (auto row = (*B)->data.begin(); row != (*B)->data.end(); row++)
	{
		for (auto val = row->begin(); val != row->end(); val++)
		{
			*val = 1.0;
		}
	}
}

Matrix_t *init_bias_matrix(int rows, int cols)
{
	Matrix_t *B = new Matrix_t(rows, cols);

	for (auto row = B->data.begin(); row != B->data.end(); row++)
	{
		for (auto val = row->begin(); val != row->end(); val++)
		{
			*val = 1.0;
		}
	}

	return B;
}

void activate(Matrix_t *a, int activation, Matrix_t **output)
{
	*output = new Matrix_t(a->data.size(), (*(a->data.begin())).size());
	for (int row = 0; row < a->data.size(); row++)
	{
		for (int col = 0; col < (*(a->data.begin())).size(); col++)
		{
			if (activation == SIGMOID)
			{
				(*output)->data[row][col] = sigmoid(a->data[row][col]);
			}
			else if (activation == TANH)
			{
				(*output)->data[row][col] = tanh(a->data[row][col]);
			}
			else if (activation == RELU)
			{
				(*output)->data[row][col] = ReLU(a->data[row][col]);
			}
			else if (activation == INPUT)
			{
				(*output)->data[row][col] = a->data[row][col];
			}
		}
	}
}

Matrix_t *activate(Matrix_t *a, int activation)
{
	Matrix_t *res = new Matrix_t(a->data.size(), (*(a->data.begin())).size());
	for (int row = 0; row < a->data.size(); row++)
	{
		for (int col = 0; col < (*(a->data.begin())).size(); col++)
		{
			if (activation == SIGMOID)
			{
				res->data[row][col] = sigmoid(a->data[row][col]);
			}
			else if (activation == TANH)
			{
				res->data[row][col] = tanh(a->data[row][col]);
			}
			else if (activation == RELU)
			{
				res->data[row][col] = ReLU(a->data[row][col]);
			}
			else if (activation == INPUT)
			{
				res->data[row][col] = a->data[row][col];
			}
		}
	}

	return res;
}

void d_activate(Matrix_t *a, int activation, Matrix_t **output)
{
	*output = new Matrix_t(a->data.size(), (*(a->data.begin())).size());
	for (int row = 0; row < a->data.size(); row++)
	{
		for (int col = 0; col < (*(a->data.begin())).size(); col++)
		{
			if (activation == SIGMOID)
			{
				(*output)->data[row][col] = d_sigmoid(a->data[row][col]);
			}
			else if (activation == TANH)
			{
				(*output)->data[row][col] = d_tanh(a->data[row][col]);
			}
			else if (activation == RELU)
			{
				(*output)->data[row][col] = d_ReLU(a->data[row][col]);
			}
			else if (activation == INPUT)
			{
				(*output)->data[row][col] = a->data[row][col];
			}
		}
	}
}

Matrix_t *d_activate(Matrix_t *a, int activation)
{
	Matrix_t *res = new Matrix_t(a->data.size(), (*(a->data.begin())).size());

	for (int row = 0; row < a->data.size(); row++)
	{
		for (int col = 0; col < (*(a->data.begin())).size(); col++)
		{
			if (activation == SIGMOID)
			{
				res->data[row][col] = d_sigmoid(a->data[row][col]);
			}
			else if (activation == TANH)
			{
				res->data[row][col] = d_tanh(a->data[row][col]);
			}
			else if (activation == RELU)
			{
				res->data[row][col] = d_ReLU(a->data[row][col]);
			}
			else if (activation == INPUT)
			{
				res->data[row][col] = a->data[row][col];
			}
		}
	}

	return res;
}

double calc_error(NeuralNet_t &nn, Matrix_t &expected, Matrix_t **err)
{
	Matrix_t *diff = NULL;
	Matrix_t *square = NULL;
	Matrix_t *mult = NULL;
	Matrix_t *div = NULL;
	double error;

	mat_sub((*(nn.layers.end()-1))->mat, &expected, &diff);
	mat_elementwise_square(diff, &square);
	mat_scalar_mult(0.5, square, &div);

	(*err) = mat_copy(*div);
	error = mat_sum(div);

	mat_free(diff);
	mat_free(square);
	mat_free(mult);
	mat_free(div);

	return error;
}


void backprop(NeuralNet_t *nn, Matrix_t &expected, Matrix_t &err)
{
	// dZ^(l+1)/dA^l == w^(l+1) == The weight matrix of the next highest layer
	Matrix_t *w_lplus1 = NULL; 
	// dA^l/dZ^l == d_actiavte function for current layer
	Matrix_t *A_l_prime = NULL;
	// dZ^l/dW^l == A^(l-1) == the activation of the next lower layer
	Matrix_t *A_lminus1 = NULL;

	Matrix_t *layer_input = NULL;

	Matrix_t *passdown_mat = NULL; // For each layer, value passed on
	Matrix_t *pass_mat_cpy = NULL;

	// // Input to (output layer - 1)
	// cout << "MAT MULT 324\n";
	layer_input = mat_mult((*(nn->layers.end()-3))->mat, (*(nn->layers.end()-2))->mat);
	// The derivative of the output layer
	A_l_prime = d_activate(layer_input, (*(nn->layers.end()-1))->activation);

	// Calculate the derivative of the error function WRT output
	w_lplus1 = mat_sub((*(nn->layers.end()-1))->mat, &expected);
	passdown_mat = mat_elementwise_mult(w_lplus1, A_l_prime);

	A_lminus1 = mat_transpose((*(nn->layers.end()-3))->mat);

	// Set the Lth weight delta matrix 
	// cout << "MAT MULT 326\n";
	mat_mult(A_lminus1, passdown_mat, &(*(nn->layers.end()-2))->d_mat);

	mat_free(w_lplus1);
	mat_free(A_l_prime);
	mat_free(layer_input);
	mat_free(A_lminus1);


	for (int i = nn->layers.size()-3; i > 0; i-=2)
	{		
		// cout << "MAT MULT 346\n";
		layer_input = mat_mult((*(nn->layers[i-2])).mat, (*(nn->layers[i-1])).mat);

		w_lplus1 = nn->layers[i+1]->mat;
		A_l_prime = d_activate(layer_input, (*(nn->layers[i])).activation);

		A_lminus1 = mat_transpose((*(nn->layers[i-2])).mat);

		pass_mat_cpy = mat_copy(*passdown_mat);

		Matrix_t *pd_x_w_lplus1_T = mat_mult(pass_mat_cpy, mat_transpose_p(&w_lplus1));
		Matrix_t *pd_x_w_lplus1_T_dotx_a_prime_l = mat_elementwise_mult(A_l_prime, pd_x_w_lplus1_T);

		mat_free(passdown_mat);
		passdown_mat = mat_copy(*pd_x_w_lplus1_T_dotx_a_prime_l);

		// cout << "MAT MULT 363\n";
	 	mat_mult(A_lminus1, passdown_mat, &(*(nn->layers[i-1])).d_mat);


		mat_free(w_lplus1);
		mat_free(A_l_prime);
		mat_free(layer_input);
		mat_free(A_lminus1);
		mat_free(pass_mat_cpy);
		mat_free(pd_x_w_lplus1_T);
		mat_free(pd_x_w_lplus1_T_dotx_a_prime_l);
	}	
}

void adjust_weight(NeuralNet_t *nn, double lr)
{
	Matrix_t *tmp_sub = NULL;
	// Hit each weight layer
	for (int i = 1; i < nn->layers.size()-1; i += 2)
	{
		nn->layers[i]->d_mat = mat_scalar_mult_p(lr, nn->layers[i]->d_mat);
		// cout << "fine1\n";
		mat_sub(nn->layers[i]->mat,nn->layers[i]->d_mat,&tmp_sub);
		// cout << "fine2\n";
		// mat_free(nn->layers[i]->mat);
		// cout << "fine3\n";
		// mat_free(nn->layers[i]->d_mat);
		// cout << "fine4\n";

		nn->layers[i]->mat = mat_copy(*tmp_sub);
		// cout << "fine5\n";
		// mat_free(tmp_sub);
	}
}

void neuralnet_print(NeuralNet_t *nn)
{
	Layer_t *curr = *(nn->layers.begin());

	while (curr != NULL)
	{
		if (curr->activation != 5)
		{
			cout
				<< "Layer: " << curr->id << endl
				<< "Size: " << curr->mat->row << "x" << curr->mat->col << endl
				<< "Activation: " << 
					(curr->activation == 0 ? "INPUT"	: 
					 curr->activation == 1 ? "SIGMOID"	:
					 curr->activation == 2 ? "TANH"		: 
					 curr->activation == 3 ? "ReLU"		:
					 curr->activation == 4 ? "SOFTMAX"	:
					 "WEIGHT"
					 ) << endl;
		}
		else
		{
			cout 
				<< "\nWEIGHT LAYER: "
				<< curr->mat->row << "x" << curr->mat->col << endl << endl;
		}

		curr = curr->next;
	}
}

void neuralnet_print(NeuralNet_t *nn, bool tf)
{
	Layer_t *curr = *(nn->layers.begin());

	while (curr != NULL)
	{
		if (curr->activation != 5)
		{
			cout
				<< "Layer: " << curr->id << endl
				<< "Size: " << curr->mat->row << "x" << curr->mat->col << endl
				<< "Activation: " << 
					(curr->activation == 0 ? "INPUT"	: 
					 curr->activation == 1 ? "SIGMOID"	:
					 curr->activation == 2 ? "TANH"		: 
					 curr->activation == 3 ? "ReLU"		:
					 curr->activation == 4 ? "SOFTMAX"	:
					 "WEIGHT"
					 ) << endl;
		}
		else
		{
			cout 
				<< "\nWEIGHT LAYER: "
				<< curr->mat->row << "x" << curr->mat->col << endl;
		}

		if (tf)
		{
			mat_print(curr->mat);
			cout << endl;
		}

		curr = curr->next;
	}
}






double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
double ReLU(double x) { return x > 0 ? x : 0; }
double tanh(double x) { return 2.0 * (2.0 * (1.0/(1.0+exp(-2.0 * x)))) - 1.0; }
double softmax(int i, Row& x)
{
	double total = 0.0;
	for (auto it = x.begin(); it != x.end(); it++)
	{
		total += exp(*it);
	}

	return exp(x[i]) / total;
}
double d_sigmoid(double x) { return sigmoid(x) * (1 - sigmoid(x)); }
double d_ReLU(double x) { return x > 0 ? 1.0 : 0.0; }
double d_tanh(double x) { return 1.0 - pow(tanh(x),2); }
double d_softmax(int i, Row& x)
{
	double total = 0.0;
	double total_n_i = 0.0;

	for (int j = 0; j < x.size(); j++)
	{
		total += exp(x[j]);
		total_n_i += (j != i ? exp(x[j]) : 0.0);
	}

	return (exp(x[i]) * (total_n_i)) / pow(total,2);
}


double frand(double rmax)
{
	double res = (double) rand() / RAND_MAX;
	return -rmax + 2 * rmax * res;
}

