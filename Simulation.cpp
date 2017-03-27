#include "Simulation.h"
#include <new>
#include <chrono>
#include <thread>

#define FPS(x)	(1000/(x))


Simulation :: Simulation(uint _robotCount, uint _width, uint _height, Graphics * _g)
{
	ticks = 0;
	robotCount = _robotCount;

	if (_g == NULL)		//si graphic es NULL es porque no hay que graficar
		wantToGraphic = false;
	else
		wantToGraphic = true;

	valid = false;	//empieza como false. Si podemos hacer todo sin errores, ponemos true
	r = NULL;		//en caso de que haya un error antes de definir los punteros, los ponemos en NULL
	f = NULL;

	if (_robotCount <= MAX_ROBOTS && _height <= MAX_HEIGHT && _width <= MAX_WIDTH ) {
	//primero verificamos que los parametros recibidos sean validos para esta simulacion
		f = new Floor(_width, _height);
		if (f != NULL) {					//verificar que se haya podido reservar memoria para el piso
			r = new Robot[robotCount];
			if (r != NULL)	
				if ((*f).isValid()) {											//lo mismo para los robots
					valid = true;						//en este punto, ya se hizo todo el control de error
					g = _g;
					for ( uint i = 0; i<robotCount; i++ )					//inicializar todos los robots
						r[i].redefRobot(_width, _height);
				}
		}
	}
}


bool Simulation :: isValid ()
{
	return valid;
}

bool Simulation :: nextSimulationStep()
{
	//primero chequear que no se haya terminado previamente y que los punteros esten inicializados
	//por evaluacion lazy, solo se ejecuta "(*f).isDirty()" si se verifico que f no era NULL
	if  ( f == NULL || r == NULL || !(*f).isDirty() ) 
		return true;

	ticks++;	//indicar que se hizo otro paso mas

	for (uint i = 0; i<robotCount; i ++) {
		if (!r[i].checkAngle()) {   //hace falta cambiar el angulo? si es asi, lo cambia
			r[i].move();			//si no, mueve el robot y limpia la baldosa donde cae

			(*f).cleanTile( uint (r[i].getX()), uint (r[i].getY()));
			//al castear a int se trunca: si x=3,45, y=0,23, el robot esta en la fila
			//3 y la columna 0 del piso
		}
	}
	if (wantToGraphic)
	{
		(*g).drawFloor((*f).getFloor(), (*f).getWidth(), (*f).getHeight());

		for (uint i = 0; i < robotCount; i++) {
			(*g).drawRobot(r[i].getX(), r[i].getY(), r[i].getAngle());
		}

		(*g).showChanges();
		std::this_thread::sleep_for(std::chrono::milliseconds(FPS(80)));
	}	
		
	return !(*f).isDirty();	//devuelve true si el piso esta limpio
}
	
	
ulong Simulation :: getTickCount()
{
	return ticks;
}
	
	
uint Simulation :: getRobotCount()
{
	return robotCount;
}
	
	
uint Simulation :: getFloorWidth()
{
	if (f == NULL)	//si no esta inicializado f, el piso no tiene ancho porque no existe
		return 0;
	else
		return (*f).getWidth();
}
	
	
uint Simulation :: getFloorHeight()
{
	if (f == NULL)	//si no esta inicializado f, el piso no tiene alto porque no existe
		return 0;
	else
		return (*f).getHeight();
}
	

bool Simulation :: amIgraphing()
{
	return wantToGraphic;
}
	
	
void Simulation :: startGraphing()
{
	wantToGraphic = true;
}
	
	
void Simulation :: stopGraphing()
{
	wantToGraphic = false;
}
	
void Simulation :: destroy()
{
	delete f;
	delete r;
	f = NULL;
	r = NULL;
}
