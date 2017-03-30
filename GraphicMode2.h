#ifndef GRAPHICMODE2_H
#define GRAPHICMODE2_H

#include "Floor.h"
#include "Robot.h"
#include "Simulation.h"
#include "Point.h"
extern "C"{
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> 
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
}
#define FONTSIZE 20     //tamaño de letra usada para etiquetar los ejes y el maximo valor
#define DISPLAY_W 1200
#define DISPLAY_H 800

class GraphicMode2      //genera un grafico de barras 
{
private:
        ALLEGRO_DISPLAY* display;
        ALLEGRO_FONT* defaultFont;
        Point origin;                   //coordenada de origen del grafico
        uint32_t barWidth; 
        uint32_t barAmount;             
        uint32_t displayHeight;
        uint32_t displayWidth;
        float resizingFactor;           //modificacion de tamñano de las barras para que no se excedan del display
        bool valid;                     //true: no hubo error. false: hubo error.
        void drawBar(uint32_t barPosition, uint32_t barHeight); //dibuja una barra en el grafico

public:
        GraphicMode2(uint32_t simRepetition); //inicializa allegro y calcula el tamanio de las barras
        void drawAllBars(double barValue[]); //dibuja todas las barras del grafico
        void showChanges(); //muestra lo dibujado en pantalla
        bool isValid(); //indica si hubo error o no en el constructor
		void destructor();
};

#endif /* GRAPHICMODE2_H */
