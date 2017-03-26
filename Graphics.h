#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include "Floor.h"
#include "Robot.h"
#include "Simulation.h"
#include "Point.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#define TILESIDE 30 //lado de las baldosas, son cuadradas
#define ROBOT_SPRITE "Travolta.png"

typedef unsigned int uint;

class Graphics
{
public:
    ALLEGRO_BITMAP* robotBitmap;
    Graphics(uint xTiles, uint yTiles);          //inicializa allegro y calcula el tamanio de las baldosas
    void drawRobot(Point center, double angle);  //dibuja un robot en el punto center con el angulo angle
    void drawFloor(bool* tiles, int i, int j);   //dibuja el piso con los colores correspondientes a sucio y limpio
    void showChanges();                          //muestra lo dibujado en pantalla
private:
    ALLEGRO_DISPLAY* display;    
    uint tileSide;              //lado de una baldosa (son cuadradas)
    uint displayHeight;
    uint displayWidth;
    Point getTileCorner(uint i, uint j);            //recibe fila y columna de la baldosa, devuelve el punto de la esquina superior derecha
    ALLEGRO_COLOR getTileColor(Point tileCorner);   //recibe la esquina de la tile y devuelve un color

};
#endif /* GRAPHICS_H */