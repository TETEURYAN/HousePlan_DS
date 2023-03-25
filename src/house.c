#include "calcs.h"
#include "drawning.h"
#include "house.h"
#include <GL/freeglut.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define WALL 0.15

double coef(double, double, double, double);
double reta(double, double, double);

Room * newRoom(char * name, double area, double raioOne, double raioTwo, int wall_pos, double angulo)
{
    Room * comodo = malloc(sizeof(Room));
    strcpy(comodo->name, name);
    comodo->area = area;
    comodo->delta = -1;
    comodo->r1 = raioOne;
    comodo->r2 = raioTwo;
    comodo->angle = angulo;
    comodo->wall = wall_pos;
    comodo->next = NULL;
    return comodo;
}

void drawRoom(Room * comodo)
{
    int wall_pos = comodo->wall;
    int option, f, pos = 0;
    double dangle = 0, deg, text_pos[2], angulo;
    double m, equ, x1, x2, y1, y2;

    angulo = comodo->angle;
    for(int i = -1; i < 2; i+=2)
    {

        glColor3f(0.0, 0.0, 0.0);

        angulo += dangle;
        deg = angulo * M_PI / 180;

        comodo->cobert[pos][0] = cos(deg) * comodo->r1; comodo->cobert[pos++][1] = sin(deg) * comodo->r1;

        glBegin(GL_LINE_LOOP);
        glVertex2f(cos(deg) * comodo->r1, sin(deg) * comodo->r1);
        glVertex2f(cos(deg) * comodo->r2, sin(deg) * comodo->r2);
        glEnd();

        if(i == -1)
        {
            dangle = (360 * comodo->area)/(M_PI * (comodo->r2 - comodo->r1) * (comodo->r2 + comodo->r1));
            comodo->delta = dangle;
        }
    }


    x1 = comodo->cobert[wall_pos+1][0]; y1 = comodo->cobert[wall_pos+1][1];
    x2 = comodo->cobert[wall_pos+2][0]; y2 = comodo->cobert[wall_pos+2][1];

    option = (x1 >= 0) ? 1 : -1;
    m = coef(x1, x2, y1, y2);

    equ = y1 - m*x1;
    equ = equ + wall_pos*option*(5*(sqrt(1 + m*m)));

    x1 = (-2*m*equ + option*sqrt(4*m*m*equ*equ - 4*(1 + m*m)*(equ*equ - pow(comodo->r1,2))))/(2*(1 + m*m));
    y1 = reta(m, x1, equ);
    x2 = (-2*m*equ + option*sqrt(4*m*m*equ*equ - 4*(1 + m*m)*(equ*equ - pow(comodo->r2,2))))/(2*(1 + m*m));
    y2 = reta(m, x2, equ);

    comodo->wallp[0][0] = x1; comodo->wallp[0][1] = y1;
    comodo->wallp[1][0] = x2; comodo->wallp[1][1] = y2;

    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

}
