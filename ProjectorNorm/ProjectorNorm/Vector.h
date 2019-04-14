#pragma once
#include<iostream>
class Vector // Класс вектора (точки) размерности n
{
private:
	double* vector; // Массив, в котором будут храниться элементы вектора
	int n; // Размерность вектора
public:
	Vector(); // Конструктор по умолчанию, его не используем, но он должен быть
	Vector(int n); // Конструктор, который создает пустой вектор размерности n
	Vector(double a, int n); // Конструктор, который создает вектор размерности n, все элементы которого равны a
	Vector(const Vector &v); // Конструктор копирования
	void setValue(double a, int i); // Функция, которая в i-ую позицию вектора ставит значение равное a
	Vector& operator=(const Vector &v); // Оператор присваивания
	bool operator==(const Vector &v); // Оператор сравнения двух векторов
	double operator[](int i); // Оператор индексации. Нужен, чтобы было проще обращаться к элементам вектора
	friend std::ostream& operator<< (std::ostream &out, const Vector &v); // Оператор вывода
	~Vector(); // Деструктор
};

