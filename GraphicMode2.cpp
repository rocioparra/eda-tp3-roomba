#include "GraphicMode2.h"
#include <stdio.h>

//inicializa allegro y calcula el tamanio de las barras.
//Recibe uint32_t simRepetition: cuántas veces se calculo el promedio de la duracion de la simulacion
GraphicMode2::GraphicMode2(uint32_t simRepetition)
{
	valid = true;
	//inicialiacion de allegro. Si alguna funcion de inicializacion devuelve error, 
	//se lo indica en la variable "Valid" y se llevan a cabo las funciones de finalizacion correspondientes.
	if(!al_init()) 
		valid = false;
	else if(!al_init_primitives_addon())
		valid = false;
	else if(!al_init_image_addon())
	{
		valid = false;
		al_shutdown_primitives_addon();
	}
        else
        {
                al_init_font_addon();
                al_init_ttf_addon();
        }
        
	displayWidth = DISPLAY_W;
	displayHeight = DISPLAY_H;
        
        
	//creacion del display
        if(valid)
                display = al_create_display(displayWidth, displayHeight);
	if(!display)
	{
		valid = false;
		al_shutdown_primitives_addon();
		al_shutdown_image_addon();
	}
        
	//cargar fuente
        if(valid)
                defaultFont = al_load_ttf_font("defaultFont.ttf", FONTSIZE,0 );
	if (!defaultFont)
	{
		valid = false;
		al_shutdown_primitives_addon();
		al_shutdown_image_addon();
	}
        
	//setear el origen del grafico
	origin.setX(displayWidth*0.125);        //MAGIC NUMBERS????????????????????????????????
	origin.setY(displayHeight*0.875);
        
	//dibuja ejes vertical y horizontal
        if(valid)
        {
                al_draw_line(origin.getX(), origin.getY(), origin.getX(), origin.getY()-displayHeight*0.75, al_map_rgb(255,255,255), 2); 
                al_draw_line(origin.getX(), origin.getY(), origin.getX()+displayWidth*0.75, origin.getY(), al_map_rgb(255,255,255), 2);
                barAmount = simRepetition;	//hay una barra por cada promedio
                barWidth = displayWidth*0.75/(simRepetition + 1); //se agrega uno mas para dejar lugar entre la ultima barra y el fin de la linea
        }
}
void GraphicMode2::drawAllBars(double barValue[]) //dibuja todas las barras del grafico
{
	//calcular que modificacion de tamaño se debe hacer para que la barra mas alta no se exceda del grafico
	resizingFactor = (displayHeight*0.75)/barValue[0]; 
	char maxValueA[6]; //arreglo para guardar el ascii del maximo valor
        snprintf( maxValueA, sizeof(maxValueA), "%f", barValue[0] );
      
	al_draw_text(defaultFont, al_map_rgb(255,255,255), origin.getX(), origin.getY()-displayHeight*0.75, ALLEGRO_ALIGN_RIGHT, maxValueA);
	al_draw_text(defaultFont, al_map_rgb(255,255,255), origin.getX(), origin.getY()-displayHeight*0.8, ALLEGRO_ALIGN_RIGHT, "ticks");
	al_draw_text(defaultFont, al_map_rgb(255,255,255), origin.getX()+displayWidth*0.75, origin.getY()+30, ALLEGRO_ALIGN_RIGHT, "travoltas");
	al_draw_text(defaultFont, al_map_rgb(255,255,255), displayWidth/2, origin.getY()-displayHeight*0.8, ALLEGRO_ALIGN_CENTER, "Promedio de ticks");

	for(uint32_t i = 0; i < barAmount; i++)	//dibujar cada barra
		drawBar(i, barValue[i]);
}
void GraphicMode2::showChanges() //muestra lo dibujado en pantalla
{
	al_flip_display();
}
void GraphicMode2::drawBar(uint32_t barPosition, uint32_t barHeight) //dibuja una barra del grafico
{
	al_draw_filled_rectangle( origin.getX() + barPosition * barWidth, origin.getY(),
                                  origin.getX() + (barPosition + 1) * barWidth, origin.getY() - barHeight*resizingFactor,
                                  al_map_rgb(255,255,80));
}
bool GraphicMode2::isValid()
{
	return valid;
}
