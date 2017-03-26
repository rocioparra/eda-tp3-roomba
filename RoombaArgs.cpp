#include "RoombaArgs.h"
#include <string>
#include <cstdlib>
extern "C" {
#include "moreString.h"
}


using namespace std;

int check (char * key, char * value, void * userData);


RoombaArgs :: RoombaArgs()
{
	width = 0;	//si alguno de estos valores sigue siendo 0 despues de llamar al parser,
	height = 0;	//sabremos que ese dato no se recibio (ya que el callback verifica que 
	robotN = 0;	//el valor recibido no sea 0
	mode = 0;

	
	callback = check;		
}



int check (char * _key, char * _value, void * userData)
{
	if (_key == NULL)		//el programa roomba solo recibe opciones como argumento
		return false;

	int isUInt;

	uint valueNumber = getUnsInt(_value, &isUInt);
	if ( !isUInt || valueNumber == 0 )					//verificar que se la conversion se hizo bien y que el value no era 0												
		return false;				//como todos los values de este programa son uints > 0 , si es otra cosa es error
									//notese que la func. strtol devolvera 0 si no habia un int

	string key(_key);										//pasar a string por simplicidad en el codigo
	RoombaArgs * ud = (RoombaArgs *) userData;				
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


pCallback RoombaArgs :: getCallback()
{

	return callback;
}



uint RoombaArgs :: getWidth()
{
	return width;
}


uint RoombaArgs :: getHeight()
{
	return height;
}


uint RoombaArgs :: getMode()
{
	if ( height && width && (mode == 2 || robotN ) )
	//ambos modos necesitan height y width. Si el modo es 2, robotN puede no estar
	//esto tambien se cumplira si el modo no se recibio, pero en ese caso mode == 0
		return mode;
	else
		return 0;	//el modo no esta bien: devuelvo 0
}


uint RoombaArgs :: getRobotN()
{
	return robotN;
}



void RoombaArgs :: setWidth(uint _width)
{
	width = _width;
}


void RoombaArgs :: setHeight(uint _height)
{
	height = _height;
}


void RoombaArgs :: setMode(uint _mode)
{
	mode = _mode;
}


void RoombaArgs :: setRobotN(uint _robotN)
{
	robotN = _robotN;
}
