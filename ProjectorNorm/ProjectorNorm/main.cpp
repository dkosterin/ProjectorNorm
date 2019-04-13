#include<iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace std;

int main() {
	Vector v(1, 2);
	cout << v << endl;
	Vector v1(5);
	for (int i = 0; i < 5; i++)
		v1.setValue((i + 1) * (i + 1), i);
	cout << v1 << endl;
	cout << v1[2] << endl;
	cout << (v1 == v) << endl;
	Matrix m(3);
	m.setValue(0, 0, 0);
	m.setValue(1, 1, 0);
	m.setValue(2, 2, 0);
	m.setValue(6, 0, 1);
	m.setValue(2, 1, 1);
	m.setValue(3, 2, 1);
	m.setValue(4, 2, 0);
	m.setValue(6, 2, 1);
	m.setValue(5, 2, 2);
	cout << m << endl;
	cout << m.Determinant() << endl;
	Matrix inv = m.Inverse();
	//m.diag();
	cout << m << endl;
	cout << inv << endl;
	system("pause");
	return 0;
}