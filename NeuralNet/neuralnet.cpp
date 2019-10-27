/*
* @Author: Charlie Gallentine
* @Date:   2019-10-15 21:57:03
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-10-27 13:03:19
*/

#include "neuralnet.h"
#include "../Matrix/matrix.h"

double frand(double rmin, double rmax);

NeuralNet_t *neuralnet_generate(vector<pair<int, int> >& l_size_type)
{
	NeuralNet_t *nn = new NeuralNet_t();
	nn->layers.reserve(l_size_type.size() + l_size_type.size()-1);

	for (int i = 0; i < (int) l_size_type.size(); i++)
	{
		if (i == 0)
		{
			nn->layers.push_back(
				new Layer_t(
					l_size_type[i].second, i,
					NULL, NULL, 
					make_pair(1,l_size_type[i].first)));

			nn->layers[i]->bias = init_ones_matrix(1,1);
		}
		else
		{
			nn->layers.push_back(
				new Layer_t(
					l_size_type[i].second, i,
					*(nn->layers.end()-1), NULL, 
					make_pair(1,l_size_type[i].first)));

			if (i < (int) l_size_type.size()-1)
			{
				(*(nn->layers.end()-1))->bias = init_ones_matrix(1,1);
			}

		}

		if (i < (int) l_size_type.size()-1)
		{
			nn->layers.push_back(
				new Layer_t(
					WEIGHT, -1,
					*(nn->layers.end()-1), NULL));


			(*(nn->layers.end()-1))->mat = init_rand_matrix(
				(*(nn->layers.end()-2))->mat->col,
				l_size_type[i+1].first, 
				MIN_INIT_WEIGHT, MAX_INIT_WEIGHT);

			(*(nn->layers.end()-1))->bias = init_ones_matrix(1,l_size_type[i+1].first);
		}
	}

	return nn;
}

void neuralnet_set_input(NeuralNet_t *nn, Matrix_t &in)
{
	(*(nn->layers.begin()))->mat->data = in.data;
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
		bias = init_ones_matrix(1, size.second);
	}
	else
	{
		bias = NULL;
	}
}



void neuralnet_feed_forward(NeuralNet_t *nn)
{
	// Matrix_t *bias = NULL;
	Matrix_t *activated = NULL;
	Matrix_t *mult = NULL;

	for (auto it = nn->layers.begin(); it != nn->layers.end() - 1; it+=2)
	{
		if ((*it)->activation != 5)
		{	
			// A(*it)
			activate((*it)->mat, (*it)->activation, &activated);
			
			// A(*it) * W(*(it+1))
			mat_mult(activated, (*(it+1))->mat, &mult);
			
			// init_ones_matrix(1, mult->col, &bias);

			// A(*it) * W(*(it+1)) + 1.0
			if (INCLUDE_BIAS)
			{
				(*(it+2))->mat = mat_add(mult, (*(it+1))->bias);
			}
			else
			{
				(*(it+2))->mat = mat_copy(*mult);
			}
			// mat_free(bias);Z
			mat_free(activated);
			mat_free(mult);
		}
	}
}


void init_rand_matrix(int rows, int cols, double min_range, double max_range, Matrix_t **W)
{
	(*W) = new Matrix_t(rows, cols);

	for (auto row = (*W)->data.begin(); row != (*W)->data.end(); row++)
	{
		for (auto val = row->begin(); val != row->end(); val++)
		{
			*val = frand(min_range, max_range);
		}
	}
}

Matrix_t *init_rand_matrix(int rows, int cols, double min_range, double max_range)
{
	Matrix_t *W = new Matrix_t(rows, cols);

	for (auto row = W->data.begin(); row != W->data.end(); row++)
	{
		for (auto val = row->begin(); val != row->end(); val++)
		{
			*val = frand(min_range, max_range);
		}
	}

	return W;
}

void init_ones_matrix(int rows, int cols, Matrix_t **B)
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

Matrix_t *init_ones_matrix(int rows, int cols)
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
	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
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
	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
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
	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
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

	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
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
	Matrix_t *dzl_dwl = NULL;
	Matrix_t *dal_dzl = NULL;
	Matrix_t *dzlplus1_dal = NULL;
	Matrix_t *passdown_mat = NULL;
	Matrix_t *pd_x_dzlplus1_dal = NULL;
	Matrix_t *pd_elmwise_dal_dzl = NULL;

	Matrix_t *tmp = NULL;

	// Output minus expected values == dE_daL
	dzlplus1_dal = mat_sub((*(nn->layers.end()-1))->mat, &expected);
	if (!dzlplus1_dal) { cout << "ERROR MAT SUB 219\n"; exit(0); }

	// Derivative of activation for layer L
	dal_dzl = d_activate((*(nn->layers.end()-1))->mat, (*(nn->layers.end()-1))->activation);
	if (!dal_dzl) { cout << "ERROR D_ACTIVATE LAST LAYER\n"; exit(0); }

	// Get the activation for layer L-1
	dzl_dwl = mat_copy(*(*(nn->layers.end()-3))->mat);

	// Track the first two terms I.E. dE_dzL
	passdown_mat = mat_elementwise_mult(dzlplus1_dal, dal_dzl);

	mat_transpose_p(dzl_dwl);

	// mat_free((*(nn->layers.end()-2))->d_mat);

	mat_free(tmp);
	tmp = mat_mult(dzl_dwl, passdown_mat);
	if ((*(nn->layers.end()-2))->d_mat == NULL)
	{
		(*(nn->layers.end()-2))->d_mat = mat_copy(*tmp);
		mat_scalar_mult_p(0.0, (*(nn->layers.end()-2))->d_mat);
	}
	mat_add_p(tmp, (*(nn->layers.end()-2))->d_mat);
	// (*(nn->layers.end()-2))->d_mat = mat_mult(dzl_dwl, passdown_mat);

	// mat_free((*(nn->layers.end()-2))->d_bias);
	if (INCLUDE_BIAS)
	{	
		//
		// (*(nn->layers.end()-2))->d_bias = mat_copy(*passdown_mat);	
		// 
		if ((*(nn->layers.end()-2))->d_bias == NULL)
		{
			(*(nn->layers.end()-2))->d_bias = mat_copy(*passdown_mat);
			mat_scalar_mult_p(0.0, (*(nn->layers.end()-2))->d_bias);
		}
		mat_add_p(passdown_mat, (*(nn->layers.end()-2))->d_bias);	
	}

	for (int lyr = (int) nn->layers.size()-3; lyr > 0; lyr -= 2)
	{
		mat_free(dzlplus1_dal);
		dzlplus1_dal = mat_copy(*(nn->layers[lyr + 1]->mat));

		mat_free(dal_dzl);
		dal_dzl = d_activate((nn->layers[lyr])->mat, (nn->layers[lyr])->activation);
		if (!dal_dzl) { cout << "ERROR D_ACTIVATE LAST LAYER\n"; exit(0); }

		mat_free(dzl_dwl);
		dzl_dwl = mat_copy(*(nn->layers[lyr-2])->mat);

		mat_transpose_p(dzlplus1_dal);
		mat_transpose_p(dzl_dwl);

		mat_free(pd_x_dzlplus1_dal);
		pd_x_dzlplus1_dal = mat_mult(passdown_mat, dzlplus1_dal);
		if (!pd_x_dzlplus1_dal) { cout << "ERROR MAT MULT 351\n"; exit(0); }

		pd_elmwise_dal_dzl = mat_elementwise_mult(pd_x_dzlplus1_dal, dal_dzl);
		if (!pd_elmwise_dal_dzl) { cout << "ERROR MAT ELEM MULT 354\n"; exit(0); }

		mat_free(passdown_mat);
		passdown_mat = mat_copy(*pd_elmwise_dal_dzl);

		// mat_free(nn->layers[lyr - 1]->d_mat);
		// 
		mat_free(tmp);
		tmp = mat_mult(dzl_dwl, pd_elmwise_dal_dzl);
		if (!(nn->layers[lyr - 1]->d_mat))
		{
			(nn->layers[lyr - 1]->d_mat) = mat_copy(*tmp);
			mat_scalar_mult_p(0.0, (nn->layers[lyr - 1]->d_mat));
		}
		//
		// nn->layers[lyr - 1]->d_mat = mat_mult(dzl_dwl, pd_elmwise_dal_dzl);
		if (!(nn->layers[lyr - 1]->d_mat)) { cout << "ERROR MAT MULT 361\n"; exit(0); }
		mat_add_p(tmp, nn->layers[lyr - 1]->d_mat);

		// mat_free(nn->layers[lyr - 1]->d_bias);
		if (INCLUDE_BIAS)
		{
			if (nn->layers[lyr - 1]->d_bias == NULL)
			{
				nn->layers[lyr - 1]->d_bias = mat_copy(*passdown_mat);
				mat_scalar_mult_p(0.0, nn->layers[lyr - 1]->d_bias);
			}

			mat_add_p(passdown_mat, nn->layers[lyr - 1]->d_bias);
			// nn->layers[lyr - 1]->d_bias = mat_copy(*passdown_mat);
		}
	}

	mat_free(passdown_mat);
	mat_free(pd_x_dzlplus1_dal);
	mat_free(dzl_dwl);
	mat_free(dal_dzl);
	mat_free(dzlplus1_dal);
	mat_free(pd_elmwise_dal_dzl);
}

void adjust_weight(NeuralNet_t *nn, double lr)
{
	for (int i = 1; i < (int) nn->layers.size()-1; i += 2)
	{
		// Get Average Gradient
		mat_scalar_mult_p((double) 1.0 / TRAINING_EXAMPLES, nn->layers[i]->d_mat);

		// Multiply by learning rate and subtract from weights matrix
		mat_scalar_mult_p(lr, nn->layers[i]->d_mat);
		mat_sub_p(nn->layers[i]->d_mat,nn->layers[i]->mat);

		// Zero out weights matrix for future iterations
		mat_scalar_mult_p(0.0, nn->layers[i]->d_mat);

		// If bias is used, perform above 
		if (nn->layers[i]->d_bias)
		{
			// Get Average Gradient
			mat_scalar_mult_p((double) 1.0 / TRAINING_EXAMPLES, nn->layers[i]->d_bias);
			
			mat_sub_p(nn->layers[i]->d_bias,nn->layers[i]->bias);
			mat_scalar_mult_p(0.0, nn->layers[i]->d_bias);
		}
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

void neuralnet_print_dims(NeuralNet_t &nn)
{
	for (auto lyr = nn.layers.begin(); lyr != nn.layers.end(); lyr++)
	{

	cout 
		<< (*lyr)->id 
		<< ": " << (*lyr)->mat->row 
		<< "x" << (*lyr)->mat->col << endl;
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

	for (int j = 0; j < (int) x.size(); j++)
	{
		total += exp(x[j]);
		total_n_i += (j != i ? exp(x[j]) : 0.0);
	}

	return (exp(x[i]) * (total_n_i)) / pow(total,2);
}


double frand(double rmin, double rmax)
{
	double res = (double) rand() / RAND_MAX;
	return (res * (rmax - rmin)) + rmin;
}

