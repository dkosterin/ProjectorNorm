#pragma once
#include "Vector.h"
#include "Matrix.h"
class NormCalculation // ����� ������� ����� ���������
{
private:
	Vector* ver; // ������ ������ ��������� [0,1]^n (�������, ��� � �.�.)
	int* a; // � ���� ������� �������� ����� �� 0 �� countPoints - 1 � ������� �����������
	int n, countVer, countPoints; // n - �����������. countVer - ���������� ������. countPoints - ���������� ���� ����� �� �������� [0,1]^n
	double h; // ��� �� ������� [0,1]
	Vector& getVer(int i); // �������, ������� ������� ������� �� [0,1]^n
	double LambdaFunction(Vector x, Matrix &inv, int j); // ������� Lambda
	bool nextSet(); // �������, ������������ ��������� C �� countPoints ��������� �� n + 1
	Vector getPoint(int i); // �������, ������� ���������� ����� �� [0,1]^n
public:
	NormCalculation(); // ����������� �� ���������
	NormCalculation(int n, double h); // �����������, ������� ����� �������������� ������
	double getNorm(Matrix &points); // �������, ������� ��������� ����� ��� �����-�� ������� �������� �����
	double findMinNorm(Vector* res); // �������, ������� ������� ����������� �����
	~NormCalculation(); // ����������
};

