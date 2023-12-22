#include "vector3d.h"

Vector3d::Vector3d()
{
	cords[0] = 0;
	cords[1] = 0;
	cords[2] = 0;
	cords[3] = 1;
}
Vector3d::Vector3d(double x, double y, double z, double w)
{
	cords[0] = x;
	cords[1] = y;
	cords[2] = z;
	cords[3] = w;
}
Vector3d::Vector3d(const Vector3d& copy)
{
	cords[0] = copy.x();
	cords[1] = copy.y();
	cords[2] = copy.z();
	cords[3] = copy.w();
}

Vector3d::~Vector3d() {}

double Vector3d::getLength() {
	return sqrt(cords[0] * cords[0] + cords[1] * cords[1] + cords[2] * cords[2]);
}

Vector3d& Vector3d::multyplyByScalar(double s)
{
	cords[0] *= s;
	cords[1] *= s;
	cords[2] *= s;
	return (*this);
}

Vector3d& Vector3d::normalize()
{
	const double len = getLength();
	if (len == 0)
	{
		return (*this);
	}
	cords[0] /= len;
	cords[1] /= len;
	cords[2] /= len;
	return (*this);
}

double& Vector3d::x()
{
	return cords[0];
}
double& Vector3d::y()
{
	return cords[1];
}
double& Vector3d::z()
{
	return cords[2];
}
double& Vector3d::w()
{
	return cords[3];
}

double Vector3d::x() const
{
	return cords[0];
}
double Vector3d::y() const
{
	return cords[1];
}
double Vector3d::z() const
{
	return cords[2];
}
double Vector3d::w() const
{
	return cords[3];
}

Vector3d add(const Vector3d& v1, const Vector3d& v2)
{
	Vector3d vec(v1.cords[0] + v2.cords[0], v1.cords[1] + v2.cords[1], v1.cords[2] + v2.cords[2]);
	return vec;
}
Vector3d substract(const Vector3d& v1, const Vector3d& v2)
{
	Vector3d vec(v1.cords[0] - v2.cords[0], v1.cords[1] - v2.cords[1], v1.cords[2] - v2.cords[2]);
	return vec;
}
double scalarMult(const Vector3d& v1, const Vector3d& v2)
{
	return v1.cords[0] * v2.cords[0] + v1.cords[1] * v2.cords[1] + v1.cords[2] * v2.cords[2];
}
Vector3d crossProduct(const Vector3d& v1, const Vector3d& v2)
{
	Vector3d vec(v1.cords[1] * v2.cords[2] - v1.cords[2] * v2.cords[1],
		v1.cords[2] * v2.cords[0] - v1.cords[0] * v2.cords[2],
		v1.cords[0] * v2.cords[1] - v1.cords[1] * v2.cords[0]);
	return vec;
}
Vector3d multiplyMatrix(const Matrix& m, const Vector3d& v)
{
	Vector3d vec;
	for (int i = 0; i < 4; i++)
	{
		vec.cords[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			vec.cords[i] += m.m[i][j] * v.cords[j];
		}
	}
	return vec;
}
