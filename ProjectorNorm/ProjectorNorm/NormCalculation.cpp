#include "NormCalculation.h"
#include "Vector.h"
#include "Matrix.h"
#include<cmath>

// Здесь находим i-ую вершину нашего множества.
// В случае квадрата вершины: (0,0); (0,1); (1,0); (1,1).
// По сути просто переводим число i в двоичную систему и получаем координату i-ой вершины.
Vector& NormCalculation::getVer(int i)
{
	Vector* res(new Vector(0, n));
	for (int j = n - 1; j >= 0; j--)
	{
		res->setValue(i % 2, j);
		i /= 2;
	}
	return *res;
}

NormCalculation::NormCalculation()
{
}

NormCalculation::NormCalculation(int n, double h)
{
	this->n = n;
	countVer = pow(2, n); // Количество вершин n-мерного куба равно 2^n.
	// Находим все вершины и запихиваем их в массив вершин.
	ver = new Vector[countVer]; 
	for (int i = 0; i < countVer; i++)
		ver[i] = getVer(i);
	this->h = h;
	// Разбиваем отрезок [0,1] на отрезки длины h. Всего таких отрезков 1 / h, а концов этих отрезков - 1 / h + 1
	countPoints = (int)(1 / h) + 1;
	// Но так как у нас не отрезок [0,1], а его n-ая степень, то возводим это количество в n-ую степень.
	countPoints = pow(countPoints, n);
	a = new int[countPoints];
	// Заполняем массив a числами от 0 до countPoints-1 включительно.
	for (int i = 0; i < countPoints; i++)
		a[i] = i;
}

// Здесь вычисляется j-ая функция лямбда в точке x.
double NormCalculation::LambdaFunction(Vector x, Matrix &inv, int j)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += inv[i][j] * x[i];
	sum += inv[n][j];
	return sum;
}

// Здесь вычисляем норму проектора на заданных узлах, которые лежат в матрице points.
double NormCalculation::getNorm(Matrix &points)
{
	Matrix inv = points.Inverse();
	
	double max = 0;
	for (int i = 0; i < countVer; i++)
	{
		double sum = 0;
		for (int j = 0; j < n + 1; j++)
		{
			sum += abs(LambdaFunction(ver[i], inv, j));
		}
			
		if (sum > max)
			max = sum;
	}
	return max;
}

// Здесь находим минимальную норму.
double NormCalculation::findMinNorm(Vector* res)
{
	Vector* points = new Vector[n + 1];
	double min = 10000000;
	// Перебираем все возможные сочетания чисел от 0 до countPoints-1 включительно по n + 1
	// Например, если countPoints = 4, n = 2, то все сочетания: (0, 1, 2); (0, 1, 3); (0, 2, 3); (1, 2, 3).
	do
	{
		// По полученным сочетаниям находим точки из множества.
		for (int i = 0; i < n + 1; i++)
			points[i] = getPoint(a[i]);
		// Точки делаем столбцами матрицы.
		Matrix m(points, n + 1);
		// Если определитель этой матрицы равен 0, то их рассматривать не нужно, так как не существует обратной.
		double det = m.Determinant();
		// Из-за того, что действительные числа в компьютере считаются так, что 0.1 + 0.1 = 0.200000000000004, 
		// функция подсчета определителя не всегда возвращает 0 там, где это надо, поэтому смотрим, чтобы модуль определителя был очень маленьким.
		if (abs(det) < 0.000001)
			continue;
		// Если определитель получился ненулевым, то вычисляем норму.
		double p = getNorm(m); 
		// Если эта норма меньше той, что сейчас находится в min, то запихиваем в min эту норму.
		if (p < min)
		{
			for (int i = 0; i < n + 1; i++)
				for (int j = 0; j < n; j++)
					res[i].setValue(points[i][j], j);
			min = p;
		}
	} while (nextSet());
	return min;
}

// Здесь ищем точку из множества [0,1]^n по числу i.
// Метод такой: если n = 2, h = 0.5, то
// При i = 0 вернется точка (0, 0)
// При i = 1 вернется точка (0, 0.5)
// При i = 2 вернется точка (0, 1)
// При i = 3 вернется точка (0.5, 0)
// При i = 4 вернется точка (0.5, 0.5)
// При i = 5 вернется точка (0.5, 1)
// И так далее
// При i = countPoints - 1 вернется вектор из всех единиц
Vector NormCalculation::getPoint(int i)
{
	// Считаем количество знаков после запятой у h, так как c++ не умеет округлять до знаков после запятой.
	int count = 0;
	double c = h;
	while ((int)c == 0)
	{
		c *= 10;
		count++;
	}
	count = pow(10, count);

	// В res будет нужная нам точка. Так как точек для нахождения нормы нужно n+1, а размерность векторов всего n,
	// то увеличиваем размерность вектора на 1.
	Vector res(0, n + 1);
	// В цикле тупо по разрядам перебираем все числа от 0 до 1 с шагом h, пока не придем к тому, которое нам нужно.
	int k = n - 1;
	for (int j = 0; j < i; j++)
	{
		if (res[k] == 1)
		{
			while (k >= 0 && res[k] == 1)
			{
				res.setValue(0, k);
				k--;
			}
			res.setValue(round((res[k] + h) * count) / count, k);
			k = n - 1;
		}
		else res.setValue(round((res[k] + h) * count) / count, k);
	}
	// Последний элемент всегда считаем равным 1.
	res.setValue(1, n);
	return res;
}

// Здесь генерируется сочетание чисел от 0 до countPoints - 1
// С каждым вызовом этой функции в массиве a пересчитываются первые n+1 чисел.
// Пока не будут перебраны все возможные сочетания, она будет возвращать true, а когда они закончатся - false.
bool NormCalculation::nextSet()
{
	int k = n + 1;
	for (int i = k - 1; i >= 0; --i)
		if (a[i] < countPoints - k + i)
		{
			++a[i];
			for (int j = i + 1; j < k; ++j)
				a[j] = a[j - 1] + 1;
			return true;
		}
	return false;
}


NormCalculation::~NormCalculation()
{
	delete[] a;
	delete[] ver;
}
