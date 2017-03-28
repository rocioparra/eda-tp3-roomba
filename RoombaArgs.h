#ifndef ROOMBA_ARGS_H
#define ROOMBA_ARGS_H
#include <stdint.h>

extern "C" {
#include "parseCmdLine.h"
}


class RoombaArgs{
private:
	uint32_t width;			//ancho del piso
	uint32_t height;		//alto del piso
	uint32_t robotN;		//numero de robots que limpian simultaneamente
	uint32_t mode;			//1: grafica un ciclo de limpieza; 2: saca los ticks promedio para cada n hasta llegar a robotN

public:
	RoombaArgs();				//constructor

	uint32_t getWidth();
	uint32_t getHeight();
	uint32_t getMode();
	uint32_t getRobotN();

	void setWidth(uint32_t);		//setters
	void setHeight(uint32_t);
	void setMode(uint32_t);
	void setRobotN(uint32_t);

};



#endif //ROOMBA_ARGS_H
