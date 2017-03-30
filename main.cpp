/*	

	Instituto Tecnológico de Buenos Aires
	22.08 - Algoritmos y estructura de datos

	Trabajo práctico n° 3: Robots

	Autores:	Díaz, Ian Cruz				- legajo 57.515
				Parra, Rocío				- legajo 57.669
				Stewart Harris, María Luz	- legajo 57.676

	Fecha de entrega: jueves 30 de marzo de 2017

*/
	



#include <iostream>
#include <chrono>
#include <thread>
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


// MODOS: show once muestra una simulacion graficamente, average muestra un grafico del promedio de ticks para un piso con
// distintos numeros de robots
#define SHOW_ONCE	1
#define AVERAGE		2

// CONSTANTES MODO 2:
#define CICLES		1000	//numero de veces que repite la simulacion para calcular el promedio de ticks 
#define MAX_ROBOTS	100		//maximo numero de robots para el que se calcula el promedio de ticks 
#define MIN_DIFF	0.1		//minima diferencia que debe haber entre dos promedios consecutivos para seguir calculando promedios

#define N_AUDIO_SAMPLES	1	//cuantas pistas de audio se utilizan en este programa (solo la musica de fondo)


using namespace std;

int32_t check (char * _key, char * _value, void * userData);	//predeclaracion: callback para el parser

//donde se guardaran los datos recibidos por linea de comando
typedef struct {
	uint32_t width;
	uint32_t height;
	uint32_t mode;
	uint32_t robotN;
} userData_t;


int32_t main(int32_t argc, char * argv[])
{
	srand(time(NULL));
	userData_t ud = {0, 0, 0, 0};
	//datos recibidos por el usuario: todo debe empezar en 0, que no es un dato valido para
	//ninguna opcion, ya que despues sabemos que no se recibio un dato si sigue en 0
		
	if((parseCmdLine(argc, argv, check, &ud)) == PARSER_ERROR) { 
		//si no se reciben datos validos por linea de comando, no se puede continuar
		cout << "Invalid parameters. Keep in mind that:"						<< endl
			 << "- all parameters must be positive integers"					<< endl
			 << "- Mode can only be 1 (show once) or 2 (mean average)"			<< endl;
		return -1;
	}

	if( !ud.height || !ud.width || (!ud.robotN && ud.mode == SHOW_ONCE) )
	// si no se recibieron las medidas del piso, o si no se recibieron los robots para el modo 1,
	// no se puede realizar la simulacion. al quedar el modo en 0, se avanzara a la parte de error
		ud.mode = 0;


	if(ud.mode == SHOW_ONCE) { //MODO 1
		Graphics g(ud.width, ud.height);					//inicializar la parte grafica
      
		if ( !g.isValid() ) {
			cout << "Error: allegro was not properly initialized" << endl;
			return -1;
		}

		MyAudio a(N_AUDIO_SAMPLES);							//inicializar el audio
        sampleID bgMusic = a.loadSample("DiscoMusic.wav");	//cargar la musica de fondo
		Simulation s(ud.robotN, ud.width, ud.height, &g);	//inicializar la simulacion

		if( bgMusic == NULL ) {
			cout << "Error: could not load audio sample" << endl;
			g.destructor();
			return -1;
		}
		else if ( !s.isValid() ) {
			cout << "Error: parameters exceeded the maximum (width <= 100, height <=70)" << endl;
			g.destructor();
			a.destructor();
			return -1;
		}
		
		a.playSampleLooped(bgMusic);		//encender la musica de fondo

		while(!s.nextSimulationStep());		//realizar y mostrar la simulacion
                
		g.showTickCount(s.getTickCount());	//pop-up que indica los ticks

		s.destroy();						//destruir todo
		a.stopSamples();
		g.destructor();
		a.destructor();
	}

	else if (ud.mode == AVERAGE) {    //MODO 2
		double meanTicks[MAX_ROBOTS];				//promedios
		uint32_t n, i;								//contadores: robots, ciclos
		memset(meanTicks, 0, sizeof(meanTicks));	//inicializo todo el arreglo en 0

		for (n = 0; n < MAX_ROBOTS && ( n<=1 || (meanTicks[n-2] - meanTicks[n-1] > (double)MIN_DIFF)); n++) {
		//se prueba desde 1 robot a 100 robots, o hasta que los promedios den casi lo mismo para dos
		//numeros de robots consecutivos
			cout << "Simulating "<< n+1 << " robots"<< endl;

			for(i = 0; i < CICLES; i++)	{
			//para cada numero de robots, simular 1000 veces
				Simulation s(n+1, ud.width, ud.height);
				if ( !s.isValid() ) {
					cout << "Error: parameters exceeded the maximum (0<width<=100"
						 <<", 0<height <=70, 0<robots, mode = 1 or mode =2)" << endl;
					return -1;
				}
				
				while(!s.nextSimulationStep());	//realizar la simulacion (no muestra nada)
				meanTicks[n] += double (s.getTickCount());	//va sumando los ticks 
				s.destroy();
			}
			meanTicks[n]/=CICLES;	//obtiene el promedio de ticks de las simulaciones hechas 
		}

		GraphicMode2 g(n);
		if ( !g.isValid() ) {
			cout << "Error: allegro was not properly initialized" << endl;
			return -1;
		}

		g.drawAllBars(meanTicks);	//grafica los resultados obtenidos
		g.showChanges();
		this_thread::sleep_for(chrono::seconds(5));	//muestra los resultados por 5 segundos
		g.destructor();
	}
	else { //parametros no validos
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

	else if (key == "Mode") {				
		if ( valueNumber <=2 ) { //modo puede ser solo 1 o 2
			ud->mode = valueNumber;
			status = true;
		}
	}

	return status;
}