#include<iostream>
#include "Vector.h"

using namespace std;

int main() {
	Vector v(1, 2);
	cout << v << endl;
	double* vector = new double[5];
	for (int i = 0; i < 5; i++)
		vector[i] = (i + 1) * (i + 1);
	Vector v1(vector, 5);
	cout << v1 << endl;
	cout << v1[2] << endl;
	cout << (v1 == v) << endl;
	Vector v2(vector, 5);
	cout << (v1 == v2) << endl;
	delete[] vector;
	system("pause");
	return 0;
}