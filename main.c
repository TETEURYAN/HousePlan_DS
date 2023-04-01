#include <GL/glut.h>

#include <stdio.h>
#include <stdbool.h>
#include <iso646.h>
#include <math.h>

#include "src/calcs.h"
#include "src/drawning.h"
#include "src/house.h"

#define MINIM 8.7
double TEAR = 7.7;

//variáveis globais criadas para armazenar os valores de largura, comprimento, sol e raio da imagem
int level = 0;
double largura = 0, comprimento = 0;
char sun = 0;
double AreaDoComodoDaEscada = 7.7;
Piso Home[12];
Stack sector;
double AreaMax;
double Raio;
int NumFloor = 0;

void Display() //Função de display
{
    glClear(GL_COLOR_BUFFER_BIT);
  
    AddZoom();
    glColor3f(0.0, 0.0, 0.0);

    listFloor * aux = Home[level].firstComodo;
    MakeRoom(aux,0, 0, level, Raio, Raio, sun);

    glFlush(); 
}

void reshape(int w, int h) {//Função de callback
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-600, 600, -360, 360);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {//Função para receber informações do teclado
    switch (key){
    case 'l'://Mais zoom
        MoreZoom(); 
        break;
    case 'j'://menos zoom
        LessZoom(); 
        break;
    case 'q'://Andar pelos andares
        level = (level != 0 and level > -1) ? --level : 0; 
        break;
    case 'e':
        level = (level != NumFloor-1 and level < NumFloor) ? ++level : NumFloor-1;        
        break;
    }
    glutPostRedisplay();
}

void input()//Função para a entrada de largura, comprimento da área e nascer do sol
{
        do //Loop para a digitação em intervalos corretosde números aceitos
        {
            clearScreen();
            WelcomeScreen();
            
            printf("Digite um valor para a largura: ");
            scanf("%lf", &largura);
            if(largura < 0) largura = 0;
            
            printf("Digite um valor para o comprimento: ");
            scanf("%lf", &comprimento);
            if(comprimento < 0) comprimento = 0;
            
            
        } while ( largura < MINIM or comprimento < MINIM);


        do //Laço para a decisão do nascer do sol
        {
            clearScreen();
            WelcomeScreen();
            printf("Digite um valor para o nascer do sol:\n\n"
                    "(1) - Norte\n"
                    "(2) - Sul\n"
                    "(3) - Leste\n"
                    "(4) - Oeste\n\n");

            printf("Escolha: ");
            scanf(" %c", &sun);
        } while (sun > '4' || sun < '1');


        loadScreen ();//Tela de carregamento, clássica
        system("clear || cls");
        
        AreaDoComodoDaEscada = Min(largura, comprimento); // menor lado
        Raio = AreaCircle(largura, comprimento); // raio da casa;
        AreaDoComodoDaEscada = (M_PI * Raio) - (7.7)/2; // area do comodo da escada
        AreaMax = (Raio * Raio * M_PI) - TEAR; // area da coroa
        printf("Area da Casa gerada: %.2lf metro quadrados\n", AreaMax); //Raio em função das entradas dadas, crucial para definir a área exibida na tela
        
        sector = initStack(sector, Raio);
        printStack(sector);
        AddFloor(sector, Home, AreaDoComodoDaEscada, AreaMax, &NumFloor, Raio);
        ++NumFloor;
        printFloor(Home, NumFloor);
}

int main(int argc, char **argv) //Cérebro
{

  input();  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1200, 720); 
  glutCreateWindow("Planta baixa em circunferência");
  glClearColor(1.0, 1.0, 1.0, 0.0); 
  gluOrtho2D(-600, 600, -360, 360); 
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}