#include "parseCmdLine.h"
#include <stdio.h>


////////////////////////parseCmdLine//////////////////////////////
//																
//  parseCmdLine va analizando los argumentos ingresados.		
//  Si el argumento comienza con '-' lo manda a parseCallback	
//  como OPCION. De lo contrario lo manda como PARAMETRO.		
//																
//////////////////////////////////////////////////////////////////

int parseCmdLine(int argc, char *argv[], pCallback p, void *userData)
{
	int i = 1, parsedArgs = 0;							// i : indice para el arreglo de argumentos.
	bool status = true;									// status: flag de error.
	 													// parsedArgs: contador de argumentos procesados.
	 																	    

	while ( i < argc && status == true )	// El ciclo se ejecuta hasta procesar todos los argumentos o que haya un error.
     {   
       	if( (*(argv[i]) ) == '-' )			// Deteccion del comienzo de una opcion.
       	{  
			if (*((argv[i])+1) != 0 && i+1 < argc )				// Verificar que haya una clave y un valor.
			{
				status = p((argv[i]) + 1, argv[i+1], userData);	// Verificar contenido.
				i++;												
				parsedArgs++;
			}
			else
			{
				status = false;
			}
       	}
       	else
       	{
           	status=p(NULL, argv[i], userData);		// Los parametros solo pueden tener errores de contenido.
			parsedArgs++;							
       	}

		i++;
    }
    
	if (status == false)
	{
		parsedArgs = -1;	//si hubo error, indicarlo al programa
	}


    return parsedArgs;
}
