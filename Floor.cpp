#include "Floor.h"
#include <cstdlib>

#define DEBUG

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

Floor :: Floor(uint _width, uint _height)
{
	tile = (bool *) calloc(_width*_height, sizeof(bool));	//reservar memoria para el piso, en 0

	if (tile == NULL) {
		width = 0;		//si hubo error, registrar que el piso no tiene medidas porque no existe
		height = 0;
	}
	else {
		width = _width;	//si el piso se pudo crear, guardar su tamano
		height = _height;
	}


}


bool Floor :: isValid()
{
	if (tile == NULL)	//verificar que malloc no haya devuelto NULL
		return false;
	else
		return true;
}


bool Floor :: getTileState(uint i, uint j)
{
	if (tile == NULL || i >= width || j >= height )   //verificar que malloc no haya devuelto NULL,
		return false;								//y que los parametros recibidos sean validos

	return tile[i*height+j];						//devolver el parametro pedido
}


bool * Floor :: getFloor()
{
	return tile;
}


uint Floor :: getWidth()
{
	return width;
}


uint Floor :: getHeight()
{
	return height;
}


bool Floor :: isDirty()
{
	if (tile == NULL)	//verificar que malloc no ha ya devuelto NULL
		return false;

	for (uint i = 0; i < width*height; i++)	//recorrer todo el piso
		if (tile[i] == false)
			return true;		//si encuentra una baldosa sucia, el piso esta sucio

	return false;				//si no encontro ninguna, el piso no esta sucio
}


void Floor :: cleanTile(uint i, uint j)
{
	if (tile == NULL || i >= width || j >= height ) //verificar que malloc no haya devuelto NULL,
		return;										//y que los parametros recibidos sean validos

	tile[i*height + j] = true;	//limpiar la baldosa
}


void Floor :: destroy ()
{
	free(tile);	//libera la memoria. si tile era NULL, no hace nada
}
