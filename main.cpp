//#ifdef WIN32

#include <iostream>
#include <chrono>
#include <string>
#include <stdint.h>
#include "Simulation.h"
#include "RoombaArgs.h"
#include "Graphics.h"
#include "GraphicMode2.h"
#include "myAudio.h"
extern "C" {
#include "parseCmdLine.h"
}
extern "C" {
#include "moreString.h"
}



#define GRAPHIC	1
#define AVERAGE	2

// CONSTANTES MODO 2:
#define CICLES		1000	//numero de veces que repite la simulacion para calcular el promedio de ticks 
#define MAX_ROBOTS	100		//maximo numero de robots para el que se calcula el promedio de ticks 
#define MIN_DIFF	0,1		//minima diferencia que debe haber entre dos promedios consecutivos para seguir calculando promedios


#define DEBUG
#ifdef DEBUG
#include "mainTest.h"
#endif

using namespace std;


int32_t check (char * _key, char * _value, void * userData);



int32_t main (int32_t argc, char * argv[])
{
	RoombaArgs userData;

	srand(time(NULL));
	if((parseCmdLine(argc, argv, check, &userData)) == PARSER_ERROR)
	{
		cout << "ERROR en el pasaje de parametros! Abort!" << endl;
		return -1;
	}


	if(userData.getMode() == GRAPHIC)
	{
		Graphics g(userData.getWidth(), userData.getHeight());
                MyAudio a(2);
                sampleID bgMusic = a.loadSample("DiscoMusic.wav");
		a.playSampleLooped(bgMusic);

		if(bgMusic == NULL || !s.isValid())
			return -1;
				
		while(!s.nextSimulationStep());
                
		a.stopSamples();
		g.showTickCount(s.getTickCount());
		s.destroy();
                g.destructor();
	}

	else if (userData.getMode() == AVERAGE)
	{
		double meanTicks[100];
		uint32_t n;
		memset(meanTicks, 0, sizeof(meanTicks));	//Inicializo todo el arreglo en 0

		for (n = 0; n < MAX_ROBOTS && ( n>1 && meanTicks[n-2] - meanTicks[n-1] > MIN_DIFF); n++)
		{
			for(ciclos = 0; ciclos < CICLES; ciclos++)
			{
				Simulation s(n+1, userData.getWidth(), userData.getHeight(), NULL);
				if(!s.isValid())
					return -1;
				
				while(!s.nextSimulationStep());
				meanTicks[n] += double (s.getTickCount());
				s.destroy();
			}

			meanTicks[n]/=CICLES;
		}

		GraphicMode2 g(n);
		g.drawAllBars(meanTicks);
		g.showChanges();
	}
	return EXIT_SUCCESS;
}




int32_t check (char * _key, char * _value, void * userData)
{
	if (_key == NULL)		//el programa roomba solo recibe opciones como argumento
		return false;

	int32_t isUInt;

	uint32_t valueNumber = getUnsInt(_value, &isUInt);
	if ( !isUInt || valueNumber == 0 )					//verificar que se la conversion se hizo bien y que el value no era 0												
		return false;				//como todos los values de este programa son uints > 0 , si es otra cosa es error
									//notese que la func. strtol devolvera 0 si no habia un int

	string key(_key);										//pasar a string por simplicidad en el codigo
	RoombaArgs * ud = (RoombaArgs *) userData;				
	int32_t status = false;							//status cambiara a true si se verifica que se recibio algo valido

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

//#endif	//WIN32
