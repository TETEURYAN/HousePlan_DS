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
        GLfloat angle = i * M_PI/ 180.0; // Converte graus para radianos

        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
    glEnd();
}


void MakeBackground(float x, float y, float r, int numPontos) {
    float angulo;
    int i;

    // Desenha círculo branco
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (i = 0; i <= numPontos; i++) {
        angulo = 2 * M_PI * i / numPontos;
        glVertex2f(x + (r + 0.05) * cos(angulo), y + (r + 0.05) * sin(angulo));
    }
    glEnd();

    // Desenha círculo amarelo
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (i = 0; i <= numPontos; i++) {
        angulo = 2 * M_PI * i / numPontos;
        glVertex2f(x + r * cos(angulo), y + r * sin(angulo));
    }
    glEnd();
}

void MakeRoom(Room * comodoOne, Room * comodoTwo, Room * comodoThree, GLfloat x, GLfloat y, GLfloat radius)
{
    //MakeElipse(0.0, 0, 150.0);// primeiro andar ou terreo
    // glBegin(GL_LINE_LOOP);
    //     for(int i=0; i<360; i++) {
    //     GLfloat angle = i * M_PI / 180.0; // Converte graus para radianos
    //     glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    //     }
    // glEnd();

    MakeBackground(x, y, radius + 10, 160);
    
    //Drawn the room selected
    if(comodoOne != NULL)
        drawRoom(comodoOne);
     if(comodoTwo != NULL)
        drawRoom(comodoTwo);
     if(comodoThree != NULL)
        drawRoom(comodoThree);

    MakeElipse(x, y, radius);// paredes primeiro andar ou terreo
    MakeElipse(x, y, radius - 5);// paredes primeiro andar ou terreo
    MakeElipse(x, y, (radius*0.4));// paredes primeiro andar ou terreo
    MakeElipse(x, y, (radius*0.4)-5);// paredes primeiro andar ou terreo
}

