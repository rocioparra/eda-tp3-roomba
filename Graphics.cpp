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
    
    tileSide = TILESIDE;    //preg: ES MEGA AL PEDO ESTA VARIABLE NO?
    displayWidth = tileSide*xTiles;
    displayHeight = tileSide*yTiles;
    
    display = al_create_display(displayWidth, displayHeight);
    if(!display){
       al_shutdown_primitives_addon();
//       fprintf(stderr, "failed to create display!\n");
//       return -1;
    } 
    
    robotBitmap = al_load_bitmap(ROBOT_SPRITE);
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
    unsigned char r = (unsigned char)(tileCorner.getY() * tileCorner.getY());
    unsigned char g = (unsigned char)(tileCorner.getX() * tileCorner.getY());
    unsigned char b = (unsigned char)(tileCorner.getX() * tileCorner.getX());
    return(al_map_rgb(r,g,b));
}
void Graphics::drawRobot(Point center, double angle)
{
    //no esta bien invocada la funcion todavia
//    al_draw_scaled_rotated_bitmap( *ROBOT_SPRITE, al_get_bitmap_width(ROBOT_SPRITE)/2, al_get_bitmap_height(ROBOT_SPRITE)/2, center.getX(), center.getY(), 0.5, 0.5, angle, 0);
}
void Graphics::drawFloor(bool* tiles)
{
    
}
void Graphics::showChanges()
{
    al_flip_display();
}