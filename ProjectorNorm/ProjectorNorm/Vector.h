#pragma once
#include<iostream>
class Vector
{
private:
	double* vector;
	int n;
public:
	Vector();
	Vector(double a, int n);
	Vector(double* vector, int n);
	bool operator==(const Vector &v);
	double operator[](int i);
	friend std::ostream& operator<< (std::ostream &out, const Vector &v);
	~Vector();
};

