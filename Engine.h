#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include "faststack.h"
#include "vector.h"
#include "matrix.h"
#include "vector3d.h"
#include "mpolygon.h"
#include "figure.h"

#include "graphics.h"
#pragma comment(lib,"graphics.lib")

class Engine
{
public:
	Engine();
	Engine(int width, int height);
	~Engine();

	void draw_dot(double x, double y, int color, const MPolygon& p); 

	void draw_line(double x1, double y1, double x2, double y2, int color, const MPolygon& p); 

	double z_buff_get_pix(double x, double y, const MPolygon& p);

	void fill_z_buff(const MPolygon& p);
	void fill(double x, double y, int color, int bordercolor, const MPolygon& p); 
	void draw_poly(const MPolygon& p, int color, int colorborders, bool fillflag = true); 
	void draw_figure(const Figure& f, int colorborders, bool fillflag);

	void clean(); 
private:
	int width; 
	int height; 
	double** z_buff;
};