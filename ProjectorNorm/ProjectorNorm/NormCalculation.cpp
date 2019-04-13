#include "NormCalculation.h"
#include "Vector.h"
#include "Matrix.h"
#include<cmath>
#include<iostream>

Vector& NormCalculation::getVer(int i)
{
	Vector* res(new Vector(0, n));
	for (int j = n - 1; j >= 0; j--)
	{
		res->setValue(i % 2, j);
		i /= 2;
	}
	return *res;
}

NormCalculation::NormCalculation()
{
}

NormCalculation::NormCalculation(int n, double h)
{
	this->n = n;
	countVer = pow(2, n);
	ver = new Vector[countVer];
	for (int i = 0; i < countVer; i++)
		ver[i] = getVer(i);
	this->h = h;
}

double NormCalculation::LambdaFunction(Vector x, Matrix &inv, int j)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += inv[i][j] * x[i];
	sum += inv[n][j];
	return sum;
}

double NormCalculation::getNorm(Matrix &points)
{
	Matrix inv = points.Inverse();
	
	double max = 0;
	for (int i = 0; i < countVer; i++)
	{
		double sum = 0;
		for (int j = 0; j < n + 1; j++)
		{
			sum += abs(LambdaFunction(ver[i], inv, j));
		}
			
		if (sum > max)
			max = sum;
	}
	return max;
}

NormCalculation::~NormCalculation()
{
	delete[] ver;
}
