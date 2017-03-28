#include "Graphics.h"
#include <stdint.h>

using namespace std;

Graphics::Graphics(uint32_t xTiles, uint32_t yTiles)
{
    valid = true;
    if(!al_init())
    {
        valid = false;
    }
    else if(!al_init_primitives_addon())
    {
        valid = false;
    }
    else if(!al_init_image_addon())
    {
    	al_shutdown_primitives_addon();
        valid = false;
    }
    
    if (valid)
        robotBitmap = al_load_bitmap("Travolta.png");
    
    if(robotBitmap == nullptr)
    {
        al_shutdown_primitives_addon();
        al_shutdown_image_addon();
        valid = false;
    }
    
    float screenResX = 1600, screenResY = 900;  //falta averiguar la resolucion del display en ejecucion  
    
    //tamanio de balosa: minimo entre ancho de pantalla/xTiles, alto de pantalla/ytiles, y el maximo establecido en MAXTILESIDE
    tileSide = min( min((uint32_t)(screenResX/xTiles),(uint32_t)(screenResY/yTiles)) , MAXTILESIDE);

    //constante por la cual hay que modificar el tamanio del sprite del robot en relacion al tamanio de las baldosas
    resizingFactor = (float)tileSide*ROBOT_TILE_RATIO/(float)al_get_bitmap_width(robotBitmap);
    
    if(valid)
        display = al_create_display(tileSide*xTiles, tileSide*yTiles);
    
    if(display == nullptr)
    {
        al_shutdown_primitives_addon();
        al_shutdown_image_addon();
        valid = false;
    }
}
void Graphics::drawFloor(bool* tiles, uint32_t xTiles, uint32_t yTiles)//podria no recibir yTiles pero se lo incluye por claridad
{   
    for( uint32_t j = 0; j < yTiles ; j++ )  //recorrer todas las filas
    {
        for( uint32_t i = 0; i < xTiles ; i++ )  //recorrer todas las columnas
        {
            Point corner = getTileCorner(i,j);
            
            if(tiles[ i*yTiles + j ] == true) //si esta limpia
                //dibujar la baldosa de color
                al_draw_filled_rectangle(corner.getX(), corner.getY(), corner.getX()+tileSide, corner.getY()+tileSide, getTileColor(corner));
            else    //si esta sucia
                //dibujar la baldosa de negro
                al_draw_filled_rectangle(corner.getX(), corner.getY(), corner.getX()+tileSide, corner.getY()+tileSide, al_map_rgb(0,0,0) );
           
            //dibujar un contorno negro alrededor de la baldosa
            al_draw_rectangle(corner.getX(), corner.getY(), corner.getX()+tileSide, corner.getY()+tileSide, al_map_rgb(0,0,0), 6 );
        }
    }
}
void Graphics::drawRobot(float xCenter, float yCenter, double angle)
{
    al_draw_scaled_rotated_bitmap( robotBitmap, al_get_bitmap_width(robotBitmap)/2, al_get_bitmap_height(robotBitmap)/2, xCenter*tileSide, yCenter*tileSide, resizingFactor, resizingFactor, angle, 0);
}
Point Graphics::getTileCorner(uint32_t i, uint32_t j) //devuelve un punto en la esquina superior izquierda de la baldosa
{
    Point corner;
    corner.setX(i*tileSide);
    corner.setY(j*tileSide);
    return(corner);
}
void Graphics::showChanges()
{
    al_flip_display();
}
ALLEGRO_COLOR Graphics::getTileColor(Point tileCorner)
{
    uint32_t i = tileCorner.getX(), j = tileCorner.getY();
    
    //dar valores semialeatorios que dependen de la posicion para que no cambien durate el programa
    //los valores de r, g, y b estan siempre entre 127 y 255, por lo que nunca se acercan a los valores
    //que deberian tener para parecer sucias 0
    return(al_map_rgb( 127 + (unsigned char)(i-100*j*j)/2 , 127 + (100*i*i - j)/2 , 127 + (100*i - 67*j)/2));
}
void Graphics::showTickCount(uint32_t tickCount)
{
    char tickCountA[100];       //arreglo para uardar el codigo ascii del tickCount
    snprintf( tickCountA, sizeof(tickCountA), "%d", tickCount );    //generar el string de tickCount
    
    al_show_native_message_box(
    NULL,
    "Fiebre de sabado por la noche",
    "Tu fiebre de sabado por la noche llego a los siguientes grados:",
    tickCountA,
    "close",
    ALLEGRO_MESSAGEBOX_OK_CANCEL);
}
bool Graphics::isValid()
{
    return valid;
}
void Graphics::destructor()
{
    al_destroy_bitmap(robotBitmap);
    al_destroy_display(display);
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
}
