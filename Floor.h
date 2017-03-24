#ifndef FLOOR_H
#define FLOOR_H

class Floor
{
  private:
	bool * tile;		//arreglo de baldosas
	unsigned int width;	//dimensiones del arreglo
	unsigned int height;

  public:
	Floor(unsigned int _width, unsigned int _height);
	//las medidas deben explicitarse. inicializa todo como false, que indica sucio

	bool isValid(); //para chequear si el contructor se hizo bien

	bool getTileState(unsigned int i, unsigned int j);
	/*	getTileState:
		devuelve el estado de la baldosa especificada (fila i, columna j)
		el estado puede ser limpio o sucio, indicado por true y false respectivamente
		de haberse recibido valores de i o j no validos, tambien devuelve false
	*/

	unsigned int getWidth();	//devolver las medidas del piso
	unsigned int getHeight();	//si no se pudo inicializar, esas medidas van a ser 0

	bool isDirty();
	//devuelve true si hay al menos una baldosa sucia, false si todas estan limpias
	//si se trato de usar para un piso que no se habia podido inicializar, tambien devuelve false

	void cleanTile(unsigned int i, unsigned int j);
	//limpia la baldosa especificada, a menos que se reciban valores de i o j (fila, columna) no validos,
	//en cuyo caso no hara nada

	void destroy ();
	//libera la memoria utilizada por el piso
};

#endif //FLOOR_H