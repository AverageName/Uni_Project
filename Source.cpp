#include <iostream>
#include "Matrices.h"
using namespace std;


int main()
{
	double** kek = new double*[4];
	for (int i = 0; i < 4; ++i)
	{
		kek[i] = new double[3];
		for (int j = 0; j < 3; ++j)
		{
			kek[i][j] = i;
		}
	}


	double** kek3 = new double*[3];
	for (int i = 0; i < 3; ++i)
	{
		kek3[i] = new double[1];
		for (int j = 0; j < 1; ++j)
		{
			kek3[i][j] = i;
		}
	}
	double** kek4 = new double*[4];
	for (int i = 0; i < 4; ++i)
	{
		kek4[i] = new double[1];
		for (int j = 0; j < 1; ++j)
		{
			kek4[i][j] = i * 3 + 1;
		}
	}

	Matrix kek1(kek, 4, 3);
	Matrix kek2(kek3, 3, 1);
	Matrix kek5(kek4, 4, 1);

	cout << kek1 << endl;
	cout << kek2 << endl;
	cout << kek5 << endl;
	cout << forward_prop(kek1,kek2) << endl;
	cout << net_loss(kek1, kek2, kek5) << endl;
	net_train(kek1, kek2, kek5, 0.05, 25);

	cout << back_prop(kek1,kek2,kek5,0.1) << endl;

	for (int i = 0; i < 4; ++i)
	{
		delete[] kek[i];
	}
	delete[] kek;

	for (int i = 0; i < 3; ++i)
	{
		delete[] kek3[i];
	}
	delete[] kek3;

	for (int i = 0; i < 4; ++i)
	{
		delete[] kek4[i];
	}
	delete kek4;
	system("pause");
	return 0;
}
