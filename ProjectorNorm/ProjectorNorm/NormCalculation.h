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
	NormCalculation();
	NormCalculation(int n, double h);
	Vector& getVer(int i);
	double LambdaFunction(Vector x, Matrix &inv, int j);
	double getNorm(Matrix &points);
	~NormCalculation();
};

