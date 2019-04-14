#include "NormCalculation.h"
#include "Vector.h"
#include "Matrix.h"
#include<cmath>
#include<iostream>

using namespace std;

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
	countPoints = (int)(1 / h) + 1;
	countPoints = pow(countPoints, n);
	a = new int[countPoints];
	for (int i = 0; i < countPoints; i++)
		a[i] = i;
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

double NormCalculation::findMinNorm(Matrix &res)
{
	Vector* points = new Vector[n + 1];
	double min = 10000000;
	do
	{
		for (int i = 0; i < n + 1; i++)
		{
			points[i] = getPoint(a[i]);
			// TODO: ѕроверка точки на принадлежность границе
			//cout << i << " " << points[i] << endl;
		}
		Matrix m(points, n + 1);
		double det = m.Determinant();
		if (abs(det) < 0.000001)
			continue;
		double p = getNorm(m);
		if (p < min)
		{
			res = m;
			min = p;
		}
	} while (nextSet());
	return min;
}

Vector NormCalculation::getPoint(int i)
{
	int count = 0;
	double c = h;
	while ((int)c == 0)
	{
		c *= 10;
		count++;
	}
	count = pow(10, count);

	Vector res(0, n + 1);
	int k = n - 1;
	for (int j = 0; j < i; j++)
	{
		if (res[k] == 1)
		{
			while (k >= 0 && res[k] == 1)
			{
				res.setValue(0, k);
				k--;
			}
			res.setValue(round((res[k] + h) * count) / count, k);
			k = n - 1;
		}
		else res.setValue(round((res[k] + h) * count) / count, k);
	}
	res.setValue(1, n);
	return res;
}

bool NormCalculation::nextSet()
{
	int k = n + 1;
	for (int i = k - 1; i >= 0; --i)
		if (a[i] < countPoints - k + i)
		{
			++a[i];
			for (int j = i + 1; j < k; ++j)
				a[j] = a[j - 1] + 1;
			return true;
		}
	return false;
}


NormCalculation::~NormCalculation()
{
	delete[] ver;
}
