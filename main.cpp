#ifdef WIN32

#include <iostream>
#include <chrono>
#include <string>
#include "Simulation.h"
#include "RoombaArgs.h"
#include "Graphics.h"
extern "C" {
#include "parseCmdLine.h"
}
extern "C" {
#include "moreString.h"
}


#define MODE1	1
#define MODE2	2

#define DEBUG
#ifdef DEBUG
#include "mainTest.h"
#endif

using namespace std;


int check (char * _key, char * _value, void * userData);



int main2 (int argc, char * argv[])
{
	RoombaArgs userData;

	srand(time(NULL));
	if((parseCmdLine(argc, argv, check, &userData)) == PARSER_ERROR)
	{
		cout << "ERROR en el pasaje de parametros! Abort!" << endl;
		return -1;
	}


	if(userData.getMode() == MODE1)
	{
		Graphics g(userData.getWidth(), userData.getHeight());
		Simulation s (userData.getRobotN(), userData.getWidth(), userData.getHeight(), &g);
		s.startGraphing();

#ifdef DEBUG
		while (!s.nextSimulationStep())
		cout << "Pasos: " << s.getTickCount() << endl;
#elif
		while(!s.nextSimulationStep());
#endif
		cout << "La simulacion duro: " << s.getTickCount() << endl;
		s.stopGraphing();
	}

	else if (userData.getMode() == MODE2)
	{
		ulong meanTicks[100];
		memset(meanTicks, 0, sizeof(meanTicks));	//Inicializo todo el arreglo en 0
		for(int robs = 1; robs < 100 ; robs++)		//falta verificar otra cosa
		{
			for(int ciclos = 0; ciclos < 1000; ciclos++)
			{
				Simulation s(userData.getRobotN(), userData.getWidth(), userData.getHeight(), NULL);
				while(!s.nextSimulationStep());
				meanTicks[robs-1] += s.getTickCount();
				s.destroy();
			}
			meanTicks[robs-1] /= 1000;
//			graficoParcial(meanTicks);
		}
	}
	return EXIT_SUCCESS;
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

#endif	//WIN32