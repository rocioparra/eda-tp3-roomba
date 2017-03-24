#include "Robot.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define M_PI	3.14159265359

Robot::Robot(uint _xmax, uint _ymax)
{
	xmax= _xmax;
	ymax= _ymax;
	moveRobotToPoint(randomPoint());
	return;
}

bool Robot::moveRobotToPoint(Point& _p)
{
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

bool Robot::moveRobot(void)
{
	double _angle, c,d;
	_angle = changeAngle2Rad();
	if (((c = p.getX() + sin(_angle)) < xmax) && (c>0) && ((d = p.getY() + cos(_angle)) < ymax) && (d>0))
	{
		p.setX(c);
		p.setY(d);
		return true;
	}
	else
		return false;
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

Point Robot::randomPoint(void)
{
	Point _p;
	srand((uint) time(NULL));
	_p.setX((rand() % xmax));
	_p.setY((rand() % ymax));
	return _p;
}

bool Robot::getNewAngle(void)
{
	double c, d, _angle;
	_angle = changeAngle2Rad();
	if (((c = p.getX() + sin(_angle)) < xmax) && (c>0) && ((d = p.getY() + cos(_angle)) < ymax) && (d>0))
		return false;
	else
	{
		srand((uint) time(NULL));
		angle = (rand() % 360);
		return true;
	}
}

bool Robot::checkEverythingOk(void)
{
	if((angle<360) && (angle > 0) && (p.getX() < xmax) && (p.getX() > 0) && (p.getY() <ymax) && (p.getY() >0))
		return true;
	else
		return false;
}