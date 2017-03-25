#ifndef SIMULATION_H
#define SIMULATION_H

#include "Robot.h"
#include "Floor.h"
//#include "Graphics.h" falta

//parametros maximos aceptados por esta simulacion
#define MAX_ROBOTS	100
#define MAX_WIDTH	20
#define	MAX_HEIGHT	20

typedef unsigned long int ulong; //para simplificar el codigo


class Simulation 
{
  private:
	bool valid;			//si es false, no se pudo implementar la simulacion 
	uint robotCount;	//numero de robots que estan limpiando simultaneamente
	ulong ticks;
	//cantidad de ticks que pasaron desde que empezo la simulacion.
	//empieza en 0 e incrementa cada vez que se llama a nextSimulationStep,
	//hasta que se limpie el piso completamente

	Floor * f;			//el piso que se esta limpiando
	Robot * r;			//direccion del primer robot
	bool wantToGraphic;	//si es true, va a mostrar la simulacion por pantalla
//	Graphics * graph;

public:
	Simulation(uint _robotCount, uint _width, uint _height); //falta graphic
	//recibe la cantidad de robots y el tamano del piso para la simulacion.
	//si se quiere graficar, recibe un puntero a un objeto graphic

	bool isValid();	
	//verifica que los parametros hayan sido validos, y que se haya podido reservar memoria

	ulong getTickCount();	//getters
	uint getRobotCount();
	uint getFloorWidth();
	uint getFloorHeight();
	bool amIgraphing();

	void startGraphing();			//setters para wantToGraphic
	void stopGraphing();

	bool nextSimulationStep();
	//realiza el siguiente paso de la simulacion e incrementa el tick counter.
	//devuelve true si el piso ya esta limpio y false si no
};




#endif //SIMULATION_H
