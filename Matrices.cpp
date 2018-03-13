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
	/*cout << "destructor" << endl;*/
	for (int i = 0; i < (this->rows); ++i)
	{
		delete[] (this->data)[i];

	}
	delete[] (this->data);


}

void Matrix::allocSpace()
{
	this->data = new double*[rows];
	for (int i = 0; i < rows; ++i)
	{
			
		(this->data)[i] = new double[cols];

	}
}



Matrix & Matrix::operator*=(const Matrix& matrix)
{
	Matrix tmp_2(this->rows, matrix.cols);
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < matrix.cols; ++j)
		{
			for (int k = 0; k < matrix.rows; ++k)
			{
				tmp_2.data[i][j] += (this->data)[i][k] * matrix.data[k][j];
			}
		}
	}
	return (*this = tmp_2);
}


Matrix& Matrix::operator=(const Matrix& matrix)
{
	if (this == &matrix)
	{

		return *this;

	}

	if ((rows != matrix.rows) || (cols != matrix.cols))
	{
		for (int i = 0; i < this->rows; ++i)
		{
			delete[](this->data)[i];
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

Matrix& Matrix::operator+=(const Matrix& matrix)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			(this->data)[i][j] += matrix.data[i][j];
		}
	}
	return *this;
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
	Matrix tmp(first_matrix);
	return(tmp += second_matrix);
}

Matrix operator*(const Matrix& first_matrix, const Matrix& second_matrix)
{
	Matrix tmp(first_matrix);
	return (tmp*=second_matrix);
}

Matrix operator+(const Matrix& matrix, double numeric)
{
	Matrix tmp = matrix;
	for (int i = 0; i < tmp.rows; ++i)
	{
		for (int j = 0; j < tmp.cols; ++j)
		{
			(tmp.data)[i][j] = (tmp.data)[i][j] + numeric;
		}
	}

	return tmp;
}


Matrix & Matrix::operator-=(const Matrix & matrix)
{
	for (int i = 0; i < (this->rows); ++i)
	{
		for (int j = 0; j < (this->cols); ++j)
		{
			(this->data)[i][j] -= matrix.data[i][j];
		}
	}
	return *this;
}

Matrix operator*(const Matrix& matrix,const double numeric)
{
	Matrix tmp = matrix;
	for (int i = 0; i < matrix.rows; ++i)
	{
		for (int j = 0; j < matrix.cols; ++j)
		{
			tmp.data[i][j] *= numeric;
		}
	}
	return tmp;
}

Matrix& Matrix::transpose(void)
{
	Matrix tmp(this->cols, this->rows);
	for (int i = 0; i < this->cols; ++i)
	{
		for (int j = 0; j < this->rows; ++j)
		{
			tmp.data[i][j] = (this->data)[j][i];
		}
	}
	return (*this = tmp);
}



Matrix forward_prop(const Matrix& first_matrix, const Matrix& weights)
{
	return (first_matrix*weights);
}

Matrix back_prop(Matrix& first_matrix, Matrix& weights,Matrix& true_labels,double learning_rate)
{
	Matrix labels = forward_prop(first_matrix, weights);
	Matrix tmp = first_matrix;
	Matrix grad = ((tmp.transpose())*(labels -= true_labels)) * (1.0 / first_matrix.rows) ;
	weights -= grad*learning_rate;
	return weights;
}

double Matrix::sum()
{
	double sum = 0;
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			sum += (this->data)[i][j];
		}
	}
	return sum;
}

double net_loss(Matrix& first_matrix, Matrix& weights, Matrix& true_labels)
{
	Matrix labels = forward_prop(first_matrix, weights);
	double loss = (1.0 / (2 * first_matrix.rows))*(labels -= true_labels).sum();
	return abs(loss);
}

void net_train(Matrix& first_matrix, Matrix& weights, Matrix& true_labels, double learning_rate,int num_iter)
{
	for (int i = 0; i < num_iter; ++i)
	{
		cout << "Iter number: " << i << endl;
		cout << "Current loss: " << net_loss(first_matrix, weights, true_labels) << endl;
		weights = back_prop(first_matrix, weights, true_labels, learning_rate);
	}

}
