#include <iostream>
#include <chrono>
#include <string>
#include <cstdint>

#include "Simulation.h"
#include "Graphics.h"
#include "GraphicMode2.h"
#include "myAudio.h"

extern "C" {
#include "parseCmdLine.h"
#include "moreString.h"

}



#define SHOW_ONCE	1
#define AVERAGE		2

// CONSTANTES MODO 2:
#define CICLES		1000	//numero de veces que repite la simulacion para calcular el promedio de ticks 
#define MAX_ROBOTS	100		//maximo numero de robots para el que se calcula el promedio de ticks 
#define MIN_DIFF	0,1		//minima diferencia que debe haber entre dos promedios consecutivos para seguir calculando promedios

#define N_AUDIO_SAMPLES	1

#define DEBUG
#ifdef DEBUG
#include "mainTest.h"
#endif

using namespace std;

int32_t check (char * _key, char * _value, void * userData);

typedef struct {
	uint32_t width;
	uint32_t height;
	uint32_t mode;
	uint32_t robotN;
} userData_t;

int32_t main (int32_t argc, char * argv[])
{
	userData_t ud = {0, 0, 0, 0};

	srand(time(NULL));
	if((parseCmdLine(argc, argv, check, &ud)) == PARSER_ERROR) {
		cout << "ERROR en el pasaje de parametros! Abort!" << endl;
		return -1;
	}

	if( !ud.height || !ud.width || (!ud.robotN && ud.mode == SHOW_ONCE) )
		ud.mode = 0;


	if(ud.mode == SHOW_ONCE) {
		Graphics g(ud.width, ud.height);
                if ( !g.isValid() ) {
			cout << "Error: allegro was not properly initialized" << endl;
			return -1;
		}
                MyAudio a(N_AUDIO_SAMPLES);
                sampleID bgMusic = a.loadSample("DiscoMusic.wav");
		Simulation s(ud.robotN, ud.width, ud.height, &g);

		if( bgMusic == NULL ) {
			cout << "Error: could not load audio sample" << endl;
			return -1;
		}
		else if ( !s.isValid() ) {
			cout << "Error: parameters exceeded the maximum (width <= 100, height <=70)" << endl;
			return -1;
		}
		
		a.playSampleLooped(bgMusic);

		while(!s.nextSimulationStep());
                
		a.stopSamples();
		g.showTickCount(s.getTickCount());
		s.destroy();
        g.destructor();
	}

	else if (ud.mode == AVERAGE) {
		double meanTicks[MAX_ROBOTS];				//promedios
		uint32_t n, i;								//contadores: robots, ciclos
		memset(meanTicks, 0, sizeof(meanTicks));	//inicializo todo el arreglo en 0

		for (n = 0; n < MAX_ROBOTS && ( n>1 && meanTicks[n-2] - meanTicks[n-1] > MIN_DIFF); n++) {
			for(i = 0; i < CICLES; i++)	{
				Simulation s(n+1, ud.width, ud.height);
				if ( !s.isValid() ) {
					cout << "Error: parameters exceeded the maximum (0<width<=100"
						 <<", 0<height <=70, 0<robots, mode = 1 or mode =2)" << endl;
					return -1;
				}
				
				while(!s.nextSimulationStep());
				meanTicks[n] += double (s.getTickCount());
				s.destroy();
			}

			meanTicks[n]/=CICLES;
		}

		GraphicMode2 g(n);
		if ( !g.isValid() ) {
			cout << "Error: allegro was not properly initialized" << endl;
			return -1;
		}

		g.drawAllBars(meanTicks);
		g.showChanges();
                al_rest(5.0);
	}
	else {
		cout << "Error: invalid or insufficient parameters. Keep in mind that:"	<< endl
			 << "- all parameters must be positive integers"					<< endl
			 << "- Mode can only be 1 (show once) or 2 (mean average)"			<< endl
			 << "- Robots must be explicit for mode 1"							<< endl
			 << "- Width, Height and Mode must always be explicit"				<< endl;
		return -1;
	}

	return EXIT_SUCCESS;
}

int32_t check (char * _key, char * _value, void * userData)
{
	if (_key == NULL || _value == NULL || userData == NULL)		//el programa roomba solo recibe opciones como argumento
		return false;

	int32_t isUInt;

	uint32_t valueNumber = getUnsInt(_value, &isUInt);
	if ( !isUInt || valueNumber == 0 )					//verificar que se la conversion se hizo bien y que el value no era 0												
		return false;				//como todos los values de este programa son uints > 0 , si es otra cosa es error
									//notese que la func. strtol devolvera 0 si no habia un int

	string key(_key);										//pasar a string por simplicidad en el codigo
	userData_t * ud = (userData_t *) userData;				
	int32_t status = false;							//status cambiara a true si se verifica que se recibio algo valido

	//	Se procede a verificar que la key sea una de las validas y a guardar el valor donde corresponda.
	//  El control de cuales son los parametros maximos que se puede recibir lo hara la simulacion, esta
	//funcion solo verifica que los numeros sean mayores a 0 y que el modo sea valido.

	if (key == "Width") {
		ud->width = valueNumber;
		status = true;
	}

	else if (key == "Height") {
		ud->height = valueNumber;
		status = true;
	}

	else if (key == "Robots") {
		ud->robotN = valueNumber;
		status = true;
	}

	else if (key == "Modo") {				
		if ( valueNumber <=2 ) { //modo puede ser solo 1 o 2
			ud->mode = valueNumber;
			status = true;
		}
	}

	return status;
}