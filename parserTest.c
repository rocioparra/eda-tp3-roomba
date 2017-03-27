extern "C" {
#include "parseCmdLine.h"
}
#include <stdio.h>
#include <string.h>
#include <time.h>


#define TEST_NUMBER		10	// Cantidad de tests en esta base de pruebas.
#define MAX_ARGC		21	// Valor maximo que se utilizara en los tests para argc.
#define	MAX_ARG_LEN		20	// Long. max. de cada argumento incluido en los tests.


/* Codigos de error de la funcion parseCmdLine() y del callback que utiliza */
#define PARSER_ERROR	-1
#define CALLBACK_ERROR	 0
#define CALLBACK_OK		 1

/* Predeclaracion*/
int testCallback(char * key, char * value, void * userData); 



/* Estructura parserTest_t: informacion de cada uno de los tests que se realizaran */
typedef struct
{
	int argc;					// argc no debe tener errores, no es generado por el usuario
	char * argv[MAX_ARGC-1];	// El primer elemento corresponderia al nombre del archivo, se ignorara
	int parserShouldReturn;		// opciones + parametros
	char * explanation;			// Que se esta testeando?
}parserTest_t;


/*Estructura userData_t: donde el callback guardara los datos recibidos por el parser */
typedef struct
{
	int counter;				// Registro de que opcion/parametro se esta procesando.
	char * key[MAX_ARGC-1];		// Clave de la opcion, o NULL si es un parametro.
	char * value[MAX_ARGC-1];	// Valor de la opcion o parametro.

}userData_t;





int main(void)
{
	userData_t ud ;		// Estructura donde el callback guardara lo que reciba del parser.

	int parsedArgs, i, j, key;  	//  i, j: indices.
									//  parsedArgs: recibira el resultado del parser.
									//  key: vacia el buffer del getchar.

	int wrong_test[TEST_NUMBER+1] = { 0 }; 	
	/* wrong_test[0]: cantidad de tests que salieron mal.
	 * wrong_test[i], i>=wrong_test[0]: numero de test que salio mal (de existir) */

    time_t rawtime;					// Variables requeridas para generar el reporte.
    struct tm *timeinfo;
    char buffer[80];
    FILE *f;

    time(&rawtime);				// Obtener fecha y hora.
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "testReport(%d%B%Y-%Hhs%Mmin%Sseg).txt", timeinfo);

    f = fopen(buffer, "w");			// Archivo de reporte.

	parserTest_t test[TEST_NUMBER] = {
	/************************************* TESTS **********************************************/
	{ 2, { [1] = "-"}, -1 , "option with no key or value (format error)"},	
	{ 2, { [1] = "-valueMissing" }, -1 , "option with no value (format error)"},
	{ 3, { [1] = "-", "keyMissing" }, -1, "option with no key (format error)" },
	{ 1, .parserShouldReturn = 0, "no arguments"},
	{ 3, { [1] = "-theKey!!!", "-2%" }, 1, "value starting with '-'"},
	{ 3, { [1] = "--key", "20"}, 1, "key starting with '-'"},					
	{ 7, { [1] = "-key1", "val1", "par1", "-key2", "val2", "par2" }, 4, "multiple arguments" },
	{ 4, { [1] = "-key1", "val1", "nonValidParam" }, -1, "non-valid parameter" },
	{ 4, { [1] = "par1", "-key1", "nonValidVal" }, -1, "non-valid option value" },						
	{ 4, { [1] = "par2", "-nonValidKey", "val1" }, -1, "non-valid option key" }						
	/******************************************************************************************/
	};

	fprintf(f, "Reporte de Banco de Prueba\n\n");

	for (i = 0; i<TEST_NUMBER; i++)				// Se recorre la totalidad el arreglo de tests.
	{
		printf("\n\nTEST %d: %s \nCommand line: ", i + 1, test[i].explanation);
        fprintf(f, "\n\nTEST %d: %s \nCommand line: ", i + 1, test[i].explanation);

		for (j = 1; j < test[i].argc; j++)
		{
			printf("%s ", test[i].argv[j]);		//Imprimir la linea que se procesara.
			fprintf(f, "%s ", test[i].argv[j]);
		}

		putchar('\n');
		fputc('\n', f);

		ud.counter = 0;							// Reinicia el contador para el test actual.

		parsedArgs = parseCmdLine(test[i].argc, test[i].argv, testCallback, &ud);		
		/* parseCmdLine deberia devolver test[i].parserShouldReturn, que es la cantidad de 
		 * argumentos procesados,o -1 si hubo un error */

		if (parsedArgs != test[i].parserShouldReturn)
		{
			printf("Error: parser returned %d when %d was expected\n", parsedArgs, test[i].parserShouldReturn);
			fprintf(f, "Error: parser returned %d when %d was expected\n", parsedArgs, test[i].parserShouldReturn);
			//Indicar que lo devuelto por el parser no era lo que se esperaba.

			wrong_test[0]++;					// Incrementar contador de test incorrectos.
			wrong_test[wrong_test[0]] = i + 1; 	// Indicar cual fue el ultimo test que salio mal.
		}
		else
		{
			printf("Parser returned expected value (%d)\n", parsedArgs);
			fprintf(f, "Parser returned expected value (%d)\n", parsedArgs);
		}

		if (ud.counter > 0)	// Si se guardo algo, correcto o no, lo muestra por pantalla.
		{
			printf("Content received by the callback:\n");
			fprintf(f, "Content received by the callback:\n");

			for (j = 0; j < ud.counter; j++)
			{
				if (ud.key[j] == NULL)	// Mostrar parametros.
				{
					printf("%s (parameter)\n", ud.value[j]);
					fprintf(f, "%s (parameter)\n", ud.value[j]);
				}
				else                    // Mostrar opciones.
				{
					printf("-%s %s (option)\n", ud.key[j], ud.value[j]);
					fprintf(f, "-%s %s (option)\n", ud.key[j], ud.value[j]);
				}
			}
		}
		else
		{
			printf("Callback was not invoked\n");
			fprintf(f, "Callback was not invoked\n");
		}

		printf("\nPress ENTER to continue...");
		do
		{
			key = getchar();		// Esperar a que el usuario apriete enter.

		} while (key != '\n');		// Vaciar el buffer.
	}

	printf("\n\n");
	fprintf(f, "\n\n");

	if (wrong_test[0] != 0)	// Si hubo errores, indicar donde.
	{
		printf("ERRORS REGISTERED IN TEST/S: %d", wrong_test[1]);	
		fprintf(f, "ERRORS REGISTERED IN TEST/S: %d", wrong_test[1]);
		for (j = 2; j <= wrong_test[0]; j++)
		{
			printf(" - %d", wrong_test[j]);
			fprintf(f, " - %d", wrong_test[j]);
		}
	}
	else
	{
		fprintf(f, "All tests completed successfully.");		// Indicar que no hubo errores.
		printf("All tests completed successfully.");
	}

	printf("\n\nPress ENTER to finish.");
	do
	{
		key = getchar();	// Esperar a que el usuario apriete enter.

	} while (key !='\n');		// Vaciar el buffer.

    fclose(f);

	return 0;
}


int testCallback(char * key, char * value, void * userData)
{
	userData_t * ud = userData;

	int argVal = CALLBACK_OK;

	/* Guarda lo que recibe del parser en el elemento indicado por el contador*/
	ud->key[ud->counter] = key;
	ud->value[ud->counter] = value;
	ud->counter++;	//Avanzar el contador.


	/* Verificar que el parser interprete correctamente una indicacion de contenido no valido, tanto
     * para clave como para valor y parametro. Si lo recibido no es uno de los casos especificados a
	 * continuacion, siempre se devuelve que no hubo error */

	if (key != NULL)
	{
		if ( strcmp(key, "nonValidKey") == 0 )
		{
			argVal = CALLBACK_ERROR;
		}
	}
	if ( strcmp(value, "nonValidParam") == 0 || strcmp(value, "nonValidVal") == 0 )
	{
		argVal = CALLBACK_ERROR;
	}

	return argVal;
}


