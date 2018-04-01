#include "Matrices.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


//Constructors
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


//Destructor
Matrix::~Matrix()
{
	/*cout << "destructor" << endl;*/
	for (int i = 0; i < (this->rows); ++i)
	{
		delete[] (this->data)[i];

	}
	delete[] (this->data);


}


//Space allocation
void Matrix::allocSpace()
{
	this->data = new double*[rows];
	for (int i = 0; i < rows; ++i)
	{
			
		(this->data)[i] = new double[cols];

	}
}


//Overloading operators
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


Matrix operator+(const Matrix& first_matrix, const Matrix& second_matrix)
{
	Matrix tmp(first_matrix);
	return(tmp += second_matrix);
}


Matrix operator-(const Matrix& first_matrix, const Matrix& second_matrix)
{
	Matrix tmp(first_matrix);
	return (tmp -= second_matrix);
}


Matrix operator*(const Matrix& first_matrix, const Matrix& second_matrix)
{
	Matrix tmp(first_matrix);
	return (tmp *= second_matrix);
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


Matrix operator*(const Matrix& matrix, const double numeric)
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


//Matrix functions
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


Matrix& Matrix::pow_elem(int degree)
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
		{
			(this->data)[i][j] = pow((this->data)[i][j], degree);
		}
	}
	return *this;
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


//Net functions
Matrix forward_prop(const Matrix& first_matrix, const Matrix& weights, double bias)
{
	return ((first_matrix*weights)+bias);
}


double net_loss(Matrix& first_matrix, Matrix& weights, Matrix& true_labels, double& bias)
{
	Matrix labels = forward_prop(first_matrix, weights, bias);
	double loss = (1.0 / (2 * labels.rows))*(((labels - true_labels).pow_elem(2)).sum());
	return abs(loss);
}


void back_prop(Matrix& first_matrix, Matrix& weights,Matrix& true_labels,double learning_rate,double& bias)
{
	cout << bias << endl;
	Matrix labels = forward_prop(first_matrix, weights,bias);
	Matrix tmp = first_matrix;
	Matrix grad = ((tmp.transpose())*(labels - true_labels)) * (1.0 / first_matrix.rows) ;
	double grad_bias = (1.0 / first_matrix.rows)*((labels - true_labels).sum());
	weights -= grad*learning_rate;
	bias -= grad_bias*learning_rate;
}


void net_train(Matrix& first_matrix, Matrix& weights, Matrix& true_labels, double learning_rate,double& bias,int num_iter)
{
	for (int i = 0; i < num_iter; ++i)
	{
		cout << "Iter number: " << i << endl;
		cout << "Current loss: " << net_loss(first_matrix, weights, true_labels,bias) << endl;
		back_prop(first_matrix, weights, true_labels, learning_rate,bias);
	}

}

//Matrix max(const Matrix& matrix)
//{
//	
//	for (int i = 0; i < matrix.rows; ++i)
//	{
//		for (int j = 0; j < matrix.cols; ++j)
//		{
//			if (tmp[i] < matrix.data[i][j])
//			{
//				tmp[i] = matrix.data[i][j];
// 			}
//		}
//	}
//	return tmp;
//}
//
//ostream& operator<<(ostream& out, double* vec)
//{
//	for 
//}

//Matrix softmax(const Matrix& matrix)
//{
//
//}





