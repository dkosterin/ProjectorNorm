#pragma once
#include "Vector.h"
#include "Matrix.h"
class NormCalculation
{
private:
	Vector * ver;
	int n, countVer;
	double h;
public:
	int* a;
	int countPoints;
	NormCalculation();
	NormCalculation(int n, double h);
	Vector& getVer(int i);
	double LambdaFunction(Vector x, Matrix &inv, int j);
	double getNorm(Matrix &points);
	double findMinNorm(Matrix &res);
	Vector getPoint(int i);
	bool nextSet();
	~NormCalculation();
};

