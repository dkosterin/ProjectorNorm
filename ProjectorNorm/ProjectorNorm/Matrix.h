#pragma once
#include<iostream>
#include "Vector.h"
class Matrix // ����� ������� ����������� n. ������������� ������ ���������� �������
{
private:
	Vector* matrix; // ������ ��������. ���� ������ - ���� ������ �������
	int n; // ����������� �������
public:
	Matrix(); // ����������� �� ���������
	Matrix(int n); // �����������, ������� ������� ������ ������� ����������� n
	Matrix(double a, int n); // �����������, ������� ������� ������� ����������� n. �� ������� ��������� ��� ����� a, ��������� - ����
	Matrix(Vector* vectors, int n); // �����������, ������� ������� ������� ����������� n, � ������� ������� �������� ������� vectors
	void setValue(double a, int i, int j); // ������� ������������� �������� a � i-�� ������ j-��� �������
	Matrix& operator=(const Matrix &m); // �������� ������������
	Vector operator[](int i); // �������� ����������. �������� ����������. �����, ����� ���� ����� ���������� � ��������� �������
	double Determinant(); // �������, ����������� ������������ �������
	Matrix& Inverse(); // �������, ����������� �������� �������
	friend std::ostream& operator<< (std::ostream &out, const Matrix &m); // �������� ������
	~Matrix(); // ����������
};

