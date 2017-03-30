#ifndef POINT_H
#define POINT_H

/*	

	Instituto Tecnol�gico de Buenos Aires
	22.08 - Algoritmos y estructura de datos

	Trabajo pr�ctico n� 3: Robots

	Autores:	D�az, Ian Cruz				- legajo 57.515
				Parra, Roc�o				- legajo 57.669
				Stewart Harris, Mar�a Luz	- legajo 

	Fecha de entrega: jueves 30 de marzo de 2017

***********************************************************************************************************
	
	Clase Point
	Cada elemento contiene dos coordenadas, que son de tipo double.

*/


#include <cstdint>

class Point
{
  private:
	double x;
	double y;

  public:
	Point(double _x=0.0, double _y=0.0);	//punto por default = (0,0)

	double getX();	//getters
	double getY();

	void setX(double _x);	//setters (cualquier valor es valido)
	void setY(double _y);
};

#endif //POINT_H

