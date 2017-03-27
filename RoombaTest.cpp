#include <iostream> 
#include "mainTest.h"

using namespace std;

#define TEST_NUMBER		16	// Cantidad de tests en esta base de pruebas.
#define MAX_ARGC		9	// Valor maximo que se utilizara en los tests para argc.
#define	MAX_ARG_LEN		10	// Long. max. de cada argumento incluido en los tests.

/* Estructura parserTest_t: informacion de cada uno de los tests que se realizaran */
typedef unsigned int uint;
typedef struct
{
	int argc;							// argc no debe tener errores, no es generado por el usuario
	char * argv[MAX_ARGC];	// El primer elemento corresponderia al nombre del archivo, se ignorara
	int shouldReturn;				// opciones + parametros
}test_t;


int main (void)
{
	uint i,j;
	int parsedArgs;


	test_t test[TEST_NUMBER] =
	{
		{9, { {NULL}, {"-Modo"}, {"2"}, {"-Width"}, {"5"}, {"-Height"}, {"5"}, {"-Robots"}, {"10"} }, 0 },	//CORRECTO	
		{9, { {NULL}, {"-Modo"}, {"2"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, 0 },	//CORRECTO
		{9, { {NULL}, {"-Modo"}, {"3"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//modo no puede ser 3
		{9, { {NULL}, {"-Modo"}, {"0"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//modo no puede ser 0
		{9, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"-3"} }, -1 },	//no puede ser menor que 0
		{9, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"0"}, {"-Robots"}, {"10"} }, -1 },	//no puede ser 0
		{9, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4.8"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//no puede ser float
		{7, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"8"} }, 0 },						//falta robots
		{7, { {NULL}, {"-Modo"}, {"2"}, {"-Width"}, {"4"}, {"-Height"}, {"8"} }, 0 },						//modo 2, puede no estar robots
		{7, { {NULL}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, 0 },						//falta modo
		{7, { {NULL}, {"-Modo"}, {"1"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, 0 },						//falta width
		{7, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Robots"}, {"10"} }, 0 },						//falta height
		{9, { {NULL}, {"-Modo"}, {"fgh"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//no es int
		{9, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"dfg"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//no es int
		{9, { {NULL}, {"-godo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//no es valido
		{9, { {NULL}, {"Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} },-1 },	//param
//16 TESTS
	};

	for (i = 0; i<TEST_NUMBER; i++)				// Se recorre la totalidad el arreglo de tests.
	{
		cout << "TEST " << i+1 << endl << "Command line: ";

		for (j = 1; j < test[i].argc; j++)
		{
			cout << test[i].argv[j] << " ";			//Imprimir la linea que se procesara.
		}
		cout << endl;

		parsedArgs = main2(test[i].argc, &(test[i].argv[0]));		

		if (parsedArgs != test[i].shouldReturn)
		{
			cout << "Error: parser returned " << parsedArgs << " when " << test[i].shouldReturn << " was expected" << endl;
		}
		else
		{
			cout << "Returned expected value (" << parsedArgs << ")" << endl;
		}

		cout << endl << "Press ENTER to continue..." << endl;
		system("pause");
		cout << endl << endl;

	}

	return 0;
}

/*

int main (void)
{
	uint i,j;
	int parsedArgs;
	RoombaArgs r;

	parserTest_t test[TEST_NUMBER] =
	{
		{9, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, 4 },	//CORRECTO	
		{9, { {NULL}, {"-Modo"}, {"2"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, 4 },	//CORRECTO
		{9, { {NULL}, {"-Modo"}, {"3"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//modo no puede ser 3
		{9, { {NULL}, {"-Modo"}, {"0"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//modo no puede ser 0
		{9, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"-3"} }, -1 },	//no puede ser menor que 0
		{9, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"0"}, {"-Robots"}, {"10"} }, -1 },	//no puede ser 0
		{9, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4.8"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//no puede ser float
		{7, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"8"} }, 3 },						//falta robots
		{7, { {NULL}, {"-Modo"}, {"2"}, {"-Width"}, {"4"}, {"-Height"}, {"8"} }, 3 },						//modo 2, puede no estar robots
		{7, { {NULL}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, 3 },						//falta modo
		{7, { {NULL}, {"-Modo"}, {"1"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, 3 },						//falta width
		{7, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Robots"}, {"10"} }, 3 },						//falta height
		{9, { {NULL}, {"-Modo"}, {"fgh"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//no es int
		{9, { {NULL}, {"-Modo"}, {"1"}, {"-Width"}, {"dfg"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//no es int
		{9, { {NULL}, {"-godo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//no es valido
		{9, { {NULL}, {"Modo"}, {"1"}, {"-Width"}, {"4"}, {"-Height"}, {"8"}, {"-Robots"}, {"10"} }, -1 },	//param
//16 TESTS
	};

	for (i = 0; i<TEST_NUMBER; i++)				// Se recorre la totalidad el arreglo de tests.
	{
		cout << "TEST " << i+1 << endl << "Command line: ";

		for (j = 1; j < test[i].argc; j++)
		{
			cout << test[i].argv[j] << " ";			//Imprimir la linea que se procesara.
		}
		cout << endl;

		parsedArgs = parseCmdLine(test[i].argc, &(test[i].argv[0]), r.getCallback(), &r);		
		//parseCmdLine deberia devolver test[i].parserShouldReturn, que es la cantidad de 
		// argumentos procesados,o -1 si hubo un error

		if (parsedArgs != test[i].parserShouldReturn)
		{
			cout << "Error: parser returned " << parsedArgs << " when " << test[i].parserShouldReturn << " was expected" << endl;
		}
		else
		{
			cout << "Parser returned expected value (" << parsedArgs << ")" << endl;
		}

		cout << "Content received:" << endl;
		cout << "width = " << r.getWidth() << endl; 
		cout << "height = " << r.getHeight() << endl; 
		cout << "robots = " << r.getRobotN() << endl; 
		cout << "mode = " << r.getMode() << endl; 
		
		cout << endl << "Press ENTER to continue..." << endl;
		system("pause");
		cout << endl << endl;

		r.setHeight(0); r.setMode(0); r.setWidth(0); r.setRobotN(0);
		//volver a params. init.
	}

	return 0;
}

*/