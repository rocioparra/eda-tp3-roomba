#include "ZoombaArgs.h"
#include <string>
#include <cstdlib>

using namespace std;

int check (char * key, char * value, void * userData);


ZoombaArgs :: ZoombaArgs()
{
	callback = check;		//el unico dato que hay que inicializar es el callback!
}



int check (char * _key, char * _value, void * userData)
{
	if (_key == NULL)		//el programa zoomba solo recibe opciones como argumento
		return false;

	errno = 0;				
	uint valueNumber = (uint) strtoul(_value, NULL, 10);	//convertir value a un entero no signado en base 10
	if (!(errno && valueNumber))			//verificar que se la conversion se hizo bien y que el value no era 0												
		return false;				//como todos los values de este programa son uints > 0 , si es otra cosa es error

	string key(_key);										//pasar a string por simplicidad en el codigo
	ZoombaArgs * ud = (ZoombaArgs *) userData;				
	int status = false;							//status cambiara a true si se verifica que se recibio algo valido

	//	Se procede a verificar que la key sea una de las validas y a guardar el valor donde corresponda.
	//  El control de cuales son los parametros maximos que se puede recibir lo hara la simulacion, esta
	//funcion solo verifica que los numeros sean mayores a 0 y que el modo sea valido.

	if (key == "Width") {
		(*ud).setWidth(valueNumber);
		status = true;
	}

	else if (key == "Height") {
		(*ud).setHeight(valueNumber);
		status = true;
	}

	else if (key == "Robots") {
		(*ud).setRobotN(valueNumber);
		status = true;
	}

	else if (key == "Modo") {				
		if ( valueNumber <=2 ) { //modo puede ser solo 1 o 2
			(*ud).setMode(valueNumber);
			status = true;
		}
	}

	return status;
}


pCallback ZoombaArgs :: getCallback()
{
	return callback;
}


uint ZoombaArgs :: getWidth()
{
	return width;
}


uint ZoombaArgs :: getHeight()
{
	return height;
}


uint ZoombaArgs :: getMode()
{
	return mode;
}


uint ZoombaArgs :: getRobotN()
{
	return robotN;
}



void ZoombaArgs :: setWidth(uint _width)
{
	width = _width;
}


void ZoombaArgs :: setHeight(uint _height)
{
	height = _height;
}


void ZoombaArgs :: setMode(uint _mode)
{
	mode = _mode;
}


void ZoombaArgs :: setRobotN(uint _robotN)
{
	robotN = _robotN;
}