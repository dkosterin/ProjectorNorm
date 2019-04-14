#pragma once
#include "Vector.h"
#include "Matrix.h"
class NormCalculation
{
private:
	Vector * ver;
	int* a;
	int n, countVer, countPoints;
	double h;
public:
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

