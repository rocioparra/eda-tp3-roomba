#ifndef ROOMBA_ARGS_H
#define ROOMBA_ARGS_H

extern "C" {
#include "parseCmdLine.h"
}

typedef unsigned int uint;

class RoombaArgs{
  private:
	uint width;			//ancho del piso
	uint height;		//alto del piso
	uint robotN;		//numero de robots que limpian simultaneamente
	uint mode;			//1: grafica un ciclo de limpieza; 2: saca los ticks promedio para cada n hasta llegar a robotN



  public:
	RoombaArgs();				//constructor
	uint getWidth();
	uint getHeight();
	uint getMode();
	uint getRobotN();

	void setWidth(uint);		//setters
	void setHeight(uint);
	void setMode(uint);
	void setRobotN(uint);

};



#endif //ROOMBA_ARGS_H
