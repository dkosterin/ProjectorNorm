#pragma once
#include<iostream>
class Vector // ����� ������� (�����) ����������� n
{
private:
	double* vector; // ������, � ������� ����� ��������� �������� �������
	int n; // ����������� �������
public:
	Vector(); // ����������� �� ���������, ��� �� ����������, �� �� ������ ����
	Vector(int n); // �����������, ������� ������� ������ ������ ����������� n
	Vector(double a, int n); // �����������, ������� ������� ������ ����������� n, ��� �������� �������� ����� a
	Vector(const Vector &v); // ����������� �����������
	void setValue(double a, int i); // �������, ������� � i-�� ������� ������� ������ �������� ������ a
	Vector& operator=(const Vector &v); // �������� ������������
	bool operator==(const Vector &v); // �������� ��������� ���� ��������
	double operator[](int i); // �������� ����������. �����, ����� ���� ����� ���������� � ��������� �������
	friend std::ostream& operator<< (std::ostream &out, const Vector &v); // �������� ������
	~Vector(); // ����������
};

