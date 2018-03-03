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
		kek3[i] = new double[4];
		for (int j = 0; j < 4; ++j)
		{
			kek3[i][j] = i;
		}
	}

	Matrix kek1(kek, 4, 3);
	Matrix kek2(kek3, 3, 4);
	cout << kek1 << endl;
	cout << kek1 << endl;
	cout << (kek2*kek1) << endl;

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
	system("pause");
	return 0;
}
