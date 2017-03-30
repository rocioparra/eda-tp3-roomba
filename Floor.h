#ifndef FLOOR_H
#define FLOOR_H
#include <cstdint>

/*	

	Instituto Tecnológico de Buenos Aires
	22.08 - Algoritmos y estructura de datos

	Trabajo práctico n° 3: Robots

	Autores:	Díaz, Ian Cruz				- legajo 57.515
				Parra, Rocío				- legajo 57.669
				Stewart Harris, María Luz	- legajo 57.676

	Fecha de entrega: jueves 30 de marzo de 2017

***********************************************************************************************************

	Clase: Floor
	
	Los objetos de esta clase consisten en un piso, con un cierto numero de baldosas de ancho y de largo.
	Cada baldosa puede estar limpia (1) o sucia (0).
	
*/


class Floor
{
private:
	bool * tile;		//arreglo de baldosas
	uint32_t width;		//dimensiones del arreglo
	uint32_t height;
public:
  
	Floor(uint32_t _width, uint32_t _height);
	//las medidas deben explicitarse. inicializa todo como false, que indica sucio

	bool isValid(); //para chequear si el contructor se hizo bien

	bool getTileState(uint32_t i, uint32_t j);
	/*	getTileState:
		devuelve el estado de la baldosa especificada (fila i, columna j)
		el estado puede ser limpio o sucio, indicado por true y false respectivamente
		de haberse recibido valores de i o j no validos, tambien devuelve false
	*/

	bool * getFloor();	//devuelve puntero al arreglo de bools que representa el piso
	uint32_t getWidth();	//devolver las medidas del piso
	uint32_t getHeight();	//si no se pudo inicializar, esas medidas van a ser 0

	bool isDirty();
	//devuelve true si hay al menos una baldosa sucia, false si todas estan limpias
	//si se trato de usar para un piso que no se habia podido inicializar, tambien devuelve false

	void cleanTile(uint32_t i, uint32_t j);
	//limpia la baldosa especificada, a menos que se reciban valores de i o j (fila, columna) no validos,
	//en cuyo caso no hara nada

	void destroy ();
	//libera la memoria utilizada por el piso
};

#endif //FLOOR_H
