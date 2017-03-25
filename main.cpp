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
typedef struct
{
	int mode;
	unsigned int width;
	unsigned int height;
}UserData_s;

int main (int argc, char * argv[])
{
	ALLEGRO_DISPLAY * display;
	ALLEGRO_BITMAP *robotimg, *tileimg;	//Buscar imagenes
	UserData_s UserData;
	srand(time(NULL));
	if((parseCmdLine(argc, argv, pCallback, UserData)) == ERROR)
	{
		printf("ERROR en el pasaje de parametros! Abort!\n\n");
		return ERROR;
	}
	if(!al_init())
	{
		printf("ERROR, no se pudo inicializar allegro! Abort!\n\n");
		return ERROR;
	}
	display = al_create_display(D_WIDTH,D_HEIGHT);
	if(display == NULL)
	{
		printf("ERROR, no se pudo inicializar el display! Abort!\n\n");
		return ERROR;
	}

	if(modo == MODE1)
	{
		Graphics g;
		Simulacion S(arg_rob, arg_ancho, arg_largo, &g)		//los que dicen arg representan argumentos
		S.startGraphing();
		while(!S.nextSimulationStep());
		printf("La simulacion duro: %d\n",S.getTickCount());

	}
	else if (modo == MODE2)
	{
		meanTicks[100]={0 ... 99 = 0};
		for(int robs = 1; robs < 100 && ... ; robs++)
		{
			for(int ciclos = 0; ciclos < 1000; ciclos++)
			{
				Simulacion S(robs, arg_ancho,arg_largo);
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

#endif	//WIN32