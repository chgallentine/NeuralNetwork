#include "../Matrix/matrix.h"

#ifndef NEURALNET_H
#define NEURALNET_H

#include <cmath>
#include <utility>
#include <vector>

#define INPUT 	0
#define SIGMOID 1
#define TANH 	2
#define RELU 	3
#define SOFTMAX 4
#define WEIGHT 	5

using namespace std;

typedef vector<vector<double> > Matrix;
typedef vector<double> Row;

struct Layer_t;
struct NeuralNet_t;

struct Layer_t {
	int activation; // Input/ReLU/SIGMOID/ETC
	int id;

	Matrix_t *mat;
	Matrix_t *d_mat;

	Matrix_t *bias;

	// Doubly linked list of layers
	Layer_t *prev;
	Layer_t *next;

	Layer_t();
	Layer_t(int _act, int _id, Layer_t *_prev, Layer_t *_next);
	Layer_t(int _act, int _id, Layer_t *_prev, Layer_t *_next, pair<int, int> size);
};

struct NeuralNet_t {
	vector<Layer_t*> layers;
};

NeuralNet_t *neuralnet_generate(vector<pair<int, int> >& l_type_size);
void neuralnet_set_input(NeuralNet_t *nn, Matrix_t &in);

void neuralnet_print(NeuralNet_t *nn);
void neuralnet_print(NeuralNet_t *nn, bool tf);

void neuralnet_feed_forward(NeuralNet_t *nn);

void init_weight_matrix(int rows, int cols, double wrange, Matrix_t **W);
Matrix_t *init_weight_matrix(int rows, int cols, double wrange);

void init_bias_matrix(int rows, int cols, Matrix_t **B);
Matrix_t *init_bias_matrix(int rows, int cols);

void activate(Matrix_t *a, int activation, Matrix_t **output);
Matrix_t *activate(Matrix_t *a, int activation);
Matrix_t *d_activate(Matrix_t *a, int activation);

double calc_error(NeuralNet_t &nn, Matrix_t &expected, Matrix_t **err);

void backprop(NeuralNet_t *nn, Matrix_t &expected, Matrix_t &err);

void adjust_weight(NeuralNet_t *nn, double lr);

double sigmoid(double x);
double ReLU(double x);
double tanh(double x);
double softmax(int i, Row& x);

double d_sigmoid(double x);
double d_ReLU(double x);
double d_tanh(double x);
double d_softmax(int i, Row& x);

#endif