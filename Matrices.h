#include <iostream>
#include <vector>
#include <map>
#include <sstream>

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
	
	
	/*friend double* max(const Matrix&);*/


};

class Module
{
public:
	int submodel_num;
	Module() { submodel_num = 0; }
	~Module(){}
	string module_name = "Module";
	//Module* Ptr;
	virtual Matrix forward(Matrix input) { return input; }
	vector<pair<string,Module>> modules;
	map<string, Matrix> parametres;
	map<string, Matrix> grads;

	void add_module(string module_name,Module module)
	{
		modules.push_back(pair<string, Module>(module_name,module));
	}
	
	void add(Module module)
	{
		string module_name = to_string(submodel_num);
		add_module(module_name, module);
		submodel_num++;
	}
};


class Sequential : public Module
{
public:
	Sequential() { module_name = "Sequential"; }
	~Sequential(){}
	Matrix forward(Matrix input)
	{
		Matrix result = input;
		for (auto submodules : modules)
		{
			result = submodules.second.forward(result);
			
		}
		return result;
	}

};

class Linear : public Module
{
public:
	int input_size;
	int output_size;
	double bias;
	Linear(int _input_size, int _output_size, double _bias)
	{
		input_size = _input_size;
		output_size = _output_size;
		bias = _bias;
		parametres["weight"] = Matrix(input_size, output_size);
	}
	~Linear() {}

	Matrix forward(Matrix input)
	{
		Matrix result = input;
		result = input*parametres["weight"] + bias;
		return result;
	}
};
