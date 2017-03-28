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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define FONTSIZE 20

class GraphicMode2
{
private:
    ALLEGRO_DISPLAY* display;   
    ALLEGRO_FONT* defaultFont;    
    Point origin;     //coordenada de origen del grafico
    uint32_t barWidth;
    uint32_t barAmount;
    uint32_t displayHeight;
    uint32_t displayWidth;
    float resizingFactor;
    bool valid;
    void drawBar(uint32_t barPosition, uint32_t barHeight);

public:
    GraphicMode2(uint32_t simRepetition); //inicializa allegro y calcula el tamanio de las barras
    void drawAllBars(double barValue[]); //dibuja todas las barras del grafico
    void showChanges(); //muestra lo dibujado en pantalla
    bool isValid();
};

#endif /* GRAPHICMODE2_H */
