#ifdef WIN32

#include <iostream>
#include <stdio.h>
#include "Floor.h"
#include "Robot.h"
#include "Simulation.h"
#include "Point.h"
#include "parseCmdLine.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#define MODE1	1
#define MODE2	2
#define ERROR	-1
#define D_WIDTH	640
#define D_HEIGHT	400

int pCallback(char *, char*, void *);

int main (int argc, char * argv[])
{
	RoombaArgs UserData;
	RoombaArgs * p2UserData;
	p2UserData = &UserData; 
	srand(time(NULL));
	if((parseCmdLine(argc, argv, check, p2UserData)) == ERROR)
	{
		printf("ERROR en el pasaje de parametros! Abort!\n\n");
		return ERROR;
	}


	if(modo == MODE1)
	{
		Graphics g;
		Simulacion S(UserData.getRobotN(),UserData.getWidth(),UserData.getHeight(), &g);
		S.startGraphing();
		while(!S.nextSimulationStep());
		printf("La simulacion duro: %d\n",S.getTickCount());

	}

	else if (modo == MODE2)
	{
		meanTicks[100];
		memset(meanTicks, 0, sizeof(meanTicks));	//Inicializo todo el arreglo en 0
		for(int robs = 1; robs < 100 && ... ; robs++)
		{
			for(int ciclos = 0; ciclos < 1000; ciclos++)
			{
				Simulacion S(robs,UserData.getWidth(),UserData.getHeight());
				while(!S.nextSimulationStep());
				meanTicks[robs-1] += S.getTickCount();
				S.destroy();
			}
			meanTicks[robs-1] /= 1000;
			graficoParcial(meanTicks);
		}
	}
	else
	{
		///destruirrrrrr;;;
	}
	al_destroy_display(display);
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