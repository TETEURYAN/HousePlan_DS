#include <GL/glut.h>
#include <math.h>
#include "drawning.h"
#include "house.h"
#include <string.h>

double IndexZoom = 1.0f;
GLfloat Zoom = 0.1;

void AddZoom()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(IndexZoom, IndexZoom, 1.0f);
    
}

void MoreZoom()
{
    if(IndexZoom >= 0) IndexZoom = IndexZoom + Zoom;
    else if (IndexZoom < 0) IndexZoom = 0;
}

void LessZoom()
{
    if(IndexZoom >= 0) IndexZoom = IndexZoom - Zoom;
    else if (IndexZoom < 0) IndexZoom = 0;
}

void MakeElipse(GLfloat x, GLfloat y, GLfloat radius)
{
    glBegin(GL_LINE_LOOP);
        for(int i=0; i<360; i++) {
        GLfloat angle = i * 3.14159265358979323846 / 180.0; // Converte graus para radianos
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
    glEnd();
}

void MakeRoom(Room * comodoOne, Room * comodoTwo, Room * comodoThree, GLfloat x, GLfloat y, GLfloat radius)
{
    //MakeElipse(0.0, 0, 150.0);// primeiro andar ou terreo

    glBegin(GL_LINE_LOOP);
        for(int i=0; i<360; i++) {
        GLfloat angle = i * 3.14159265358979323846 / 180.0; // Converte graus para radianos
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
    glEnd();

    //Drawn the room selected
    if(comodoOne != NULL)
        drawRoom(comodoOne);
     if(comodoTwo != NULL)
        drawRoom(comodoTwo);
     if(comodoThree != NULL)
        drawRoom(comodoThree);


    MakeElipse(x, y, radius - 5);// paredes primeiro andar ou terreo
    MakeElipse(x, y, (radius*0.4));// paredes primeiro andar ou terreo
    MakeElipse(x, y, (radius*0.4)-5);// paredes primeiro andar ou terreo
}
