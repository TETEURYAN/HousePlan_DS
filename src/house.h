#ifndef HOUSE_H
#define HOUSE_H

#include<stdbool.h>

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

void insertInStack (Stack *, char *, double , double, double , double , double , double , int , double );
Stack initStack (Stack, double);
Room newRoom(char * name, double min, double max, double area, double areaScreen, double raioOne, double raioTwo, int wall_pos, double angulo);
Room drawRoom(Room , int, double);
void printStack(Stack );
listFloor * getRoom(Room);
void AddFloor(Stack sector, Piso floor[],double AreaTear, double AreaMax, int *, double);


#endif // HOUSE_H
