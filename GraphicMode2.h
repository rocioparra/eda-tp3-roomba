#ifndef GRAPHICMODE2_H
#define GRAPHICMODE2_H

#include <stdio.h>      //ACA HAY BOCHA DE INCLUDES AL PEDO 
#include "Floor.h"
#include "Robot.h"
#include "Simulation.h"
#include "Point.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

class GraphicMode2
{
private:
    ALLEGRO_DISPLAY* display;    
    Point origin;     //coordenada de origen del grafico
    uint barWidth;
    uint barAmount;
    uint displayHeight;
    uint displayWidth;
    bool valid;
    void drawBar(uint barPosition, uint barHeight);

public:
    GraphicMode2(uint simRepetition); //inicializa allegro y calcula el tamanio de las barras
    void drawAllBars(ulong barValue[]); //dibuja todas las barras del grafico
    void showChanges(); //muestra lo dibujado en pantalla
    bool isValid();
};

#endif /* GRAPHICMODE2_H */
