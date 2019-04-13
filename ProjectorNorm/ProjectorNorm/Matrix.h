#pragma once
#include<iostream>
#include "Vector.h"
class Matrix
{
private:
	Vector* matrix;
	int n;
public:
	Matrix();
	Matrix(int n);
	Matrix(double a, int n);
	Matrix(Vector* vectors, int n);
	void setValue(double a, int i, int j);
	Matrix& operator=(const Matrix &m);
	Vector operator[](int i);
	double Determinant();
	Matrix& Inverse();
	//void diag();
	friend std::ostream& operator<< (std::ostream &out, const Matrix &m);
	~Matrix();
};

