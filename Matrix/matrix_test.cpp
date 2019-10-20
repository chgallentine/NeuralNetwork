/*
* @Author: Charlie Gallentine
* @Date:   2019-10-11 15:59:15
* @Last Modified by:   Charlie Gallentine
* @Last Modified time: 2019-10-11 16:27:50
*/

#include<assert.h>
#include<iostream>

#include "matrix.h"

using namespace std;

bool check_equal(Matrix &a, Matrix &b);
void test_mat_transpose();


int main(int argc, char **argv)
{

	test_mat_transpose();

	cout 
		<< "===================================\n"
		<< "ALL TESTS PASSED\n"
		<< "===================================\n";
	return 0;
}

void test_mat_transpose()
{
	Matrix_t *test_mat = NULL;
	Matrix_t *result = NULL;
	Matrix expected(0, Row(0));

	// ==========================
	
	test_mat = new Matrix_t(0,0);

	mat_transpose(test_mat, &result);
	mat_print(result); mat_print(expected);
	assert(check_equal(result->data, expected));
	
	delete test_mat; delete result;
	expected.clear();
	// ==========================
	
	test_mat = new Matrix_t(1,3);
	for (int i = 0; i < 3; i++)
	{
		test_mat->data[0][i] = i;
	}

	expected = {{0},{1},{2}};

	mat_transpose(test_mat, &result);
	mat_print(result); mat_print(expected);
	assert(check_equal(result->data, expected));

	delete test_mat; delete result;
	expected.clear();
	// ==========================	
}

bool check_equal(Matrix &a, Matrix &b)
{
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < (*(a.begin())).size(); j++)
		{
			if (a[i][j] != b[i][j])
			{
				return false;
			}
		}
	}
	return true;
}













