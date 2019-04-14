#include<iostream>
#include<clocale>
#include "Vector.h"
#include "Matrix.h"
#include "NormCalculation.h"

using namespace std;

void PrintResult(Vector* points, double p, int n, double h)
{
	cout << "Минимальная норма проектора при n = " << n << "h = " << h << ":" << endl;
	cout << "P = " << p << " в узлах" << endl;
	for (int i = 0; i < n + 1; i++)
		cout << points[i] << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	double h;
	cout << "Введите размерность n ";
	cin >> n;
	cout << "Введите шаг h ";
	cin >> h;
	
	NormCalculation calc(n, h);
	Vector* minPoints = new Vector[n + 1];
	for (int i = 0; i < n + 1; i++)
		minPoints[i] = Vector(0, n);
	double minNorm = calc.findMinNorm(minPoints);
	PrintResult(minPoints, minNorm, n, h);
	system("pause");
	return 0;
}