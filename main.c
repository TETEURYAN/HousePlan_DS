#include <GL/glut.h>
#include <stdio.h>
#include <iso646.h>
#include "src/calcs.h"
#include "src/drawning.h"
#include "src/zoom.h"
#include "src/house.h"

void MakeElipse(GLfloat, GLfloat, GLfloat);
void MakeRoom(Room *, Room *, Room *, GLfloat, GLfloat, GLfloat);
void AddZoom(void);void MoreZoom(void);void LessZoom(void);

int level = 0;

void Display() 
{
    glClear(GL_COLOR_BUFFER_BIT);
  
    AddZoom();
    glColor3f(0.0, 1.0, 0.0);

    Room * cozinhaa = newRoom("Cozinha", 550, 150-5, 150*0.4, -1, 240);
    Room * quarto = newRoom("Quarto", 550, 150-5,150*0.4, -1, -6);
    Room * salaOne = newRoom("Sala", 550, 150-5,150*0.4, -1, 120);
    Room * salaTwo = newRoom("Sala", 550, 150-5,150*0.4, -1, 50);

    switch (level)
    {
    case 0:
        MakeRoom(cozinhaa, salaTwo, NULL, 0, 0, 150);
        break;
    case 1:
        MakeRoom(quarto, salaOne, NULL, 0, 0,150);
        break;
    case 2:
        MakeRoom(salaOne, salaTwo, cozinhaa, 0, 0, 150);
        break;
    default:
        level = 0;
        break;    
    }

    glFlush(); 
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-600, 600, -360, 360);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key){
    case 'l':
        MoreZoom(); 
        break;
    case 'j':
        LessZoom(); 
        break;
    case 'q':
        level = (level != 0 and level > -1) ? --level : 0; 
        break;
    case 'e':
        level = (level != 2 and level < 3) ? ++level : 2;        
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) 
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1200, 720); 
  glutCreateWindow("Planta baixa em circunferência");
  glClearColor(0.0, 0.0, 0.0, 1.0); 
  gluOrtho2D(-600, 600, -360, 360); 
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}
