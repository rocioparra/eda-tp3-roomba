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

void Robot::moveRobotToPoint(const Point& _p)
{
	p.x = _p.x;
	p.y = _p.y;
	return;
}

void Robot::moveRobot(void)
{
	double _angle;
	_angle = Robot.change2Rad();
	p.x= p.x + sin(_angle);
	p.y= p.y + cos(_angle);
}

double Robot::change2Rad()		//Funciones que recibe un angulo y lo transforma a radianes.
{
	double temp;
	temp = angle* M_PI /180;
	return temp;
}

double Robot::getX(void)
{
	return p.x;
}

double Robot::getY(void)
{
	return p.y;
}

double Robot::getAngle(void)
{
	return angle;
}

Point Robot::randomPoint(void)
{
	Point _p;
	srand(time(NULL));
	_p.x = (rand() % xmax);
	_p.y = (rand() % ymax);
	return _p;
}