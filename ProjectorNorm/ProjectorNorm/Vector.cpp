#include "Vector.h"
#include<iostream>


Vector::Vector()
{
}

Vector::Vector(double a, int n)
{
	this->n = n;
	this->vector = new double[n];
	for (int i = 0; i < n; i++) 
	{
		this->vector[i] = a;
	}
}

Vector::Vector(double* vector, int n)
{
	this->n = n;
	this->vector = new double[n];
	for (int i = 0; i < n; i++)
	{
		this->vector[i] = vector[i];
	}
}

bool Vector::operator==(const Vector &v)
{
	if (this->n != v.n)
		return false;
	for (int i = 0; i < n; i++)
		if (this->vector[i] != v.vector[i])
			return false;
	return true;
}

double Vector::operator[](int i)
{
	return this->vector[i];
}

std::ostream& operator<< (std::ostream &out, const Vector &v)
{
	out << "[";
	for (int i = 0; i < v.n; i++)
	{
		out << v.vector[i];
		if (i < v.n - 1)
			out << ", ";
	}
	out << "]";
	return out;
}

Vector::~Vector()
{
	delete[] vector;
}
