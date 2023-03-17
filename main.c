#include "src/house.h"
#include "src/calcs.h"
#include "src/zoom.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

void AddZoom(void); void MoreZoom(void); void LessZoom(void);
void MakeElipse(GLfloat, GLfloat, GLfloat);
void MakeFirstRoom(GLfloat x, GLfloat y, GLfloat radius);

void Display() 
{
    glClear(GL_COLOR_BUFFER_BIT);
  
    AddZoom();
    glColor3f(0.0, 1.0, 0.0);


        MakeFirstRoom(0,0,150);

        MakeElipse(-400.0, 0, 150.0);// segundo andar
        MakeElipse(-400.0, 0, 145.0);// paredes segundo andar
        
        MakeElipse(400, 0, 150.0);// sótão
        MakeElipse(400, 0, 145.0);// paredes do sótão

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
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) 
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1200, 720); 
  glutCreateWindow("Circunferência");
  glClearColor(0.0, 0.0, 0.0, 1.0); 
  gluOrtho2D(-600, 600, -360, 360); 
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}
