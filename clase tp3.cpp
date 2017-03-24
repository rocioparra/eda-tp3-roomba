malloc() --> new  //blado = new bool[ancho * alto]  //int * i = new int; 
free() --> delete //delete baldo[] // delete i;
//Robot.h
class Robot
{
private:
	Point p; //class Point {public: double x; double y;};
	double angle;
	uint xmax, ymax;
public:
	void moveRobotToPoint(const Point& p);
	void moveRobot();
	void Robot(uint _xmax, uint _ymax); //-> moveRobotToPoint(randomPoint);  xmax = _xmax; ymax=_ymax;
	double getX();
	double getY();
};

void graf ()
{
	al_draw_bitmap(robotImg, r[0].getX() *tamañoxbaldosa, r[0].getY() * tamañoydebaldosa);
}

//Piso.h
class Piso
{
private:
	bool * baldo; //Arreglo de baldosas
	int ancho;
	int alto;
public:
	void Piso(uint ancho, uint alto);
	bool isDirty();
	void cleanTile(uint _x, uint _y);
	bool getTileState(uint _x, uint _y);
	void destroy ();
	bool isValid(); //para chequear si el contructor se hizo bien;

};

//Simulacion.h

#include "Robot.h"
#include "Piso.h"
#include "Graphics.h"

class Simulacion 
{
private:
	uint robotCount;
	unsigned long ticks;
	Piso p();
	Robot * r;
	bool wantToGraphic;
	Graphics * graph;
public:
	Simulacion(uint _robotCount, uint _width, uint _height, Graphics * _graph = NULL);
	bool nextSimulationStep(); //if finished --> true
	unsigned long getTickCount();
	uint getRobotCount();
	uint getFloorWidht();
	uint getFloorHeight();
	void startGraphing();
	void stopGraphing();
	bool amIgraphing();
};



//Simulacion.cpp

#include "Simulacion.h"
#define EXIT_SUCCESS	0

Simulacion::Simulacion(uint _robotCount, uint _width, uint _height, Graphics * _graph = NULL)
{
	r = new Robot (_width, _height) [_robotCount];
	p= new Piso(_width,_height);
	if(p.isValid() && (r != NULL))
	{}
	else
	{
		delete r[];
		p.destroy();
	}
}

//main.cpp


int main (int argc, char * argv[])
{
	//valid params
	//init allegro
	srand(time(NULL)); //randoms;
	...
	...
	if(modo == 1)
	{
		Graphics g;
		Simulacion S(arg_rob, arg_ancho, arg_largo, &g)
		S.startGraphing();
		while(!S.nextSimulationStep());
		cout << "tardo" << S.getTickCount() << endl;

	}
	else if (modo == 2)
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
		destruirrrrrr;;;
	}
	return EXIT_SUCCESS;
}