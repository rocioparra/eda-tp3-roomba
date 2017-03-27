#include "Robot.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define M_PI	3.14159265359

Robot::Robot(void)		//contruye cada robot en default
{
	xmax = 0;
	ymax = 0;
	angle = DEFAULT_ANGLE;
}

void Robot::redefRobot(uint _xmax, uint _ymax)		//recontruye cada robot con las variables pasadas y sus respectivos randoms
{
	xmax= _xmax;
	ymax= _ymax;
	angle = (rand() % 360);
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
	double _angle = changeAngle2Rad();
	double c = p.getX() + sin(_angle);
	double d = p.getY() + cos(_angle);
	
	//if (((c = (p.getX() + sin(_angle))) < xmax) && (c>0) && ((d = (p.getY() + cos(_angle))) < ymax) && (d>0))
	{
		p.setX(c);
		p.setY(d);
		return true;
	}
	//else
	//	return false;
}

double Robot::changeAngle2Rad(void)		//Funciones que recibe un angulo y lo transforma a radianes.
{
	double temp;
	temp = angle* M_PI /180;
	return temp;
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
	_p.setX(myRand(xmax));
	_p.setY(myRand(ymax));
	return _p;
}

bool Robot::checkAngle(void)  //Funcion que genera un nuevo angulo SOLO EN EL CASO DE SER NECESARIO, en caso de no serlo, deja el angulo como estaba.
{
	double _angle = changeAngle2Rad();
	double c= p.getX() + sin(_angle);
	double d = p.getY() + cos(_angle);
	bool changed = true;

	if (c < 0 && d < 0)
	{
		angle = (rand() % 90) + 90;	//darle un angulo que seguro sirva
	}
	else if ( c>xmax && d>ymax )
	{
		angle = (rand() % 90) + 270;
	}
	else if ( c<0 )
	{
		angle = (rand() % 180) + 90;
	}
	else if (d<0)
	{
		angle = (rand() % 180);	
	}
	else if (c>xmax)
	{
		angle = (rand() % 180) - 90;
		angle = (angle >= 0) ? angle : (360 + angle);
	}
	else if (d>ymax)
	{
		angle = (rand() % 180) + 180;
	}
	else
	{
		changed = false;
	}

	return changed;
}

bool Robot::checkEverythingOk(void)
{
	if((angle<360) && (angle > 0) && (p.getX() < xmax) && (p.getX() > 0) && (p.getY() <ymax) && (p.getY() >0))
		return true;
	else
		return false;
}

double Robot::myRand(uint max)
{
	return (((double)rand())/(RAND_MAX/max));
}