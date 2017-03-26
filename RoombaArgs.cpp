#include "RoombaArgs.h"
#include <string>
#include <cstdlib>



using namespace std;

int check (char * key, char * value, void * userData);


RoombaArgs :: RoombaArgs()
{
	width = 0;	//si alguno de estos valores sigue siendo 0 despues de llamar al parser,
	height = 0;	//sabremos que ese dato no se recibio (ya que el callback verifica que 
	robotN = 0;	//el valor recibido no sea 0
	mode = 0;
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
