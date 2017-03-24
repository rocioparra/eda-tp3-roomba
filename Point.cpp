#include "Point.h"


Point :: Point(double _x, double _y)
{
	x = _x;	//inicializa ambas coordenadas con los valores recibidos (o 0 por defecto)
	y = _y;
}	

double Point :: getX()
{
	return x;
}

double Point :: getY()
{
	return y;
}

void Point :: setX(double _x)
{
	x = _x;
}

void Point :: setY(double _y)
{
	y = _y;
}

