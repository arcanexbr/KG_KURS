#define _USE_MATH_DEFINES
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "TCPServer.h"
#include "matrixlist.h"
#include "figure.h"
#include <iostream>
#include <sstream>
#include "Engine.h"
#include <Windows.h>
#include <string>
#define MOVE_SPEED 5
#define SCALE_POWER 1.05
#define ROTATE_SPEED 5
#define START_SCALE 100
#define BUFF_DRAWER
#define ANDROID 0
using namespace std;


int main(void)
{	
	MessageBox(NULL, L"w, s, a, d, c, v - движение фигуры\nq, e, z, x, r, t - вращение фигуры\n -, = - изменение размера фигуры\np - включение рендера\n1, 2, 3, - выбор фигуры (1 - все, 2 - параллелепипед, 3 - пирамида)", L"Управление", MB_OK);
	char c;
	double d_rotxPar = 0, d_rotyPar = 0, d_rotzPar = 0, d_scPar = 1;
	double d_rotxPyr = 0, d_rotyPyr = 0, d_rotzPyr = 0, d_scPyr = 1;
	char mode = 1;
	Vector3d coordsPar(0, 0, 0), coordsPyr(1 * START_SCALE, 0, 0);
	double scPar = START_SCALE, scPyr = START_SCALE;
	Matrix matPar, matPyr, matPyrchange;

	Matrix matshadowParX;
	Matrix matshadowPyrX;
	Matrix matshadowX;

	Matrix matshadowParY;
	Matrix matshadowPyrY;
	Matrix matshadowY;

	Matrix matshadowParZ;
	Matrix matshadowPyrZ;
	Matrix matshadowZ;

	Figure originalPar;
	Figure worldPar;
	Figure shadowXPar;
	Figure shadowYPar;
	Figure shadowZPar;

	Figure originalPyr;
	Figure worldPyr;
	Figure shadowXPyr;
	Figure shadowYPyr;
	Figure shadowZPyr;

	Figure walls;
	Matrix matWalls;

	originalPar.add_dot(Vector3d(-1, 1, 1)); 
	originalPar.add_dot(Vector3d(-1, 1, -1)); 
	originalPar.add_dot(Vector3d(1, 1, -1)); 
	originalPar.add_dot(Vector3d(1, 1, 1)); 
	originalPar.add_dot(Vector3d(-1, -1, 1)); 
	originalPar.add_dot(Vector3d(-1, -1, -1)); 
	originalPar.add_dot(Vector3d(1, -1, -1)); 
	originalPar.add_dot(Vector3d(1, -1, 1)); 
	
	originalPyr.add_dot(Vector3d(-1.5, -1.5, 1.5)); 
	originalPyr.add_dot(Vector3d(1.5, -1.5, 0)); 
	originalPyr.add_dot(Vector3d(-1.5, -1.5, -1.5)); 
	originalPyr.add_dot(Vector3d(0, 2, 0)); 

	originalPar.add_line(0, 1, 2, 3);
	originalPar.add_line(0, 1, 5, 4);
	originalPar.add_line(0, 3, 7, 4);
	originalPar.add_line(1, 2, 6, 5);
	originalPar.add_line(2, 3, 7, 6);
	originalPar.add_line(4, 5, 6, 7);
	
	originalPyr.add_line(0, 1, 2);
	originalPyr.add_line(0, 1, 3);
	originalPyr.add_line(0, 2, 3);
	originalPyr.add_line(1, 2, 3);

	walls.add_dot(Vector3d(-2, -2, -2)); 
	walls.add_dot(Vector3d(-2, -2, 15)); 
	walls.add_dot(Vector3d(-2, 15, -2)); 
	walls.add_dot(Vector3d(15, -2, -2)); 
	walls.add_dot(Vector3d(-2, 15, 15)); 
	walls.add_dot(Vector3d(15, 15, -2)); 
	walls.add_dot(Vector3d(15, -2, 15)); 

	walls.add_line(0, 1, 4, 2);
	walls.add_line(0, 1, 6, 3);
	walls.add_line(0, 2, 5, 3);


	Vector3d light(1, 50, 1);
	Vector3d center;
	Vector3d d_center;
	bool fillflag;
	bool changeflag = true;
	fillflag = false;

	Engine draw(800, 800);

	worldPar = originalPar;
	shadowXPar = originalPar;
	shadowYPar = originalPar;
	shadowZPar = originalPar;

	worldPyr = originalPyr;
	shadowXPyr = originalPyr;
	shadowYPyr = originalPyr;
	shadowZPyr = originalPyr;

	Vector3d Owalls = Vector3d(-2, -2, -2);
	Owalls = multiplyMatrix(getScale(START_SCALE, START_SCALE, START_SCALE), Owalls);
	Vector3d collPar, collPyr, coll;

	matWalls = getScale(100, 100, 100);
	matWalls = multiply(getCabinet(), matWalls);

	walls.for_allDots(multiplyMatrix, matWalls);

	walls.process_poly();
	if (ANDROID) {
		CTCPServer tcpServer;
		cout << "wait connect!" << endl;
		tcpServer.Start("192.168.31.183", 4444).join();
		cout << "connect successful!" << endl;
		string input;
		int inputXY = 0;
		int inputXZ = 0;
		int inputZY = 0;
		int d_inputXY = 0;
		int d_inputXZ = 0;
		int d_inputZY = 0;
		while (1) {
			tcpServer.RecvData().detach();

			input = tcpServer.GetRecvData();
			if (inputXY != ((input[0] - 48) * 100 + (input[1] - 48) * 10 + (input[2] - 48))) {
				d_inputXY = (abs((input[0] - 48) * 100 + (input[1] - 48) * 10 + (input[2] - 48) - inputXY) < 50) ? ((input[0] - 48) * 100 + (input[1] - 48) * 10 + (input[2] - 48) - inputXY) : 0;
				inputXY = ((input[0] - 48) * 100 + (input[1] - 48) * 10 + (input[2] - 48));

				d_rotzPar += d_inputXY;
				d_rotzPyr += d_inputXY;
				changeflag = true;
			}
			if (inputXZ != ((input[3] - 48) * 100 + (input[4] - 48) * 10 + (input[5] - 48))) {
				d_inputXZ = (abs((input[3] - 48) * 100 + (input[4] - 48) * 10 + (input[5] - 48) - inputXZ) < 50) ? ((input[3] - 48) * 100 + (input[4] - 48) * 10 + (input[5] - 48) - inputXZ) : 0;
				inputXZ = ((input[3] - 48) * 100 + (input[4] - 48) * 10 + (input[5] - 48));
				d_rotyPar += d_inputXZ;
				d_rotyPyr += d_inputXZ;
				changeflag = true;
			}
			if (inputZY != ((input[6] - 48) * 100 + (input[7] - 48) * 10 + (input[8] - 48))) {
				d_inputZY = (abs((input[6] - 48) * 100 + (input[7] - 48) * 10 + (input[8] - 48) - inputZY) < 50) ? ((input[6] - 48) * 100 + (input[7] - 48) * 10 + (input[8] - 48) - inputZY) : 0;
				inputZY = ((input[6] - 48) * 100 + (input[7] - 48) * 10 + (input[8] - 48));
				d_rotxPar += d_inputZY;
				d_rotxPyr += d_inputZY;
				changeflag = true;
			}
			cout << inputXY << " " << inputXZ << " " << inputZY << '\n';


			if (changeflag)
			{
				scPar *= d_scPar;
				scPyr *= d_scPyr;

				matPar.set_ones();
				matPyr.set_ones();

				matPar = multiply(getRotationX(d_rotxPar), matPar);
				matPar = multiply(getRotationY(d_rotyPar), matPar);
				matPar = multiply(getRotationZ(d_rotzPar), matPar);
				originalPar.for_allDots(multiplyMatrix, matPar);

				matPyr = multiply(getRotationX(d_rotxPyr), matPyr);
				matPyr = multiply(getRotationY(d_rotyPyr), matPyr);
				matPyr = multiply(getRotationZ(d_rotzPyr), matPyr);
				originalPyr.for_allDots(multiplyMatrix, matPyr);

				worldPar.copy_dots(originalPar);
				worldPyr.copy_dots(originalPyr);

				matPar = getScale(scPar, scPar, scPar);

				if (mode == 1)
				{
					matPyrchange = multiply(getScale(d_scPyr, d_scPyr, d_scPyr), matPyr);
					center = substract(coordsPyr, coordsPar);
					d_center = multiplyMatrix(matPyrchange, center);
					d_center = substract(d_center, center);
					coordsPyr = add(coordsPyr, d_center);
				}

				matPyr = getScale(scPyr, scPyr, scPyr);

				matPar = multiply(getTranslation(coordsPar.x(), coordsPar.y(), coordsPar.z()), matPar);
				matPyr = multiply(getTranslation(coordsPyr.x(), coordsPyr.y(), coordsPyr.z()), matPyr);

				if (fillflag)
				{
					shadowXPar.copy_dots(originalPar);
					shadowYPar.copy_dots(originalPar);
					shadowZPar.copy_dots(originalPar);

					shadowXPyr.copy_dots(originalPyr);
					shadowYPyr.copy_dots(originalPyr);
					shadowZPyr.copy_dots(originalPyr);

					matshadowParX = multiply(getTranslation(199.9, 0, 0), matPar);
					matshadowParY = multiply(getTranslation(0, 199.9, 0), matPar);
					matshadowParZ = multiply(getTranslation(0, 0, 199.9), matPar);

					matshadowPyrX = multiply(getTranslation(199.9, 0, 0), matPyr);
					matshadowPyrY = multiply(getTranslation(0, 199.9, 0), matPyr);
					matshadowPyrZ = multiply(getTranslation(0, 0, 199.9), matPyr);

					matshadowX = getTranslation(-199.99, 0, 0);
					matshadowY = getTranslation(0, -199.99, 0);
					matshadowZ = getTranslation(0, 0, -199.99);

					matshadowX = multiply(getCabinet(), matshadowX);
					matshadowY = multiply(getCabinet(), matshadowY);
					matshadowZ = multiply(getCabinet(), matshadowZ);
				}

				worldPar.for_allDots(multiplyMatrix, matPar);
				collPar = worldPar.check_collision(Owalls);

				worldPyr.for_allDots(multiplyMatrix, matPyr);
				collPyr = worldPyr.check_collision(Owalls);

				if (mode == 1)
				{
					coll = Vector3d(min(collPar.x(), collPyr.x()), min(collPar.y(), collPyr.y()), min(collPar.z(), collPyr.z()));
					collPar = coll;
					collPyr = coll;

				}
				coordsPar = substract(coordsPar, collPar);
				coordsPyr = substract(coordsPyr, collPyr);

				matPyr = getTranslation(-collPyr.x(), -collPyr.y(), -collPyr.z());

				matPar = getTranslation(-collPar.x(), -collPar.y(), -collPar.z());

				matPar = multiply(getCabinet(), matPar);
				worldPar.for_allDots(multiplyMatrix, matPar);

				matPyr = multiply(getCabinet(), matPyr);
				worldPyr.for_allDots(multiplyMatrix, matPyr);

				worldPar.process_poly();
				worldPyr.process_poly();


				draw.clean();

				draw.draw_figure(walls, WHITE, false);
				draw.draw_figure(worldPar, WHITE, fillflag);
				draw.draw_figure(worldPyr, WHITE, fillflag);


				setcolor(BLACK);

				outstreamxy(10, 10);

				worldPar.dots_clean();

				shadowXPar.dots_clean();
				shadowYPar.dots_clean();
				shadowZPar.dots_clean();

				worldPyr.dots_clean();

				shadowXPyr.dots_clean();
				shadowYPyr.dots_clean();
				shadowZPyr.dots_clean();

				d_rotxPar = 0;
				d_rotyPar = 0;
				d_rotzPar = 0;

				d_rotxPyr = 0;
				d_rotyPyr = 0;
				d_rotzPyr = 0;

				d_scPar = 1;
				d_scPyr = 1;
				swapbuffers();
				changeflag = false;


			}
		}
		tcpServer.Close();
		cin.ignore();
		return 0;
	}
	while (1)
	{
		if (kbhit())
		{
			changeflag = true;
			c = getch();
			if (c == 0)
			{
				c = getch();
			}
			while (kbhit()) getch();
			switch (c)
			{
			case 'w':
				switch (mode)
				{
				case 1:
					coordsPar.y() += MOVE_SPEED;
					coordsPyr.y() += MOVE_SPEED;
					break;
				case 2:
					coordsPar.y() += MOVE_SPEED;
					break;
				case 3:
					coordsPyr.y() += MOVE_SPEED;
					break;
				}
				break;
			case 's':
				switch (mode)
				{
				case 1:
					coordsPar.y() -= MOVE_SPEED;
					coordsPyr.y() -= MOVE_SPEED;
					break;
				case 2:
					coordsPar.y() -= MOVE_SPEED;
					break;
				case 3:
					coordsPyr.y() -= MOVE_SPEED;
					break;
				}
				break;
			case 'a':
				switch (mode)
				{
				case 1:
					coordsPar.x() -= MOVE_SPEED;
					coordsPyr.x() -= MOVE_SPEED;
					break;
				case 2:
					coordsPar.x() -= MOVE_SPEED;
					break;
				case 3:
					coordsPyr.x() -= MOVE_SPEED;
					break;
				}
				break;
			case 'd':
				switch (mode)
				{
				case 1:
					coordsPar.x() += MOVE_SPEED;
					coordsPyr.x() += MOVE_SPEED;
					break;
				case 2:
					coordsPar.x() += MOVE_SPEED;
					break;
				case 3:
					coordsPyr.x() += MOVE_SPEED;
					break;
				}
				break;
			case 'c':
				switch (mode)
				{
				case 1:
					coordsPar.z() += MOVE_SPEED;
					coordsPyr.z() += MOVE_SPEED;
					break;
				case 2:
					coordsPar.z() += MOVE_SPEED;
					break;
				case 3:
					coordsPyr.z() += MOVE_SPEED;
					break;
				}
				break;
			case 'v':
				switch (mode)
				{
				case 1:
					coordsPar.z() -= MOVE_SPEED;
					coordsPyr.z() -= MOVE_SPEED;
					break;
				case 2:
					coordsPar.z() -= MOVE_SPEED;
					break;
				case 3:
					coordsPyr.z() -= MOVE_SPEED;
					break;
				}
				break;
			case 'q':
				switch (mode)
				{
				case 1:
					d_rotyPar += ROTATE_SPEED;
					d_rotyPyr += ROTATE_SPEED;
					break;
				case 2:
					d_rotyPar += ROTATE_SPEED;
					break;
				case 3:
					d_rotyPyr += ROTATE_SPEED;
					break;
				}
				break;
			case 'e':
				switch (mode)
				{
				case 1:
					d_rotyPar -= ROTATE_SPEED;
					d_rotyPyr -= ROTATE_SPEED;
					break;
				case 2:
					d_rotyPar -= ROTATE_SPEED;
					break;
				case 3:
					d_rotyPyr -= ROTATE_SPEED;
					break;
				}
				break;
			case 'r':
				switch (mode)
				{
				case 1:
					d_rotxPar += ROTATE_SPEED;
					d_rotxPyr += ROTATE_SPEED;
					break;
				case 2:
					d_rotxPar += ROTATE_SPEED;
					break;
				case 3:
					d_rotxPyr += ROTATE_SPEED;
					break;
				}
				break;
			case 't':
				switch (mode)
				{
				case 1:
					d_rotxPar -= ROTATE_SPEED;
					d_rotxPyr -= ROTATE_SPEED;
					break;
				case 2:
					d_rotxPar -= ROTATE_SPEED;
					break;
				case 3:
					d_rotxPyr -= ROTATE_SPEED;
					break;
				}
				break;
			case 'x':
				switch (mode)
				{
				case 1:
					d_rotzPar -= ROTATE_SPEED;
					d_rotzPyr -= ROTATE_SPEED;
					break;
				case 2:
					d_rotzPar -= ROTATE_SPEED;
					break;
				case 3:
					d_rotzPyr -= ROTATE_SPEED;
					break;
				}
				break;
			case 'z':
				switch (mode)
				{
				case 1:
					d_rotzPar += ROTATE_SPEED;
					d_rotzPyr += ROTATE_SPEED;
					break;
				case 2:
					d_rotzPar += ROTATE_SPEED;
					break;
				case 3:
					d_rotzPyr += ROTATE_SPEED;
					break;
				}
				break;
			case '-':
				switch (mode)
				{
				case 1:
					d_scPar /= SCALE_POWER;
					d_scPyr /= SCALE_POWER;
					break;
				case 2:
					d_scPar /= SCALE_POWER;
					break;
				case 3:
					d_scPyr /= SCALE_POWER;
					break;
				}
				break;
			case '=':
				switch (mode)
				{
				case 1:
					d_scPar *= SCALE_POWER;
					d_scPyr *= SCALE_POWER;
					break;
				case 2:
					d_scPar *= SCALE_POWER;
					break;
				case 3:
					d_scPyr *= SCALE_POWER;
					break;
				}
				break;
			case 'p':
				if (fillflag)
				{
					fillflag = false;
					break;
				}
				fillflag = true;
				break;
			case '1':
				mode = 1;
				break;
			case '2':
				mode = 2;
				break;
			case '3':
				mode = 3;
				break;
			default:
				changeflag = false;
				break;
			}
			
			
		}

		if (changeflag)
		{
			scPar *= d_scPar;
			scPyr *= d_scPyr;

			matPar.set_ones();
			matPyr.set_ones();

			matPar = multiply(getRotationX(d_rotxPar), matPar);
			matPar = multiply(getRotationY(d_rotyPar), matPar);
			matPar = multiply(getRotationZ(d_rotzPar), matPar);
			originalPar.for_allDots(multiplyMatrix, matPar);

			matPyr = multiply(getRotationX(d_rotxPyr), matPyr);
			matPyr = multiply(getRotationY(d_rotyPyr), matPyr);
			matPyr = multiply(getRotationZ(d_rotzPyr), matPyr);
			originalPyr.for_allDots(multiplyMatrix, matPyr);

			worldPar.copy_dots(originalPar);
			worldPyr.copy_dots(originalPyr);

			matPar = getScale(scPar, scPar, scPar);

			if (mode == 1)
			{
				matPyrchange = multiply(getScale(d_scPyr, d_scPyr, d_scPyr), matPyr);
				center = substract(coordsPyr, coordsPar);
				d_center = multiplyMatrix(matPyrchange, center);
				d_center = substract(d_center, center);
				coordsPyr = add(coordsPyr, d_center);
			}

			matPyr = getScale(scPyr, scPyr, scPyr);

			matPar = multiply(getTranslation(coordsPar.x(), coordsPar.y(), coordsPar.z()), matPar);
			matPyr = multiply(getTranslation(coordsPyr.x(), coordsPyr.y(), coordsPyr.z()), matPyr);

			if (fillflag)
			{
				shadowXPar.copy_dots(originalPar);
				shadowYPar.copy_dots(originalPar);
				shadowZPar.copy_dots(originalPar);

				shadowXPyr.copy_dots(originalPyr);
				shadowYPyr.copy_dots(originalPyr);
				shadowZPyr.copy_dots(originalPyr);

				matshadowParX = multiply(getTranslation(199.9, 0, 0), matPar);
				matshadowParY = multiply(getTranslation(0, 199.9, 0), matPar);
				matshadowParZ = multiply(getTranslation(0, 0, 199.9), matPar);

				matshadowPyrX = multiply(getTranslation(199.9, 0, 0), matPyr);
				matshadowPyrY = multiply(getTranslation(0, 199.9, 0), matPyr);
				matshadowPyrZ = multiply(getTranslation(0, 0, 199.9), matPyr);

				matshadowX = getTranslation(-199.99, 0, 0);
				matshadowY = getTranslation(0, -199.99, 0);
				matshadowZ = getTranslation(0, 0, -199.99);

				matshadowX = multiply(getCabinet(), matshadowX);
				matshadowY = multiply(getCabinet(), matshadowY);
				matshadowZ = multiply(getCabinet(), matshadowZ);
			}

			worldPar.for_allDots(multiplyMatrix, matPar);
			collPar = worldPar.check_collision(Owalls);

			worldPyr.for_allDots(multiplyMatrix, matPyr);
			collPyr = worldPyr.check_collision(Owalls);

			if (mode == 1)
			{
				coll = Vector3d(min(collPar.x(), collPyr.x()), min(collPar.y(), collPyr.y()), min(collPar.z(), collPyr.z())) ;
				collPar = coll;
				collPyr = coll;
				
			}
			coordsPar = substract(coordsPar, collPar);
			coordsPyr = substract(coordsPyr, collPyr);

			matPyr = getTranslation(-collPyr.x(), -collPyr.y(), -collPyr.z());

			matPar = getTranslation(-collPar.x(), -collPar.y(), -collPar.z());
			
			matPar = multiply(getCabinet(), matPar);
			worldPar.for_allDots(multiplyMatrix, matPar);

			matPyr = multiply(getCabinet(), matPyr);
			worldPyr.for_allDots(multiplyMatrix, matPyr);

			worldPar.process_poly();
			worldPyr.process_poly();

			if (fillflag)
			{
				matshadowParX = multiply(getTranslation(-collPar.x(), -collPar.y(), -collPar.z()), matshadowParX);
				matshadowParX = multiply(getShadowX(light), matshadowParX);
				matshadowParX = multiply(matshadowX, matshadowParX);
				shadowXPar.for_allDots(multiplyMatrix, matshadowParX);

				matshadowParY = multiply(getTranslation(-collPar.x(), -collPar.y(), -collPar.z()), matshadowParY);
				matshadowParY = multiply(getShadowY(light), matshadowParY);
				matshadowParY = multiply(matshadowY, matshadowParY);
				shadowYPar.for_allDots(multiplyMatrix, matshadowParY);

				matshadowParZ = multiply(getTranslation(-collPar.x(), -collPar.y(), -collPar.z()), matshadowParZ);
				matshadowParZ = multiply(getShadowZ(light), matshadowParZ);
				matshadowParZ = multiply(matshadowZ, matshadowParZ);
				shadowZPar.for_allDots(multiplyMatrix, matshadowParZ);


				matshadowPyrX = multiply(getTranslation(-collPyr.x(), -collPyr.y(), -collPyr.z()), matshadowPyrX);
				matshadowPyrX = multiply(getShadowX(light), matshadowPyrX);
				matshadowPyrX = multiply(matshadowX, matshadowPyrX);
				shadowXPyr.for_allDots(multiplyMatrix, matshadowPyrX);

				matshadowPyrY = multiply(getTranslation(-collPyr.x(), -collPyr.y(), -collPyr.z()), matshadowPyrY);
				matshadowPyrY = multiply(getShadowY(light), matshadowPyrY);
				matshadowPyrY = multiply(matshadowY, matshadowPyrY);
				shadowYPyr.for_allDots(multiplyMatrix, matshadowPyrY);

				matshadowPyrZ = multiply(getTranslation(-collPyr.x(), -collPyr.y(), -collPyr.z()), matshadowPyrZ);
				matshadowPyrZ = multiply(getShadowZ(light), matshadowPyrZ);
				matshadowPyrZ = multiply(matshadowZ, matshadowPyrZ);
				shadowZPyr.for_allDots(multiplyMatrix, matshadowPyrZ);

				shadowXPar.process_poly();
				shadowYPar.process_poly();
				shadowZPar.process_poly();

				shadowXPyr.process_poly();
				shadowYPyr.process_poly();
				shadowZPyr.process_poly();
			}

			draw.clean();

			draw.draw_figure(walls, WHITE, false);
			draw.draw_figure(worldPar, WHITE, fillflag);
			draw.draw_figure(worldPyr, WHITE, fillflag);

			if (fillflag)
			{
				for (int i = 0, l = walls.length(); i < l; i++)
				{
					draw.fill_z_buff(walls.get_poly(i));
				}
				for (int i = 0, l = worldPar.length(); i < l; i++)
				{
					draw.draw_poly(shadowXPar.get_poly(i), WHITE, WHITE, fillflag);
					draw.draw_poly(shadowYPar.get_poly(i), WHITE, WHITE, fillflag);
					draw.draw_poly(shadowZPar.get_poly(i), WHITE, WHITE, fillflag);
				}
				for (int i = 0, l = worldPyr.length(); i < l; i++)
				{
					draw.draw_poly(shadowXPyr.get_poly(i), WHITE, WHITE, fillflag);
					draw.draw_poly(shadowYPyr.get_poly(i), WHITE, WHITE, fillflag);
					draw.draw_poly(shadowZPyr.get_poly(i), WHITE, WHITE, fillflag);
				}

			}

			setcolor(BLACK);
			
			outstreamxy(10, 10);

			worldPar.dots_clean();

			shadowXPar.dots_clean();
			shadowYPar.dots_clean();
			shadowZPar.dots_clean();

			worldPyr.dots_clean();

			shadowXPyr.dots_clean();
			shadowYPyr.dots_clean();
			shadowZPyr.dots_clean();

			d_rotxPar = 0;
			d_rotyPar = 0;
			d_rotzPar = 0;

			d_rotxPyr = 0;
			d_rotyPyr = 0;
			d_rotzPyr = 0;
			
			d_scPar = 1;
			d_scPyr = 1;

			#ifdef BUFF_DRAWER
			swapbuffers();
			#endif
			changeflag = false;
		}
	}
	return 0;
}