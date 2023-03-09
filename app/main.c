#include <GL/glut.h>
#include <math.h>
#include "calcs.h"

void MakeElipse(GLfloat x, GLfloat y, GLfloat radius)
{
    glBegin(GL_LINE_LOOP);
        for(int i=0; i<360; i++) {
        GLfloat angle = i * 3.14159265358979323846 / 180.0; // Converte graus para radianos
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
    glEnd();
}

void MakeFirstRoom(GLfloat x, GLfloat y, GLfloat radius)
{
    //MakeElipse(0.0, 0, 150.0);// primeiro andar ou terreo

    glBegin(GL_LINE_LOOP);
        for(int i=0; i<360; i++) {
        GLfloat angle = i * 3.14159265358979323846 / 180.0; // Converte graus para radianos
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
    glEnd();

    MakeElipse(0.0, 0, radius - 5);// paredes primeiro andar ou terreo
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
  
    glColor3f(0.0, 1.0, 0.0);
       
        MakeFirstRoom(0,0,150);

        MakeElipse(-400.0, 0, 150.0);// segundo andar
        MakeElipse(-400.0, 0, 145.0);// paredes segundo andar
        
        MakeElipse(400, 0, 150.0);// sótão
        MakeElipse(400, 0, 145.0);// paredes do sótão

    glFlush(); 
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1200, 720); 
  glutCreateWindow("Circunferência");
  glClearColor(0.0, 0.0, 0.0, 1.0); 
  gluOrtho2D(-600, 600, -360, 360); 
  glutDisplayFunc(Display);
  glutMainLoop();
  return 0;
}