#ifndef ZOOMBA_ARGS_H
#define ZOOMBA_ARGS_H

#include "parseCmdLine.h"

typedef unsigned int uint;

class ZoombaArgs{
  private:
	uint width;			//ancho del piso
	uint height;		//alto del piso
	uint robotN;		//numero de robots que limpian simultaneamente
	uint mode;			//1: grafica un ciclo de limpieza; 2: saca los ticks promedio para cada n hasta llegar a robotN
	pCallback callback; //callback que se le debe pasar al parser

  public:
	ZoombaArgs();				//constructor

	pCallback getCallback();	//getters
	uint getWidth();
	uint getHeight();
	uint getMode();
	uint getRobotN();

	void setWidth(uint);		//setters
	void setHeight(uint);
	void setMode(uint);
	void setRobotN(uint);

};



#endif //ZOOMBA_ARGS_H
