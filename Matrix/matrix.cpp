/*
* @Author: Charlie Gallentine
* @Date:   2019-10-11 09:33:40
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-10-24 16:35:17
*/

#include "matrix.h"

Row *get_column(int _col, Matrix &_data);
double vec_mult_sum(Row &a, Row &b);
void mat_sub_insert(Matrix_t *_src, int _row, int _col, Matrix_t *_dest);

int mat_transpose(Matrix_t *in, Matrix_t **res)
{
	// Initialize matrix of zeros in transposed size
	*res = new Matrix_t((*(in->data.begin())).size(), in->data.size());

	// For each column in the input matrix
	for (int col = 0; col < (int) in->data[0].size(); col++)
	{
		// For each row in the input matrix
		for (int row = 0; row < (int) in->data.size(); row++)
		{
			(*res)->data[col][row] = in->data[row][col];
		}
	}

	return 0;
}

Matrix_t *mat_transpose(Matrix_t *in)
{
	// Initialize matrix of zeros in transposed size
	Matrix_t *res = new Matrix_t((*(in->data.begin())).size(), in->data.size());

	// For each column in the input matrix
	for (int col = 0; col < (int) in->data[0].size(); col++)
	{
		// For each row in the input matrix
		for (int row = 0; row < (int) in->data.size(); row++)
		{
			res->data[col][row] = in->data[row][col];
		}
	}

	return res;	
}

int mat_transpose_p(Matrix_t *in)
{
	// Initialize matrix of zeros in transposed size
	Matrix_t *res = new Matrix_t((*(in->data.begin())).size(), in->data.size());

	// For each column in the input matrix
	for (int col = 0; col < (int) in->data[0].size(); col++)
	{
		// For each row in the input matrix
		for (int row = 0; row < (int) in->data.size(); row++)
		{
			res->data[col][row] = in->data[row][col];
		}
	}

	mat_copy_data(in, res);
	free(res);

	return 0;
}

Matrix_t *mat_transpose_r(Matrix_t **in)
{
	// Initialize matrix of zeros in transposed size
	Matrix_t *res = new Matrix_t((*((*in)->data.begin())).size(), (*in)->data.size());

	// For each column in the input matrix
	for (int col = 0; col < (int) (*in)->data[0].size(); col++)
	{
		// For each row in the input matrix
		for (int row = 0; row < (int) (*in)->data.size(); row++)
		{
			res->data[col][row] = (*in)->data[row][col];
		}
	}

	mat_free(*in);
	*in = res;

	return res;	
}

int mat_add(Matrix_t *a, Matrix_t *b, Matrix_t **res)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return 1; }
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return 2; }

	*res = new Matrix_t(a->data.size(), (*(a->data.begin())).size());

	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
		{
			(*res)->data[row][col] = a->data[row][col] + b->data[row][col];
		}
	}

	return 0;
}

int mat_add_p(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return 1; }
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return 2; }

	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
		{
			b->data[row][col] += a->data[row][col];
		}
	}

	return 0;
}


Matrix_t *mat_add(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return NULL; }
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return NULL; }

	Matrix_t *res = new Matrix_t(a->data.size(), (*(a->data.begin())).size());

	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
		{
			res->data[row][col] = a->data[row][col] + b->data[row][col];
		}
	}

	return res;	
}

int mat_sub(Matrix_t *a, Matrix_t *b, Matrix_t **res)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return 1; }
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return 2; }

	*res = new Matrix_t(a->data.size(), (*(a->data.begin())).size());

	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
		{
			(*res)->data[row][col] = a->data[row][col] - b->data[row][col];
		}
	}

	return 0;
}

int mat_sub_p(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return 1; }
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return 2; }

	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
		{
			b->data[row][col] -= a->data[row][col];
		}
	}

	return 0;
}

Matrix_t *mat_sub(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return NULL; }
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return NULL; }

	Matrix_t *res = new Matrix_t(a->data.size(), (*(a->data.begin())).size());

	for (int row = 0; row < (int) a->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(a->data.begin())).size(); col++)
		{
			res->data[row][col] = a->data[row][col] - b->data[row][col];
		}
	}

	return res;	
}

int mat_scalar_mult(double a, Matrix_t *in, Matrix_t **res)
{
	*res = new Matrix_t(in->data.size(), (*(in->data.begin())).size());

	for (int row = 0; row < (int) in->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(in->data.begin())).size(); col++)
		{
			(*res)->data[row][col] = in->data[row][col] * a;
		}
	}

	return 0;
}

Matrix_t *mat_scalar_mult(double a, Matrix_t *in)
{
	Matrix_t *res = new Matrix_t(in->data.size(), (*(in->data.begin())).size());

	for (int row = 0; row < (int) in->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(in->data.begin())).size(); col++)
		{
			res->data[row][col] = in->data[row][col] * a;
		}
	}

	return res;	
}

Matrix_t *mat_scalar_mult_r(double a, Matrix_t *in)
{
	for (int row = 0; row < (int) in->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(in->data.begin())).size(); col++)
		{
			in->data[row][col] = in->data[row][col] * a;
		}
	}

	return in;	
}

int mat_scalar_mult_p(double a, Matrix_t *in)
{
	for (int row = 0; row < (int) in->data.size(); row++)
	{
		for (int col = 0; col < (int) (*(in->data.begin())).size(); col++)
		{
			in->data[row][col] *= a;
		}
	}

	return 0;
}

int mat_mult(Matrix_t *a, Matrix_t *b, Matrix_t **res)
{
	// Check for size mismatch
	if (b->data.size() != (*(a->data.begin())).size()) 
	{ 
		cout << "MISMATCH in MAT_MULT\n";
		cout 
			<< "A: " << a->data.size() << "x" << (*(a->data.begin())).size()
			<< "\nB: " 
			<< b->data.size() << "x" << (*(b->data.begin())).size() << endl;
		return 1; 
	}
	// if (b->data.size() != (*(a->data.begin())).size()) { return 2; }

	double row_by_col = 0.0;

	*res = new Matrix_t(a->data.size(), (*(b->data.begin())).size());

	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		row_by_col = 0.0;

		for (int b_col = 0; b_col < (int) (*(b->data.begin())).size(); b_col++)
		{
			row_by_col = vec_mult_sum(a->data[a_row], *get_column(b_col, b->data));

			(*res)->data[a_row][b_col] = row_by_col;
		}
	}

	return 0;
}

Matrix_t *mat_mult(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (b->data.size() != (*(a->data.begin())).size()) 
	{ 
		cout << "MISMATCH in MAT_MULT\n";
		cout 
			<< "A: " << a->data.size() << "x" << (*(a->data.begin())).size()
			<< "\nB: " 
			<< b->data.size() << "x" << (*(b->data.begin())).size() << endl;
		return NULL; 
	}
	// if (b->data.size() != (*(a->data.begin())).size()) { return 2; }

	double row_by_col = 0.0;

	Matrix_t *res = new Matrix_t(a->data.size(), (*(b->data.begin())).size());

	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		row_by_col = 0.0;

		for (int b_col = 0; b_col < (int) (*(b->data.begin())).size(); b_col++)
		{
			row_by_col = vec_mult_sum(a->data[a_row], *get_column(b_col, b->data));

			res->data[a_row][b_col] = row_by_col;
		}
	}

	return res;
}

int mat_mult_p(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (b->data.size() != (*(a->data.begin())).size()) 
	{ 
		cout << "MISMATCH in MAT_MULT_P\n";
		cout 
			<< "A: " << a->data.size() 
			<< "x" << (*(a->data.begin())).size()
			<< "\nB: " << b->data.size() 
			<< "x" << (*(b->data.begin())).size() << endl;
		return 1; 
	}
	// if (b->data.size() != (*(a->data.begin())).size()) { return 2; }

	double row_by_col = 0.0;

	Matrix_t *res = new Matrix_t(a->data.size(), (*(b->data.begin())).size());

	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		row_by_col = 0.0;

		for (int b_col = 0; b_col < (int) (*(b->data.begin())).size(); b_col++)
		{
			row_by_col = vec_mult_sum(a->data[a_row], *get_column(b_col, b->data));

			res->data[a_row][b_col] = row_by_col;
		}
	}

	mat_copy_data(b, res);
	free(res);

	return 0;
}

int mat_elementwise_mult(Matrix_t *a, Matrix_t *b, Matrix_t **res)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return 1; }
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return 2; }

	*res = new Matrix_t(a->data.size(), (*(b->data.begin())).size());

	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			(*res)->data[a_row][a_col] = a->data[a_row][a_col] * b->data[a_row][a_col];
		}
	}

	return 0;
}

Matrix_t *mat_elementwise_mult(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return NULL; }
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return NULL; }

	Matrix_t *res = new Matrix_t(a->data.size(), (*(b->data.begin())).size());

	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			res->data[a_row][a_col] = a->data[a_row][a_col] * b->data[a_row][a_col];
		}
	}

	return res;	
}

int mat_elementwise_mult_p(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return 1; }
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return 2; }

	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			b->data[a_row][a_col] *= a->data[a_row][a_col];
		}
	}

	return 0;
}


int mat_elementwise_square(Matrix_t *a, Matrix_t **res)
{
	*res = new Matrix_t(a->data.size(), (*(a->data.begin())).size());


	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			(*res)->data[a_row][a_col] = pow(a->data[a_row][a_col],2);
		}
	}

	return 0;
}

Matrix_t *mat_elementwise_square(Matrix_t *a)
{
	Matrix_t *res = new Matrix_t(a->data.size(), (*(a->data.begin())).size());

	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			res->data[a_row][a_col] = pow(a->data[a_row][a_col],2);
		}
	}

	return res;	
}


Matrix_t *mat_elementwise_square_r(Matrix_t *a)
{
	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			a->data[a_row][a_col] = pow(a->data[a_row][a_col],2);
		}
	}

	return a;	
}

int mat_elementwise_square_p(Matrix_t *a)
{
	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			a->data[a_row][a_col] = pow(a->data[a_row][a_col],2);
		}
	}

	return 0;
}

int mat_sum(Matrix_t *a, double *res)
{
	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			*res += a->data[a_row][a_col];
		}
	}

	return 0;
}

double mat_sum(Matrix_t *a)
{
	double res = 0.0;
	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			res += a->data[a_row][a_col];
		}
	}

	return res;	
}

int mat_block_mult(Matrix_t *a, Matrix_t *b, Matrix_t **res)
{
	*res = new Matrix_t(
		a->data.size() * b->data.size(), 
		(*(a->data.begin())).size() * (*(b->data.begin())).size());

	Matrix_t *tmp_mat = NULL;
	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			mat_scalar_mult(a->data[a_row][a_col], b, &tmp_mat);

			mat_sub_insert(
				tmp_mat, 
				a_row * b->data.size(),
				a_col * (*(b->data.begin())).size(), *res);
		}
	}

	return 0;
}

Matrix_t *mat_block_mult(Matrix_t *a, Matrix_t *b)
{
	Matrix_t *res = new Matrix_t(
		a->data.size() * b->data.size(), 
		(*(a->data.begin())).size() * (*(b->data.begin())).size());

	Matrix_t *tmp_mat = NULL;
	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			mat_scalar_mult(a->data[a_row][a_col], b, &tmp_mat);

			mat_sub_insert(
				tmp_mat, 
				a_row * b->data.size(),
				a_col * (*(b->data.begin())).size(), res);
		}
	}

	return res;	
}

int mat_block_mult_p(Matrix_t *a, Matrix_t *b)
{
	Matrix_t *res = new Matrix_t(
		a->data.size() * b->data.size(), 
		(*(a->data.begin())).size() * (*(b->data.begin())).size());

	Matrix_t *tmp_mat = NULL;
	for (int a_row = 0; a_row < (int) a->data.size(); a_row++)
	{
		for (int a_col = 0; a_col < (int) (*(a->data.begin())).size(); a_col++)
		{
			mat_scalar_mult(a->data[a_row][a_col], b, &tmp_mat);

			mat_sub_insert(
				tmp_mat, 
				a_row * b->data.size(),
				a_col * (*(b->data.begin())).size(), res);
		}
	}

	mat_copy_data(b, res);
	free(res);

	return 0;
}

int mat_horizontal_concat(Matrix_t *a, Matrix_t *b, Matrix_t **res)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return 1; }

	*res = new Matrix_t(
		a->data.size(), 
		(*(a->data.begin())).size() + (*(b->data.begin())).size());

	mat_sub_insert(a, 0, 0, *res);
	mat_sub_insert(b, 0, (*(b->data.begin())).size(), *res);

	return 0;
}

Matrix_t *mat_horizontal_concat(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return NULL; }

	Matrix_t *res = new Matrix_t(
		a->data.size(), 
		(*(a->data.begin())).size() + (*(b->data.begin())).size());

	mat_sub_insert(a, 0, 0, res);
	mat_sub_insert(b, 0, (*(b->data.begin())).size(), res);

	return res;	
}


int mat_horizontal_concat_p(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if (a->data.size() != b->data.size()) { return 1; }

	Matrix_t *res = new Matrix_t(
		a->data.size(), 
		(*(a->data.begin())).size() + (*(b->data.begin())).size());

	mat_sub_insert(a, 0, 0, res);
	mat_sub_insert(b, 0, (*(b->data.begin())).size(), res);

	mat_copy_data(b, res);
	free(res);

	return 0;
}

int mat_vertical_concat(Matrix_t *a, Matrix_t *b, Matrix_t **res)
{
	// Check for size mismatch
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return 1; }

	*res = new Matrix_t(
		a->data.size() + b->data.size(), 
		(*(a->data.begin())).size());

	mat_sub_insert(a, 0, 0, *res);
	mat_sub_insert(b, b->data.size(), 0, *res);

	return 0;
}

Matrix_t *mat_vertical_concat(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return NULL; }

	Matrix_t *res = new Matrix_t(
		a->data.size() + b->data.size(), 
		(*(a->data.begin())).size());

	mat_sub_insert(a, 0, 0, res);
	mat_sub_insert(b, b->data.size(), 0, res);

	return res;
}

Matrix_t *mat_copy(Matrix_t &a)
{
	Matrix_t *cpy = new Matrix_t(a.data.size(), a.data.begin()->size());

	for (int row = 0; row < (int) a.data.size(); row++)
	{
		for (int col = 0; col < (int) a.data.begin()->size(); col++)
		{
			cpy->data[row][col] = a.data[row][col];
		}
	}

	cpy->row = a.row;
	cpy->col = a.col;

	// cout << "CPY ROW/COL: " << cpy->row << "/" << cpy->col << endl;

	return cpy;
}

void mat_copy_data(Matrix_t *a, Matrix_t *b)
{
	a->row = b->row;
	a->col = b->col;
	a->data = b->data;
}

void mat_print(Matrix_t *_a)
{
	for (auto row = _a->data.begin(); row != _a->data.end(); row++)
	{
		for (auto col = row->begin(); col != row->end(); col++)
		{
			cout << *col << ", ";
			cout.flush();
		}
		cout << endl;
	}
}

void mat_print(Matrix &_a)
{
	for (auto row = _a.begin(); row != _a.end(); row++)
	{
		for (auto col = (*row).begin(); col != (*row).end(); col++)
		{
			cout << *col << ", ";
		}
		cout << endl;
	}
}


Matrix_t::Matrix_t(Matrix &_data)
{
	data = _data;
	row = _data.size();
	col = _data.begin()->size();
}

Matrix_t::Matrix_t(int _row, int _col)
{
	_row = _row == 0 ? 1 : _row;
	_col = _col == 0 ? 1 : _col;

	row = _row;
	col = _col;

	data = Matrix(_row, Row(_col));
}

vector<double> *get_column(int _col, Matrix &_data)
{
	Row *ret_vec = new Row();
	ret_vec->reserve(_data.size());

	for (auto row = _data.begin(); row != _data.end(); row++)
	{
		ret_vec->push_back((*row)[_col]);
	}
	return ret_vec;
}

double vec_mult_sum(Row &a, Row &b)
{
	if (a.size() != b.size()) { return 0.0; }

	double total = 0.0;

	for (int index = 0; index < (int) a.size(); index++)
	{
		total += a[index] * b[index];
	}

	return total;
}


void mat_sub_insert(Matrix_t *_src, int _row, int _col, Matrix_t *_dest)
{
	for (int i = _row; i < _row + (int) _src->data.size(); i++)
	{
		for (int j = _col; j < _col + (int) (*(_src->data.begin())).size(); j++)
		{
			_dest->data[i][j] = _src->data[i-_row][j-_col];
 		}
	}
}


int mat_vertical_concat_p(Matrix_t *a, Matrix_t *b)
{
	// Check for size mismatch
	if ((*(a->data.begin())).size() != (*(b->data.begin())).size()) { return 1; }

	Matrix_t *res = new Matrix_t(
		a->data.size() + b->data.size(), 
		(*(a->data.begin())).size());

	mat_sub_insert(a, 0, 0, res);
	mat_sub_insert(b, b->data.size(), 0, res);

	mat_copy_data(b, res);
	free(res);

	return 0;
}



void mat_free(Matrix_t *mat)
{
	if (mat != NULL)
	{
		delete mat;
		mat = NULL;
	}
}





















