#pragma once
#include<iostream>
class Vector
{
private:
	double* vector;
	int n;
public:
	Vector();
	Vector(int n);
	Vector(double a, int n);
	Vector(const Vector &v);
	void setValue(double a, int i);
	Vector& operator=(const Vector &v);
	bool operator==(const Vector &v);
	double operator[](int i);
	friend std::ostream& operator<< (std::ostream &out, const Vector &v);
	~Vector();
};

