#include "GraphicMode2.h"

GraphicMode2::GraphicMode2(uint32_t simRepetition) //inicializa allegro y calcula el tamanio de las barras
{
	valid = true;
	if(!al_init()) 
	{
		valid = false;
	}
	if(!al_init_primitives_addon())
	{
		valid = false;
	}
	if(!al_init_image_addon())
	{
		valid = false;
		al_shutdown_primitives_addon();
	}
	al_init_font_addon();
	al_init_ttf_addon();
        
	displayWidth = 600;     //BORRAR MAGIC NUMBER
	displayHeight = 600;     //BORRAR MAGIC NUMBER
        
	display = al_create_display(displayWidth, displayHeight);
	if(!display)
	{
		valid = false;
		al_shutdown_primitives_addon();
		al_shutdown_image_addon();
	}
        
	defaultFont = al_load_ttf_font("defaultFont.ttf", FONTSIZE,0 );
	if (!defaultFont)
	{
		valid = false;
		al_shutdown_primitives_addon();
		al_shutdown_image_addon();
	}
        
	origin.setX(displayWidth*0.125);        //MAGIC NUMBERS????????????????????????????????
	origin.setY(displayHeight*0.875);
        
	al_draw_line(origin.getX(), origin.getY(), origin.getX(), origin.getY()-displayHeight*0.75, al_map_rgb(255,255,255), 2); //dibuja eje vertical
	al_draw_line(origin.getX(), origin.getY(), origin.getX()+displayWidth*0.75, origin.getY(), al_map_rgb(255,255,255), 2); //dibuja eje horizontal       
	barAmount = simRepetition;
	barWidth = displayWidth*0.75/(simRepetition + 1); //se agrega uno mas para dejar lugar entre la ultima barra y el fin de la linea
}
void GraphicMode2::drawAllBars(double barValue[]) //dibuja todas las barras del grafico
{
	resizingFactor = (displayHeight*0.75)/barValue[0];
	char maxValueA[6]; //arreglo para guardar el ascii del maximo valor
 //       snprintf( maxValueA, sizeof(maxValueA), "%f", barValue[0] );
        
	al_draw_text(defaultFont, al_map_rgb(255,255,255), origin.getX(), origin.getY()-displayHeight*0.75, ALLEGRO_ALIGN_RIGHT, "CAMBIAR ESTO");

	for(uint32_t i = 0; i < barAmount; i++)
	{
		drawBar(i, barValue[i]);
	}
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
