#include "Simulation.h"
#include <new>
#include <chrono>
#include <thread>

#define ONE_SECOND	1000
#define FPS			60	

#define PI			3.14159

using namespace std;

Simulation :: Simulation(uint32_t _robotCount, uint32_t _width, uint32_t _height, Graphics * _g)
{
	ticks = 0;
	robotCount = _robotCount;
		
	valid = false;	//empieza como false. Si podemos hacer todo sin errores, ponemos true
	r = NULL;		//en caso de que haya un error antes de definir los punteros, los ponemos en NULL
	f = NULL;
	g = NULL;

	if (_robotCount <= MAX_ROBOTS && _height <= MAX_HEIGHT && _width <= MAX_WIDTH ) {
	//primero verificamos que los parametros recibidos sean validos para esta simulacion
		f = new Floor(_width, _height);
		if (f != NULL) {					//verificar que se haya podido reservar memoria para el piso
			r = new Robot[robotCount];
			if (r != NULL) {	
				if ((*f).isValid()) {											//lo mismo para los robots
					valid = true;						//en este punto, ya se hizo todo el control de error
					g = _g;
					for ( uint32_t i = 0; i<robotCount; i++ )					//inicializar todos los robots
						r[i].redefRobot(_width, _height);
				}
				else {
					delete f;							//si hubo un error despues de reservar memoria, la libera
					delete r;
				}
			}
			else {
				delete f;	
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
	//primero chequea que la simulacion se haya inicializado bien
	if  ( valid == false || f == NULL || r == NULL ) 
		return true;	//devuelve true para que no se ejecuten mas pasos

	ticks++;	//indicar que se hizo otro paso mas

	for (uint32_t i = 0; i<robotCount; i ++) {
		if (!r[i].move()) {   //se pudo mover? si no, cambia el angulo
			r[i].setAngle(double(rand())/double(RAND_MAX)*2*PI);	//si no, mueve el robot y limpia la baldosa donde cae
		}
		(*f).cleanTile(uint32_t (r[i].getX()),uint32_t (r[i].getY()));
		//limpiar la baldosa donde esta el robot
		//al castear a int se trunca: si x=3,45, y=0,23, el robot esta en la fila
		//3 y la columna 0 del piso
	}

	if (g != NULL)	{
	//simulacion grafica
		(*g).drawFloor((*f).getFloor(), (*f).getWidth(), (*f).getHeight());
		//dibuja el piso tal como se encuentra habiendose ejecutado este paso

		for (uint32_t i = 0; i < robotCount; i++) {
			(*g).drawRobot(r[i].getX(), r[i].getY(), r[i].getAngle());
			//ubica cada uno de los robots con el angulo que corresponda
		}

		(*g).showChanges();					//mostrar los resultados obtenidos
		this_thread::sleep_for(chrono::milliseconds(ONE_SECOND/FPS));
		//mostrar un delay para que se llegue a ver
	}	
		
	return !(*f).isDirty();	//devuelve true si el piso esta limpio
}
	
	
uint64_t Simulation :: getTickCount()
{
	return ticks;
}
	
	
uint32_t Simulation :: getRobotCount()
{
	return robotCount;
}
	
	
uint32_t Simulation :: getFloorWidth()
{
	if (f == NULL)	//si no esta inicializado f, el piso no tiene ancho porque no existe
		return 0;
	else
		return (*f).getWidth();
}
	
	
uint32_t Simulation :: getFloorHeight()
{
	if (f == NULL)	//si no esta inicializado f, el piso no tiene alto porque no existe
		return 0;
	else
		return (*f).getHeight();
}

	
void Simulation :: destroy()
{
	delete f;
	delete r;
	f = NULL;
	r = NULL;
	g = NULL;
}
