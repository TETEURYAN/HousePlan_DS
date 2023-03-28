#include <GL/glut.h>

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(1.0, 1.0, 1.0);
   glRasterPos2f(-0.9, 0.9); // Posição inicial do texto
   const char* text = "Hello World!";
   for (int i = 0; i < strlen(text); i++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]); // Renderiza cada caractere
   }

   glFlush();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutCreateWindow("OpenGL Text Example");
   glutDisplayFunc(display);
   glClearColor(0.0, 0.0, 0.0, 0.0);
   gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
   glutMainLoop();
   return 0;
}