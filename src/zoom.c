#include "zoom.h"
#include <GL/freeglut.h>

double IndexZoom = 1.0f;
double Zoom = 0.1f;

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