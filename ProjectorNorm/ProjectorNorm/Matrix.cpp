#include "Matrix.h"
#include "Vector.h"
#include<iostream>

Matrix::Matrix()
{
}

Matrix::Matrix(int n)
{
	this->n = n;
	this->matrix = new Vector[n];
	for (int i = 0; i < n; i++)
	{
		this->matrix[i] = Vector(0, n);
	}
}

Matrix::Matrix(double a, int n)
{
	this->n = n;
	matrix = new Vector[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = Vector(0, n);
		matrix[i].setValue(a, i);
	}
}

Matrix::Matrix(Vector* vectors, int n)
{
	this->n = n;
	this->matrix = new Vector[n];
	for (int i = 0; i < n; i++)
		this->matrix[i] = vectors[i];
}

void Matrix::setValue(double a, int i, int j)
{
	matrix[i].setValue(a, j);
}

Matrix& Matrix::operator=(const Matrix &m)
{
	n = m.n;
	matrix = new Vector[n];
	for (int i = 0; i < n; i++)
		matrix[i] = m.matrix[i];
	return *this;
}

Vector Matrix::operator[](int i)
{
	Vector res = Vector(matrix[i]);
	return res;
}

double Matrix::Determinant()
{
	Matrix copy(matrix, n);
	double det = 1;
	for (int j = 0; j < n; j++)
	{
		int k = -1;
		for (int i = j; i < n; i++)
			if (matrix[i][j] != 0)
			{
				k = i;
				break;
			}
		if (k == -1)
			return 0;
		if (k != j)
			det = -det;
		Vector tmp = matrix[j];
		matrix[j] = matrix[k];
		matrix[k] = tmp;
		for (int i = j + 1; i < n; i++)
		{
			double a = matrix[i][j];
			for (int l = j; l < n; l++)
				setValue(matrix[i][l] - a * matrix[j][l] / matrix[j][j], i, l);
		}
	}
	for (int i = 0; i < n; i++)
		det *= matrix[i][i];
	for (int i = 0; i < n; i++)
		matrix[i] = copy.matrix[i];
	return det;
}

Matrix& Matrix::Inverse()
{
	Matrix copy(matrix, n);
	Matrix* res(new Matrix(1, n));
	for (int j = 0; j < n; j++)
	{
		int k;
		for (int i = j; i < n; i++)
			if (matrix[i][j] != 0)
			{
				k = i;
				break;
			}
		Vector tmp = matrix[j];
		matrix[j] = matrix[k];
		matrix[k] = tmp;
		tmp = res->matrix[j];
		res->matrix[j] = res->matrix[k];
		res->matrix[k] = tmp;
		double p = matrix[j][j];
		for (int l = 0; l < n; l++)
		{
			setValue(matrix[j][l] / p, j, l);
			res->setValue(res->matrix[j][l] / p, j, l);
		}
			
		for (int i = 0; i < n; i++)
		{
			double a = matrix[i][j];
			if (i != j)
			{
				for (int l = 0; l < n; l++)
				{
					setValue(matrix[i][l] - a * matrix[j][l], i, l);
					res->setValue(res->matrix[i][l] - a * res->matrix[j][l], i, l);
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
		matrix[i] = copy.matrix[i];
	return *res;
}

std::ostream& operator<< (std::ostream &out, const Matrix &m)
{
	out << "[";
	for (int i = 0; i < m.n; i++)
	{
		out << m.matrix[i];
		if (i < m.n - 1)
			out << "," << std::endl;
	}
	out << "]";
	return out;
}

Matrix::~Matrix()
{
	delete[] matrix;
}
