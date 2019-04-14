#include "Matrix.h"
#include "Vector.h"
#include<iostream>

// Здесь тоже все просто, за исключением определителя и обратной матрицы. О них ниже.
Matrix::Matrix()
{
}

Matrix::Matrix(int n)
{
	this->n = n;
	this->matrix = new Vector[n];
	for (int i = 0; i < n; i++)
	{
		this->matrix[i] = Vector(0, n);
	}
}

Matrix::Matrix(double a, int n)
{
	this->n = n;
	matrix = new Vector[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = Vector(0, n);
		matrix[i].setValue(a, i);
	}
}

Matrix::Matrix(Vector* vectors, int n)
{
	this->n = n;
	this->matrix = new Vector[n];
	for (int i = 0; i < n; i++)
		this->matrix[i] = vectors[i];
}

void Matrix::setValue(double a, int i, int j)
{
	matrix[i].setValue(a, j);
}

Matrix& Matrix::operator=(const Matrix &m)
{
	n = m.n;
	matrix = new Vector[n];
	for (int i = 0; i < n; i++)
		matrix[i] = m.matrix[i];
	return *this;
}

Vector Matrix::operator[](int i)
{
	Vector res = Vector(matrix[i]);
	return res;
}

// Тут вычисляем опеределитель
double Matrix::Determinant()
{
	// В дальнейшем будем проводить много махинаций со строками и элементами исходной матрицы,
	// Поэтому заранее делаем копию исходной матрицы.
	Matrix copy(matrix, n);
	// В переменную det будем считать определитель
	double det = 1;
	// Все, что происходит в цикле ниже, является методом Гаусса. Там делаем переносы строк, а так же складываем их и вычитаем
	// Идем по всем столбцам
	for (int j = 0; j < n; j++)
	{
		// Сначала ищется опорный элемент. Это просто первый попавшийся ненулевой элемент в этом столбце.
		int k = -1;
		for (int i = j; i < n; i++)
			if (matrix[i][j] != 0)
			{
				k = i;
				break;
			}
		// Если получилось так, что опорного элемента нет, то определитель равен нулю.
		if (k == -1)
			return 0;
		// Когда находим опорный элемент, меняем строчку, в которой его нашли, с текущей.
		// Когда меняем в матрице строки, определитель меняет знак.
		if (k != j)
			det = -det;
		Vector tmp = matrix[j];
		matrix[j] = matrix[k];
		matrix[k] = tmp;
		// Тут зануляем все элементы под опорным элементом.
		for (int i = j + 1; i < n; i++)
		{
			double a = matrix[i][j];
			for (int l = j; l < n; l++)
				setValue(matrix[i][l] - a * matrix[j][l] / matrix[j][j], i, l); // Формула внутри функции как раз зануляет все элементы под опорным.
		}
	}
	// В конце получаем верхнюю диагональную матрицу (под главной диагонали все элементы - нули).
	// Ее определитель равен произведению элементов на главной диагонали.
	for (int i = 0; i < n; i++)
		det *= matrix[i][i];
	// В конце возвращаем матрице исходный вид.
	for (int i = 0; i < n; i++)
		matrix[i] = copy.matrix[i];
	return det;
}

// Здесь находим обратную матрицу.
// По сути тут тот же самый метод Гаусса. Только здесь зануляем еще и элементы над главной диагональю.
Matrix& Matrix::Inverse()
{
	Matrix copy(matrix, n);
	Matrix* res(new Matrix(1, n)); // В этой матрице по итогу будет находиться обратная. Изначально это единичная матрица. 
	// Методом Гаусса единичную матрицу можно превратить в обратную.
	for (int j = 0; j < n; j++)
	{
		int k;
		for (int i = j; i < n; i++)
			if (matrix[i][j] != 0)
			{
				k = i;
				break;
			}
		Vector tmp = matrix[j];
		matrix[j] = matrix[k];
		matrix[k] = tmp;
		tmp = res->matrix[j];
		res->matrix[j] = res->matrix[k];
		res->matrix[k] = tmp;
		double p = matrix[j][j];
		for (int l = 0; l < n; l++)
		{
			setValue(matrix[j][l] / p, j, l);
			res->setValue(res->matrix[j][l] / p, j, l);
		}
			
		for (int i = 0; i < n; i++)
		{
			double a = matrix[i][j];
			if (i != j)
			{
				for (int l = 0; l < n; l++)
				{
					setValue(matrix[i][l] - a * matrix[j][l], i, l);
					res->setValue(res->matrix[i][l] - a * res->matrix[j][l], i, l);
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
		matrix[i] = copy.matrix[i];
	return *res;
}

std::ostream& operator<< (std::ostream &out, const Matrix &m)
{
	out << "[";
	for (int i = 0; i < m.n; i++)
	{
		out << m.matrix[i];
		if (i < m.n - 1)
			out << "," << std::endl;
	}
	out << "]";
	return out;
}

Matrix::~Matrix()
{
	delete[] matrix;
}
