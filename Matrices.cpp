#include "Matrices.h"
using namespace std;
#include <iostream>

using namespace std;
Matrix::Matrix()
{
	rows = 1;
	cols = 1;
	allocSpace();
	data[0][0] = 0;
}

Matrix::Matrix(double** _data, int _rows, int _cols)
{
	rows = _rows;
	cols = _cols;
	allocSpace();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			data[i][j] = _data[i][j];
		}
	}

}

Matrix::Matrix(int _rows, int _cols)
{
	rows = _rows;
	cols = _cols;
	allocSpace();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			data[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix& matrix)
{
	rows = matrix.rows;
	cols = matrix.cols;
	allocSpace();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			data[i][j] = (matrix.data)[i][j];
		}
	}

}

Matrix::~Matrix()
{
	cout << "destructor" << endl;
	for (int i = 0; i < rows; ++i)
	{
		delete[] data[i];

	}
	delete[] data;


}

void Matrix::allocSpace()
{
	data = new double*[rows];
	for (int i = 0; i < rows; ++i)
	{
			
		data[i] = new double[cols];

	}
}

ostream & operator<<(ostream & out, const Matrix& matrix)
{
	for (int i = 0; i < matrix.rows; ++i)
	{
		for (int j = 0; j < matrix.cols; ++j)
		{
			out << matrix.data[i][j] << "\t";
		}
		out << endl;
	}
	return out;
}

Matrix operator+(const Matrix& first_matrix, const Matrix& second_matrix)
{
	Matrix tmp = first_matrix;
	return(tmp += second_matrix);
}

Matrix operator*(const Matrix& first_matrix, const Matrix& second_matrix)
{
	Matrix tmp = first_matrix;
	return (tmp*=second_matrix);
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
	if (this == &matrix)
	{
		
		return *this;
	
	}

	if ((rows != matrix.rows) || (cols != matrix.cols))
	{
		for (int i = 0; i < rows; ++i)
		{
			delete[] data[i];
		}
		delete[] data;

		rows = matrix.rows;
		cols = matrix.cols;
		allocSpace();

	}

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			data[i][j] = matrix.data[i][j];
		}
	}
	return *this;
}

Matrix & Matrix::operator*=(const Matrix& matrix)
{	
	cols = matrix.cols;
	Matrix tmp(rows, cols);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			for (int k = 0; k < matrix.rows; ++k)
			{
				tmp.data[i][j] += data[i][k] * matrix.data[k][j];
			}
		}
	}
	*this = tmp;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			data[i][j] += matrix.data[i][j];
		}
	}
	return *this;
}


