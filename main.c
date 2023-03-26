#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <iso646.h>
#include <math.h>
#include "src/calcs.h"
#include "src/drawning.h"
#include "src/house.h"

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#define MINIM 8.7
double TEAR = 7.7;

//Em função do problema das bibliotecas, precisei chama-las novamente nessa sessão
void MakeElipse(GLfloat, GLfloat, GLfloat);
void MakeRoom( listFloor *, GLfloat, GLfloat, GLfloat);
void MakeBackground(float x, float y, float r, int numPontos);
void AddZoom(void);void MoreZoom(void);void LessZoom(void);
void WelcomeScreen();
void loadScreen ();
void SleepSO(int tempoMS);
double Min(double a, double b);
double AreaCircle(double , double );

//variáveis globais criadas para armazenar os valores de largura, comprimento, sol e raio da imagem
int level = 0;
double largura = 0, comprimento = 0;
int sun = 0;
double AreaTear;
Piso Home[12];
Stack sector;
double AreaMax;
double Raio;
int NumFloor = 0;

void printFloor(Piso Home[], int tam)
{
    int i = 0;
    while(i < tam){
        if(Home[i].empty == false){
            printf("Andar %d: ", i+1);
            listFloor * aux = Home[i].firstComodo;
            while(aux){
                printf("%s ", aux->comodo.name);
                aux = aux->next;
            }
            printf("\n");
            i++;
            }
        else printf("Andar %d: Vazio!\n", i+1),i++;  
    }

}

void Display() //Função de display
{
    glClear(GL_COLOR_BUFFER_BIT);
  
    AddZoom();
    glColor3f(0.0, 0.0, 0.0);

    listFloor * aux = Home[level].firstComodo;
    MakeRoom(aux,0, 0, 150);

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
        system("clear || cls");
        do //Loop para a digitação em intervalos corretosde números aceitos
        {
            WelcomeScreen();
            
            printf("Digite um valor para a largura: ");
            scanf("%lf", &largura);
            if(largura < 0) largura = 0;
            
            printf("Digite um valor para o comprimento: ");
            scanf("%lf", &comprimento);
            if(comprimento < 0) comprimento = 0;
            
            
        } while ( largura < MINIM or comprimento < MINIM);

        system("clear || cls");

        do //Laço para a decisão do nascer do sol
        {
            WelcomeScreen();
            printf("Digite um valor para o nascer do sol:\n\n"
                    "(1) - Norte\n"
                    "(2) - Sul\n"
                    "(3) - Leste\n"
                    "(4) - Oeste\n\n");

            printf("Escolha: ");
            scanf("%d", &sun);
            if(sun != 4 and sun != 3 and sun != 2 and sun != 1) sun = 0;

        } while (not sun);

        loadScreen ();//Tela de carregamento, clássica
        
        AreaTear = Min(largura, comprimento);
        Raio = AreaCircle(largura, comprimento);
        AreaTear = (M_PI * Raio) - (7.7)/2; // - (M_PI/2))*AreaTear;
        printf("Area Tear: %.2lf\n", AreaTear); //Raio em função das entradas dadas, crucial para definir a área exibida na tela
        AreaMax = (Raio * Raio * M_PI) - TEAR;

        sector = initStack(sector);
        printStack(sector);

        AddFloor(sector, Home, AreaTear, AreaMax, &NumFloor);

        printFloor(Home, ++NumFloor);
}

int main(int argc, char **argv) //Cérebro
{

  input();  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1200, 720); 
  glutCreateWindow("Planta baixa em circunferência");
  glClearColor(0.0, 0.0, 0.0, 0.0); 
  gluOrtho2D(-600, 600, -360, 360); 
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}
