#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Floor.h"
#include "Robot.h"
#include "Simulation.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#define SCREENSIZE 600  //ancho y alto del display

typedef unsigned int uint;

class Graphics
{

private:
    ALLEGRO_DISPLAY* display = NULL;    
    ALLEGRO_BITMAP* robotBitmap = NULL;
    uint tileSide = 0;  //lado de una baldosa (son cuadradas)

public:
    Graphics(uint xTiles, uint yTiles);     //inicializa allegro y calcula el tamanio de las baldosas
    drawRobot(Point center, double angle);  //dibuja un robot en el punto center con el angulo angle
    drawFloor(bool* tiles);                 //dibuja el piso con los colores correspondientes a sucio y limpio
    showChanges();                          //muestra lo dibujado en pantalla
}

#endif /* GRAPHICS_H */