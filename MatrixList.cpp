#include "matrixlist.h"
#include <iostream>

Matrix multiply(const Matrix& a, const Matrix& b)
{
	Matrix mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				mat.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return mat;
}

Matrix getTranslation(double dx, double dy, double dz)
{
	double m[4][4] = { {1, 0, 0, dx},
						{0, 1, 0, dy},
						{0, 0, 1, dz},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getScale(double sx, double sy, double sz)
{
	double m[4][4] = { {sx, 0, 0, 0},
						{0, sy, 0, 0},
						{0, 0, sz, 0},
						{0, 0, 0,  1} };
	Matrix mat(m);
	return mat;
}

Matrix getRotationX(double angle)
{
	const double rad = M_PI / 180.0 * angle;
	double m[4][4] = { {1, 0, 0, 0},
						{0, cos(rad), -sin(rad), 0},
						{0, sin(rad), cos(rad), 0},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getRotationY(double angle)
{
	const double rad = M_PI / 180.0 * angle;
	double m[4][4] = { {cos(rad), 0, sin(rad), 0},
						{0, 1, 0, 0},
						{-sin(rad), 0, cos(rad), 0},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getRotationZ(double angle)
{
	const double rad = M_PI / 180.0 * angle;
	double m[4][4] = { {cos(rad), -sin(rad), 0, 0},
						{sin(rad), cos(rad), 0, 0},
						{0, 0, 1, 0},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getCabinet() {
	double m[4][4] = { {1, 0, -sqrt(2.0) / 4.0, 0},      {0, 1, -sqrt(2.0) / 4.0, 0},
		 {0, 0, sqrt(2.0) / 4.0, 0},      {0, 0, 0, 1} };
	Matrix mat(m); return mat;
}

Matrix getShadowX(const Vector3d& l)
{
	double m[4][4] = { {0, 0, 0, 0},
						{-l.y()/l.x() , 1, 0, 0},
						{-l.z()/l.x(), 0, 1, 0},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getShadowY(const Vector3d& l)
{
	double m[4][4] = { {1, -l.x()/l.y(), 0, 0},
						{0, 0, 0, 0},
						{0, -l.z()/l.y(), 1, 0},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Matrix getShadowZ(const Vector3d& l)
{
	double m[4][4] = {  {1, 0, -l.x()/l.z(), 0},
						{0, 1, -l.y()/l.z(), 0},
						{0, 0, 0, 0},
						{0, 0, 0, 1} };
	Matrix mat(m);
	return mat;
}

Vector3d checkWallsCollision(Vector3d oWalls, const Vector3d& p)
{
	Vector3d res;
	if ((res.x() = p.x() - oWalls.x()) >= 0)
	{
		res.x() = 0;
	}
	if ((res.y() = p.y() - oWalls.y()) >= 0)
	{
		res.y() = 0;
	}
	if ((res.z() = p.z() - oWalls.z()) >= 0)
	{
		res.z() = 0;
	}
	return res; 
}