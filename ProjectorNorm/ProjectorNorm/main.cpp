#include<iostream>
#include "Vector.h"
#include "Matrix.h"
#include "NormCalculation.h"

using namespace std;

int main() {
	NormCalculation p(2, 0.01);
	Vector* points = new Vector[3];
	Vector p1(1, 3);
	p1.setValue(0, 1);
	Vector p2(1, 3);
	p2.setValue(0, 0);
	Vector p3(0, 3);
	p3.setValue(1, 2);

	points[0] = p1;
	points[1] = p2;
	points[2] = p3;

	Matrix m(points, 3);
	cout << m << endl;
	double res = p.getNorm(m);
	cout << res << endl;
	delete[] points;
	system("pause");
	return 0;
}