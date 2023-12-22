#include "matrix.h"

Matrix::Matrix() {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = 0.0;
		}
	}
}
Matrix::Matrix(double m[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m[i][j] = m[i][j];
		}
	}
}
Matrix::Matrix(const Matrix& copy)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m[i][j] = copy.m[i][j];
		}
	}
}

void Matrix::set_ones()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				m[i][j] = 1.0;
			}
			else
			{
				m[i][j] = 0.0;
			}
		}
	}
}

Matrix::~Matrix() {}