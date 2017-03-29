#include "RoombaArgs.h"
#include <string>
#include <cstdlib>
#include <cstdint>


using namespace std;

int32_t check (char * key, char * value, void * userData);


RoombaArgs :: RoombaArgs()
{
	width = 0;	//si alguno de estos valores sigue siendo 0 despues de llamar al parser,
	height = 0;	//sabremos que ese dato no se recibio (ya que el callback verifica que 
	robotN = 0;	//el valor recibido no sea 0
	mode = 0;
}

uint32_t RoombaArgs :: getWidth()
{
	return width;
}


uint32_t RoombaArgs :: getHeight()
{
	return height;
}


uint32_t RoombaArgs :: getMode()
{
	if ( height && width && (mode == 2 || robotN ) )
	//ambos modos necesitan height y width. Si el modo es 2, robotN puede no estar
	//esto tambien se cumplira si el modo no se recibio, pero en ese caso mode == 0
		return mode;
	else
		return 0;	//el modo no esta bien: devuelvo 0
}


uint32_t RoombaArgs :: getRobotN()
{
	return robotN;
}



void RoombaArgs :: setWidth(uint32_t _width)
{
	width = _width;
}


void RoombaArgs :: setHeight(uint32_t _height)
{
	height = _height;
}


void RoombaArgs :: setMode(uint32_t _mode)
{
	mode = _mode;
}


void RoombaArgs :: setRobotN(uint32_t _robotN)
{
	robotN = _robotN;
}
