#include "Vector.h"
#include<iostream>


// Тут вся реализация очень простая. Описывать не буду. Если что-то непонятное будет, спросишь.
Vector::Vector()
{
}

Vector::Vector(int n)
{
	this->n = n;
	this->vector = new double[n];
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

Vector::Vector(const Vector &v)
{
	n = v.n;
	vector = new double[n];
	for (int i = 0; i < n; i++)
	{
		vector[i] = v.vector[i];
	}
}

void Vector::setValue(double a, int i) 
{
	vector[i] = a;
}

Vector& Vector::operator=(const Vector &v)
{
	n = v.n;
	vector = new double[n];
	for (int i = 0; i < v.n; i++)
		vector[i] = v.vector[i];
	return *this;
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
	return vector[i];
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
