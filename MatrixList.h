#pragma once
#define _USE_MATH_DEFINES
#include "matrix.h"
#include "vector3d.h"

Matrix multiply(const Matrix& a, const Matrix& b); 

Matrix getTranslation(double dx, double dy, double dz); 

Matrix getScale(double sx, double sy, double sz); 

Matrix getRotationX(double angle); 

Matrix getRotationY(double angle); 

Matrix getRotationZ(double angle); 

Matrix getCabinet();

Matrix getShadowX(const Vector3d& l);

Matrix getShadowY(const Vector3d& l); 

Matrix getShadowZ(const Vector3d& l); 

Vector3d checkWallsCollision(Vector3d oWalls, const Vector3d& p);
