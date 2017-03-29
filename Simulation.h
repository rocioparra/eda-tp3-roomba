#ifndef SIMULATION_H
#define SIMULATION_H

#include "Robot.h"
#include "Floor.h"
#include "Graphics.h" 
#include <stdint.h>

//parametros maximos aceptados por esta simulacion
#define MAX_ROBOTS	100
#define MAX_WIDTH	100
#define	MAX_HEIGHT	70


class Simulation 
{
  private:
	bool valid;			//si es false, no se pudo implementar la simulacion 
	uint32_t robotCount;	//numero de robots que estan limpiando simultaneamente
	uint64_t ticks;
	//cantidad de ticks que pasaron desde que empezo la simulacion.
	//empieza en 0 e incrementa cada vez que se llama a nextSimulationStep,
	//hasta que se limpie el piso completamente

	Floor * f;			//el piso que se esta limpiando
	Robot * r;			//direccion del primer robot
	Graphics * g;

public:
	Simulation(uint32_t _robotCount,uint32_t _width, uint32_t _height, Graphics * _g = NULL); 
	//recibe la cantidad de robots y el tamano del piso para la simulacion.
	//si se quiere graficar, recibe un puntero a un objeto graphic

	bool isValid();	
	//verifica que los parametros hayan sido validos, y que se haya podido reservar memoria

	uint64_t getTickCount();	//getters
	uint32_t getRobotCount();
	uint32_t getFloorWidth();
	uint32_t getFloorHeight();

	bool nextSimulationStep();
	//realiza el siguiente paso de la simulacion e incrementa el tick counter.
	//devuelve true si el piso ya esta limpio y false si no.

	void destroy();
};




#endif //SIMULATION_H
