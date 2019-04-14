#pragma once
#include "Vector.h"
#include "Matrix.h"
class NormCalculation // Здесь находим норму проектора
{
private:
	Vector* ver; // Массив вершин множества [0,1]^n (квадрат, куб и т.д.)
	int* a; // В этом массиве хранятся числа от 0 до countPoints - 1 в порядке возрастания
	int n, countVer, countPoints; // n - размерность. countVer - количество вершин. countPoints - количество всех точек из множется [0,1]^n
	double h; // Шаг по отрезку [0,1]
	Vector& getVer(int i); // Функция, которая находит вершину из [0,1]^n
	double LambdaFunction(Vector x, Matrix &inv, int j); // Функция Lambda
	bool nextSet(); // Функция, генерирующая сочетание C из countPoints элементов по n + 1
	Vector getPoint(int i); // Функция, которая генерирует точку из [0,1]^n
public:
	NormCalculation(); // Конструктор по умолчанию
	NormCalculation(int n, double h); // Конструктор, который будет использоваться всегда
	double getNorm(Matrix &points); // Функция, которая вычисляет норму для каких-то заранее заданных точек
	double findMinNorm(Vector* res); // Функция, которая находит минимальную норму
	~NormCalculation(); // Деструктор
};

