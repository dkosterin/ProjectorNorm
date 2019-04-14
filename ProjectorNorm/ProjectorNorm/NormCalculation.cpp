#include "NormCalculation.h"
#include "Vector.h"
#include "Matrix.h"
#include<cmath>

// ����� ������� i-�� ������� ������ ���������.
// � ������ �������� �������: (0,0); (0,1); (1,0); (1,1).
// �� ���� ������ ��������� ����� i � �������� ������� � �������� ���������� i-�� �������.
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
	countVer = pow(2, n); // ���������� ������ n-������� ���� ����� 2^n.
	// ������� ��� ������� � ���������� �� � ������ ������.
	ver = new Vector[countVer]; 
	for (int i = 0; i < countVer; i++)
		ver[i] = getVer(i);
	this->h = h;
	// ��������� ������� [0,1] �� ������� ����� h. ����� ����� �������� 1 / h, � ������ ���� �������� - 1 / h + 1
	countPoints = (int)(1 / h) + 1;
	// �� ��� ��� � ��� �� ������� [0,1], � ��� n-�� �������, �� �������� ��� ���������� � n-�� �������.
	countPoints = pow(countPoints, n);
	a = new int[countPoints];
	// ��������� ������ a ������� �� 0 �� countPoints-1 ������������.
	for (int i = 0; i < countPoints; i++)
		a[i] = i;
}

// ����� ����������� j-�� ������� ������ � ����� x.
double NormCalculation::LambdaFunction(Vector x, Matrix &inv, int j)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += inv[i][j] * x[i];
	sum += inv[n][j];
	return sum;
}

// ����� ��������� ����� ��������� �� �������� �����, ������� ����� � ������� points.
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

// ����� ������� ����������� �����.
double NormCalculation::findMinNorm(Vector* res)
{
	Vector* points = new Vector[n + 1];
	double min = 10000000;
	// ���������� ��� ��������� ��������� ����� �� 0 �� countPoints-1 ������������ �� n + 1
	// ��������, ���� countPoints = 4, n = 2, �� ��� ���������: (0, 1, 2); (0, 1, 3); (0, 2, 3); (1, 2, 3).
	do
	{
		// �� ���������� ���������� ������� ����� �� ���������.
		for (int i = 0; i < n + 1; i++)
			points[i] = getPoint(a[i]);
		// ����� ������ ��������� �������.
		Matrix m(points, n + 1);
		// ���� ������������ ���� ������� ����� 0, �� �� ������������� �� �����, ��� ��� �� ���������� ��������.
		double det = m.Determinant();
		// ��-�� ����, ��� �������������� ����� � ���������� ��������� ���, ��� 0.1 + 0.1 = 0.200000000000004, 
		// ������� �������� ������������ �� ������ ���������� 0 ���, ��� ��� ����, ������� �������, ����� ������ ������������ ��� ����� ���������.
		if (abs(det) < 0.000001)
			continue;
		// ���� ������������ ��������� ���������, �� ��������� �����.
		double p = getNorm(m); 
		// ���� ��� ����� ������ ���, ��� ������ ��������� � min, �� ���������� � min ��� �����.
		if (p < min)
		{
			for (int i = 0; i < n + 1; i++)
				for (int j = 0; j < n; j++)
					res[i].setValue(points[i][j], j);
			min = p;
		}
	} while (nextSet());
	return min;
}

// ����� ���� ����� �� ��������� [0,1]^n �� ����� i.
// ����� �����: ���� n = 2, h = 0.5, ��
// ��� i = 0 �������� ����� (0, 0)
// ��� i = 1 �������� ����� (0, 0.5)
// ��� i = 2 �������� ����� (0, 1)
// ��� i = 3 �������� ����� (0.5, 0)
// ��� i = 4 �������� ����� (0.5, 0.5)
// ��� i = 5 �������� ����� (0.5, 1)
// � ��� �����
// ��� i = countPoints - 1 �������� ������ �� ���� ������
Vector NormCalculation::getPoint(int i)
{
	// ������� ���������� ������ ����� ������� � h, ��� ��� c++ �� ����� ��������� �� ������ ����� �������.
	int count = 0;
	double c = h;
	while ((int)c == 0)
	{
		c *= 10;
		count++;
	}
	count = pow(10, count);

	// � res ����� ������ ��� �����. ��� ��� ����� ��� ���������� ����� ����� n+1, � ����������� �������� ����� n,
	// �� ����������� ����������� ������� �� 1.
	Vector res(0, n + 1);
	// � ����� ���� �� �������� ���������� ��� ����� �� 0 �� 1 � ����� h, ���� �� ������ � ����, ������� ��� �����.
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
	// ��������� ������� ������ ������� ������ 1.
	res.setValue(1, n);
	return res;
}

// ����� ������������ ��������� ����� �� 0 �� countPoints - 1
// � ������ ������� ���� ������� � ������� a ��������������� ������ n+1 �����.
// ���� �� ����� ��������� ��� ��������� ���������, ��� ����� ���������� true, � ����� ��� ���������� - false.
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
	delete[] a;
	delete[] ver;
}
