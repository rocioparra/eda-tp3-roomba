#include "Robot.h"
#include <cmath>
#include <cstdlib>
#include <ctime>	
#include <cstdint>

#define M_PI	3.14159265359
#define DEFAULT_ANGLE	(2*M_PI+1)

Robot::Robot(void)		//contruye cada robot en default
{
	xmax = 0;
	ymax = 0;
	angle = DEFAULT_ANGLE;
}

void Robot::redefRobot(uint32_t _xmax, uint32_t _ymax)		//recontruye cada robot con las variables pasadas y sus respectivos randoms
{
	xmax= _xmax;
	ymax= _ymax;
	angle = (rand() % (2*M_PI));
	moveToPoint(randomPoint());
	return;
}

bool Robot::moveToPoint(Point& _p)		//Mueve al robot a un punto dado del plano, siempre y cuando sea posible
{										//En caso de no ser posible devuelve false.
	double c;
	if( ((c = _p.getX()) < xmax) && (c>0) && ((c = _p.getY())< ymax) && (c > 0))
	{
		p.setX(_p.getX()); 
		p.setY(_p.getY());
		return true;
	}
	else
		return false;
}

bool Robot::move(void)			//Mueve al robot en una unidad hacia la direccion indicada por el angulo, en caso de no ser posible devuelve un false.
{
	double c,d;
	if (((c = (p.getX() + sin(angle))) < xmax) && (c>0) && ((d = (p.getY() + cos(angle))) < ymax) && (d>0))
	{
		p.setX(c);
		p.setY(d);
		return true;
	}
	else
		return false;
}

double Robot::getX(void)
{
	return p.getX();
}

double Robot::getY(void)
{
	return p.getY();
}

double Robot::getAngle(void)
{
	return angle;
}

Point Robot::randomPoint(void)		//Genera un punto random del plano
{
	Point _p;
	_p.setX(((double)rand())/(RAND_MAX/xmax));
	_p.setY(((double)rand())/(RAND_MAX/ymax));
	return _p;
}

bool Robot::checkAngle(void)  //Funcion que genera un nuevo angulo SOLO EN EL CASO DE SER NECESARIO, en caso de no serlo, deja el angulo como estaba.
{
	double nextX, nextY;
	if (((nextX = p.getX() + sin(angle)) < xmax) && (nextX>0) && ((nextY = p.getY() + cos(angle)) < ymax) && (nextY>0))
		return false;
	else
	{
		angle = (rand() % (2*M_PI));
		return true;
	}
}

bool Robot::checkEverythingOk(void)
{
	if((angle<(2*M_PI)) && (angle > 0) && (p.getX() < xmax) && (p.getX() > 0) && (p.getY() <ymax) && (p.getY() >0))
		return true;
	else
		return false;
}
