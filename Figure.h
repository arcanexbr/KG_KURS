#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "mpolygon.h"
#include "matrixlist.h"

class Figure
{
public:
	Figure();
	Figure(vector<Vector3d> d, vector<vector<int>> r);
	Figure(const Figure& copy);
	~Figure();

	void copy_dots(const Figure& copy); 

	Figure& operator= (const Figure& copy);

	vector<Vector3d> getDots() const; 
	vector<vector<int>> getRoads() const; 

	void add_dot(Vector3d dot); 
	void add_line(vector<int> road); 
	void add_line(int a, int b, int c);
	void add_line(int a, int b, int c, int d);
	int length() const; 
	void process_poly();
	MPolygon& get_poly(int i); 
	MPolygon get_poly(int i) const;

	void for_allDots(Vector3d(*op) (const Matrix&, const Vector3d&), const Matrix& m);
	void for_allDots(Vector3d(*op) (const Vector3d&, const Vector3d&), const Vector3d& v); 
	Vector3d check_collision(Vector3d oWall); 

	Vector3d get_center(); 

	void clean(); 
	void dots_clean();
	 
private:
	vector<MPolygon> polys;
	vector<vector<int>> roads;
	vector<Vector3d> dots;
	int len;

};
