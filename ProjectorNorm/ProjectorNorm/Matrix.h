#pragma once
#include<iostream>
#include "Vector.h"
class Matrix // Класс матрицы размерности n. Рассматриваем только квадратные матрицы
{
private:
	Vector* matrix; // Массив векторов. Один вектор - одна строка матрицы
	int n; // Размерность матрицы
public:
	Matrix(); // Конструктор по умолчанию
	Matrix(int n); // Конструктор, который создает пустую матрицу размерности n
	Matrix(double a, int n); // Конструктор, который создает матрицу размерности n. На главной диагонали все равно a, остальное - нули
	Matrix(Vector* vectors, int n); // Конструктор, который создает матрицу размерности n, в строках которой элементы массива vectors
	void setValue(double a, int i, int j); // Функция устанавливает значение a в i-ую строку j-ого столбца
	Matrix& operator=(const Matrix &m); // Оператор присваивания
	Vector operator[](int i); // Оператор индексации. Оператор индексации. Нужен, чтобы было проще обращаться к элементам матрицы
	double Determinant(); // Функция, вычисляющая определитель матрицы
	Matrix& Inverse(); // Функция, вычисляющая обратную матрицу
	friend std::ostream& operator<< (std::ostream &out, const Matrix &m); // Оператор вывода
	~Matrix(); // Деструктор
};

