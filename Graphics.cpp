#include "Graphics.h"

Graphics::Graphics(uint xTiles, uint yTiles)
{
    if(!al_init()) {
//       fprintf(stderr, "failed to initialize allegro!\n");
//       return -1;
    }
    if(!al_init_primitives_addon()){
//      fprintf(stderr, "failed to initialize primitives!\n");
//	return -1;
    }
    if(!al_init_image_addon()){
    	al_shutdown_primitives_addon();
        //printf("aejh");
        //return -1;
    }
    
    tileSide = TILESIDE;    //preg: ES MEGA AL PEDO ESTA VARIABLE NO?
    displayWidth = tileSide*xTiles;
    displayHeight = tileSide*yTiles;
    
    display = al_create_display(displayWidth, displayHeight);
    if(!display){
       al_shutdown_primitives_addon();
//       fprintf(stderr, "failed to create display!\n");
//       return -1;
    } 
    al_clear_to_color(al_map_rgb(50,50,50));
    
    robotBitmap = al_load_bitmap("Travolta.png");
    if(robotBitmap == NULL)
        printf("no cargo bitmap\n");
}
Point Graphics::getTileCorner(uint i, uint j) //devuelve un punto en la esquina superior izquierda de la baldosa
{
    Point corner;
    corner.setX(i*tileSide);
    corner.setY(j*tileSide);
    return(corner);
}
ALLEGRO_COLOR Graphics::getTileColor(Point tileCorner)
{
    //da valores cualquiera a r, g y b.
//    unsigned char r = (unsigned char)(tileCorner.getY() * tileCorner.getY());
//    unsigned char g = (unsigned char)(tileCorner.getX() * tileCorner.getY());
//    unsigned char b = (unsigned char)(tileCorner.getX() * tileCorner.getX());
//    return(al_map_rgb(r,g,b));
    return(al_map_rgb(255,255,255));
}
void Graphics::drawRobot(Point center, double angle)
{
    //no esta bien invocada la funcion todavia
    al_draw_scaled_rotated_bitmap( robotBitmap, al_get_bitmap_width(robotBitmap)/2, al_get_bitmap_height(robotBitmap)/2, center.getX(), center.getY(), 0.5, 0.5, angle, 0);
}
void Graphics::drawFloor(bool* tiles, int xTiles, int yTiles)//podria no recibir yTiles pero se lo incluye por claridad
{   
    for( int j = 0; j < yTiles ; j++ )
    {
        for( int i = 0; i < xTiles ; i++ )
        {
            Point corner = getTileCorner(i,j);
            
            if(tiles[ j*xTiles + i ] == true) //si esta limpio
            {
                //dibujar la baldosa de color
                al_draw_filled_rectangle(corner.getX(), corner.getY(), corner.getX()+tileSide, corner.getY()+tileSide, getTileColor(corner) );        
                //dibujar un contorno negro alrededor de la baldoza
                al_draw_rectangle(corner.getX(), corner.getY(), corner.getX()+tileSide, corner.getY()+tileSide, al_map_rgb(0,0,0), 0 );        
            }
            else
            {
                //dibujar la baldoza de negro
                al_draw_filled_rectangle(corner.getX(), corner.getY(), corner.getX()+tileSide, corner.getY()+tileSide, al_map_rgb(0,0,0) );        
                //dibujar un contorno negro alrededor de la baldoza
                al_draw_rectangle(corner.getX(), corner.getY(), corner.getX()+tileSide, corner.getY()+tileSide, al_map_rgb(255,255,255), 0 );        

            }
        }
    }
}
void Graphics::showChanges()
{
    al_flip_display();
}