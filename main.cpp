#ifdef WIN32

#include <iostream>
#include "Floor.h"
#include "Robot.h"
#include "Simulation.h"
#include "Point.h"

#define MODE1	1
#define MODE2	2


int main (int argc, char * argv[])
{
	//Hay que poner la parse comand line, no se la de quien usar, despues pongan la suya que se sacaron mejor nota...
	//init allegro
	srand(time(NULL)); //randoms;
	...
	...
	if(modo == MODE1)
	{
		Graphics g;
		Simulacion S(arg_rob, arg_ancho, arg_largo, &g)		//los que dicen arg representan argumentos
		S.startGraphing();
		while(!S.nextSimulationStep());
		cout << "tardo" << S.getTickCount() << endl;

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
	return EXIT_SUCCESS;
}

#endif	//WIN32