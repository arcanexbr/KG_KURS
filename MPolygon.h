#pragma once
#define _USE_MATH_DEFINES
#include "vector.h"
#include "vector3d.h"
#include "matrix.h"

class MPolygon 
{
public:
	MPolygon();
	MPolygon(vector<Vector3d> dots);
	MPolygon(const MPolygon& copy);
	~MPolygon();

	MPolygon& operator= (const MPolygon& copy);
	bool operator == (const MPolygon& second) const;

	void calc_v(); 
	Vector3d get_v() const;

	void calc_n(); 
	Vector3d get_n() const;

	void add_dot(Vector3d dot); 
	void clear(); 
	void set_dots(const vector<Vector3d>& dots); 
	Vector3d dot(int i) const; 

	vector<Vector3d> get_dots() const; 
	int get_len() const; 
	Vector3d get_min() const;

	bool is_onPoly(double x, double y) const;

private:
	vector<Vector3d> dots; 
	int len;
	Vector3d v; 
	Vector3d n; 
	bool definedflag; 
};