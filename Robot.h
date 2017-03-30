#ifndef ROBOT_H
#define ROBOT_H

/*	

	Instituto Tecnológico de Buenos Aires
	22.08 - Algoritmos y estructura de datos

	Trabajo práctico n° 3: Robots

	Autores:	Díaz, Ian Cruz				- legajo 57.515
				Parra, Rocío				- legajo 57.669
				Stewart Harris, María Luz	- legajo 57.676

	Fecha de entrega: jueves 30 de marzo de 2017

***********************************************************************************************************
	
	Clase robots
	Cada robot esta ubicado en un punto y se mueve en linea recta con un cierto angulo. Su posicion siempre
tiene que ser positiva y menor que un cierto numero, especifico para cada robot creado.

*/


#include "Point.h"
#include <cstdint>


class Robot
{
private:
	Point p; //class Point {public: double x; double y;};
	double angle;
	uint32_t xmax;
	uint32_t ymax;

	Point randomPoint(void);
	/*Funcion que devuelve un objeto del tipo Point Random.
	  ACLARACION: necesita tener antes definida e inicializada xmax e ymax.
	*/
public:
	Robot(void);
	/*Funcion Contructora por defecto.Inicializa:
		xmax = 0, ymax=0, angle = DEFAULT_ANGLE.  (DEFAULT_ANGLE = 2*M_PI)
	 */
	void redefRobot(uint32_t _xmax, uint32_t _ymax);
	/*Funcion reconstructora, inicializa las variables xmax e ymax con los parametros recibidos, y mueve al robor a un punto random del plano.
	  Se la llama de la siguiente manera:
	  {
		...
		Robot r;
		r.Robot(XMAX, YMAX) //XMAX e YMAX podrian ser parametros creados en el programa o defines.
		...
	  }
	*/
	bool moveToPoint(Point& _p);
	/*Funcion que bien podria ser private:, pero se la deja como publica por si el programador queire inicializar el robot en algun punto en especifico
	ACLARACION: devuelve true si se pudo inicializar el robot en la posicion indicada, o false si la posicion indicada esta fuera del rango de nuestro plano.
	Se usa de la siguiente manera:
	{
		...
		Point p;
		Robot r;
		if(r.moveToPoint(p) == false)
		{
			printf("No se pudo inicializar el robot en la posicion indicada!\n");
		}
	}
	*/
	bool checkAngle(void);
	/*Funcion que checkea si es necesario cambiar el angulo, y si es asi, genera un nuevo angulo, y se lo asigna a la variable angle. En caso de no ser necesario
	cambiar el angulo, deja la variable Angle como estaba.
	
	Solo para debug, devuelve false si no fue necesario cambiar Angle, y devuelve true si fue necesario cambiar Angle */
	bool move();
	/*Funcion que mueve al robot en 1 unidad hacia el angulo donde apunta su direccion(devuelve true si se pudo mover, y false si no se pudo   solo para debug)*/
	double getX();	//Getter de la posicion en x del robot
	double getY();	//Getter de la posicion en y de robot
	double getAngle();	//Getter del angulo direccion del robot.
	void setAngle(double temp);	//Setter del angulo del robot.
};



#endif //ROBOT_H
