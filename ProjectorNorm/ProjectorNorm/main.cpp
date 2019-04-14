#include<iostream>
#include "Vector.h"
#include "Matrix.h"
#include "NormCalculation.h"

using namespace std;

int main() {
	NormCalculation p(2, 0.1);
	Vector* points = new Vector[3];
	Vector p1(0, 3);
	p1.setValue(1, 2);
	Vector p2(1, 3);
	p2.setValue(0, 1);
	Vector p3(1, 3);
	p3.setValue(0.5, 0);

	points[0] = p1;
	points[1] = p2;
	points[2] = p3;

	for (int i = 0; i < 20; i++)
		cout << p.getPoint(i) << endl;

	Matrix m(points, 3);
	cout << m << endl;
	double res = p.getNorm(m);
	cout << res << endl;
	Matrix r(3);
	double min = p.findMinNorm(r);
	cout << min << endl;
	cout << r << endl;
	system("pause");
	return 0;
}