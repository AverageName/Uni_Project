#include "Matrices.h"
using namespace std;
#include <iostream>

using namespace std;
Matrix::Matrix()
{
	this->rows = 1;
	this->cols = 1;
	this->allocSpace();
	(this->data)[0][0] = 0;
}

Matrix::Matrix(double** _data, int _rows, int _cols)
{
	this->rows = _rows;
	this->cols = _cols;
	this->allocSpace();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			(this->data)[i][j] = _data[i][j];
		}
	}

}

Matrix::Matrix(int _rows, int _cols)
{
	this->rows = _rows;
	this->cols = _cols;
	this->allocSpace();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			(this->data)[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix& matrix)
{
	this->rows = matrix.rows;
	this->cols = matrix.cols;
	this->allocSpace();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			(this->data)[i][j] = (matrix.data)[i][j];
		}
	}

}

Matrix::~Matrix()
{
	cout << "destructor" << endl;
	for (int i = 0; i < rows; ++i)
	{
		delete[] (this->data)[i];

	}
	delete[] (this->data);


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
			delete[] (this->data)[i];
		}
		delete[] this->data;

		this->rows = matrix.rows;
		this->cols = matrix.cols;
		this->allocSpace();

	}

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			(this->data)[i][j] = matrix.data[i][j];
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


