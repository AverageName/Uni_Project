#include <iostream>
using namespace std;


class Matrix
{
private:
	double** data;
	int rows;
	int cols;
public:

	//Constructors
	Matrix();
	Matrix(int rows, int cols);
	Matrix(double** _data,int _rows, int _cols);
	Matrix(const Matrix&);
	//Destructor
	~Matrix();
	//Space allocation
	void allocSpace();
	//Operator overloading
	Matrix& operator=(const Matrix& matrix);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix& matrix);
	Matrix& operator*=(const Matrix&);
	
	
	friend Matrix operator+(const Matrix& first_matrix, const Matrix& second_matrix);
	friend Matrix operator-(const Matrix& first_matrix, const Matrix& second_matrix);
	friend Matrix operator*(const Matrix&, const Matrix&);
	friend Matrix operator+(const Matrix&,double);
	friend Matrix operator*(const Matrix&, const double);
	friend ostream& operator<<(ostream& out, const Matrix& matrix);
	
	//Matrix functions
	Matrix& Matrix::transpose(void);
	Matrix& Matrix::pow_elem(int degree);
	double sum(void);
	
	//Net functions
	friend Matrix forward_prop(const Matrix&, const Matrix&, double);
	friend double net_loss(Matrix& first_matrix, Matrix& weights, Matrix& true_labels, double&);
	friend void back_prop(Matrix& first_matrix, Matrix& weights, Matrix& true_labels,double,double&);
	friend void net_train(Matrix& first_matrix, Matrix& weights, Matrix& true_labels, double learning_rate,double& bias,int num_iter);
	
	



};


