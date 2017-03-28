#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Point.h"
#include <stdint.h>
#include <stdio.h>
#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#define MAXTILESIDE 200    //maximo medida que puede tomar el lado de una baldosa
#define ROBOT_SPRITE "Travolta.png"
#define ROBOT_SPRITE_SIDE 160.0   //tamanio del lado del sprite delrobot
#define ROBOT_TILE_RATIO 1.0    //relacion entre el lado de la baldosa y el lado del robot (baldosa/robot)


class Graphics
{
private:
    ALLEGRO_DISPLAY* display;    
    uint32_t tileSide;              //lado de una baldosa (son cuadradas)
    uint32_t displayHeight;
    uint32_t displayWidth;
    bool valid;     //si hubieron errores en el constructor, es false.
    float resizingFactor;   //valor utilizado para ajustar el tamanio del sprite del robot
    Point getTileCorner(uint32_t i, uint32_t j);            //recibe fila y columna de la baldosa, devuelve el punto de la esquina superior derecha
    ALLEGRO_COLOR getTileColor(Point tileCorner);   //recibe la esquina de la tile y devuelve un color

public:
    ALLEGRO_BITMAP* robotBitmap;
    Graphics(uint32_t xTiles, uint32_t yTiles);          //inicializa allegro y calcula el tamanio de las baldosas
    void drawRobot(float xCenter, float yCenter, double angle);  //dibuja un robot en el punto center con el angulo angle
    void drawFloor(bool* tiles, int32_t i, int32_t j);   //dibuja el piso con los colores correspondientes a sucio y limpio
    void showChanges();                          //muestra lo dibujado en pantalla
    bool isValid();
};
#endif /* GRAPHICS_H */
    