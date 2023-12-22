#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "matrix.h"

class Vector3d
{
public:
	Vector3d();
	Vector3d(double x, double y, double z, double w = 1);
	Vector3d(const Vector3d& copy);
	~Vector3d();

	double getLength();

	Vector3d& multyplyByScalar(double s);
	Vector3d& normalize();

	double& x();
	double& y();
	double& z();
	double& w();

	double x() const;
	double y() const;
	double z() const;
	double w() const;

	friend Vector3d add(const Vector3d& v1, const Vector3d& v2);
	friend Vector3d substract(const Vector3d& v1, const Vector3d& v2); 
	friend double scalarMult(const Vector3d& v1, const Vector3d& v2);
	friend Vector3d crossProduct(const Vector3d& v1, const Vector3d& v2);
	friend Vector3d multiplyMatrix(const Matrix& m, const Vector3d& v); 

private:
	double cords[4];
};

Vector3d add(const Vector3d& v1, const Vector3d& v2);
Vector3d substract(const Vector3d& v1, const Vector3d& v2);
double scalarMult(const Vector3d& v1, const Vector3d& v2);
Vector3d crossProduct(const Vector3d& v1, const Vector3d& v2);
Vector3d multiplyMatrix(const Matrix& m, const Vector3d& v);