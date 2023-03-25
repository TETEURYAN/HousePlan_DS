#include <GL/glut.h>
#include <stdio.h>
#include <iso646.h>
#include "src/calcs.h"
#include "src/drawning.h"
#include "src/house.h"

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif


//Em função do problema das bibliotecas, precisei chama-las novamente nessa sessão
void MakeElipse(GLfloat, GLfloat, GLfloat);
void MakeRoom(Room *, Room *, Room *, GLfloat, GLfloat, GLfloat);
void MakeBackground(float x, float y, float r, int numPontos);
void AddZoom(void);void MoreZoom(void);void LessZoom(void);
void WelcomeScreen();
void loadScreen ();
void SleepSO(int tempoMS);
int Min(int a, int b);

//variáveis globais criadas para armazenar os valores de largura, comprimento, sol e raio da imagem
int level = 0;
int largura = 0, comprimento = 0;
int sun = 0;
int raioImage;

void Display() //Função de display
{
    glClear(GL_COLOR_BUFFER_BIT);
  
    AddZoom();
    glColor3f(0.0, 0.0, 0.0);

    //The sector will receive the raio value
    //Seção para a criação de cômodos
    Room * cozinhaa = newRoom("Cozinha", 550, raioImage, 150-5, 150*0.4, -1, 240); 
    Room * quarto = newRoom("Quarto", 550, raioImage, 150-5,150*0.4, -1, -6);
    Room * salaOne = newRoom("Sala", 550, raioImage, 150-5,150*0.4, -1, 120);
    Room * salaTwo = newRoom("Sala", 550, raioImage, 150-5,150*0.4, -1, 50);

    //O level é o andar, que anda a cada clique na tecla E e volta em Q
    switch (level)
    {
    case 0:
        MakeRoom(cozinhaa, salaTwo, NULL, 0, 0, 150); // Cada função MakeRoom suporta até 3 cômodos, sendo esse o número máximo por andar
        break;
    case 1:
        MakeRoom(quarto, salaOne, NULL, 0, 0, 150);
        break;
    case 2:
        MakeRoom(salaOne, salaTwo, cozinhaa, 0, 0, 150);
        break;
    default:
        level = 0;//para não escapar dos níveis de andar, toda vez que o limite extrapolar, ele volta ao primeiro anda
        break;    
    }

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
        level = (level != 2 and level < 3) ? ++level : 2;        
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
            scanf("%d", &largura);
            if(largura < 0) largura = 0;
            
            printf("Digite um valor para o comprimento: ");
            scanf("%d", &comprimento);
            if(comprimento < 0) comprimento = 0;
            
            
        } while (not largura or not comprimento);

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
        
        raioImage = Min(largura, comprimento); //Raio em função das entradas dadas, crucial para definir a área exibida na tela
        raioImage /= 3;
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
