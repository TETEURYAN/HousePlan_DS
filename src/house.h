#ifndef HOUSE_H
#define HOUSE_H

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include <iso646.h>

#include "calcs.h"

typedef struct Room{
    char name[20];
    double area;
    double areaMax;
    double areaMin;
    double areaScreen;
    double angle;
    double delta;
    double r1;
    double r2;
    int wall;
    double cobert[4][2]; 
    double wallp[2][2]; 

} Room;

typedef struct stack {
    Room comodos[12];
    int topo;
} Stack;

typedef struct listFloor
{
    Room comodo;
    struct listFloor * next;
}listFloor;

typedef struct pisos {
    bool empty;
    struct listFloor *firstComodo;
} Piso;


listFloor * getRoom(Room);
Room newRoom(char *, double, double, double, double, double, double, int, double);
void insertInStack (Stack *, char *, double , double, double , double , double , double , int , double );
Stack initStack (Stack, double);
void AddFloor(Stack, Piso [],double, double, int *, double);

#endif // HOUSE_H
