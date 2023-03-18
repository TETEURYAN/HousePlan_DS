#include <GL/glut.h>
#include <math.h>

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

