/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: hamster
 *
 * Created on March 25, 2017, 5:31 PM
 */

#include <cstdlib>
#include <allegro5/allegro.h>
#include "Graphics.h"
#include "GraphicMode2.h"
#include <math.h>
#include <stdio.h>


using namespace std;

int main(int argc, char** argv) {

    int i = 5, j = 5;
    Point travolta;
    travolta.setX(20);
    travolta.setY(20);
    
   Graphics Graphic (i,j);
    
    bool floor[25] = {true, true, true, false, true, false, true, false, true, \
                      false, true, false, true, false, true, false, true, false,\
                      true, false, true, false, true, true, true};
    Graphic.drawFloor(floor, i, j);
    Graphic.drawRobot(travolta.getX(), travolta.getY(), M_PI);
    Graphic.drawRobot(40, 40, 0);
    
    Graphic.showChanges(); 
    
/*    GraphicMode2 graph (20);
    graph.showChanges();*/
    al_rest(5.0);
    return 0;
}

