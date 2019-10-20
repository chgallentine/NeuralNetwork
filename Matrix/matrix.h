#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<double> > Matrix;
typedef vector<double> Row;

struct Matrix_t {
	Matrix data;
	int row, col;
	Matrix_t(Matrix &_data);
	Matrix_t(int _row, int _col);
};

void mat_free(Matrix_t *mat);

int mat_transpose(Matrix_t *in, Matrix_t **res);
int mat_add(Matrix_t *a, Matrix_t *b, Matrix_t **res);
int mat_sub(Matrix_t *a, Matrix_t *b, Matrix_t **res);
int mat_sum(Matrix_t *a, double *sum);
int mat_scalar_mult(double a, Matrix_t *in, Matrix_t **res);
int mat_mult(Matrix_t *a, Matrix_t *b, Matrix_t **res);
int mat_elementwise_mult(Matrix_t *a, Matrix_t *b, Matrix_t **res);
int mat_elementwise_square(Matrix_t *a, Matrix_t **res);
int mat_block_mult(Matrix_t *a, Matrix_t *b, Matrix_t **res);
int mat_horizontal_concat(Matrix_t *a, Matrix_t *b, Matrix_t **res);
int mat_vertical_concat(Matrix_t *a, Matrix_t *b, Matrix_t **res);

Matrix_t *mat_transpose(Matrix_t *in);
Matrix_t *mat_add(Matrix_t *a, Matrix_t *b);
Matrix_t *mat_sub(Matrix_t *a, Matrix_t *b);
double mat_sum(Matrix_t *a);
Matrix_t *mat_scalar_mult(double a, Matrix_t *in);
Matrix_t *mat_mult(Matrix_t *a, Matrix_t *b);
Matrix_t *mat_elementwise_mult(Matrix_t *a, Matrix_t *b);
Matrix_t *mat_elementwise_square(Matrix_t *a);
Matrix_t *mat_block_mult(Matrix_t *a, Matrix_t *b);
Matrix_t *mat_horizontal_concat(Matrix_t *a, Matrix_t *b);
Matrix_t *mat_vertical_concat(Matrix_t *a, Matrix_t *b);

Matrix_t *mat_transpose_p(Matrix_t **in);
Matrix_t *mat_scalar_mult_p(double a, Matrix_t *in);
Matrix_t *mat_elementwise_square_p(Matrix_t *a);

Matrix_t *mat_copy(Matrix_t &a);

void mat_print(Matrix_t *a);
void mat_print(Matrix &a);


#endif

















