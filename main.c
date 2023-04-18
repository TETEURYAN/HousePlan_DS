#include "src/drawning.h"

double TEAR = 7.7;

//variáveis globais criadas para armazenar os valores de largura, comprimento, sol e raio da imagem
int level = 0;
int NumFloor = 0;
double Raio;
char sun = 0;
Piso Home[12];

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

void BuildHouse(double largura, double comprimento){
    Raio = AreaCircle(largura, comprimento); // raio da casa;
    double AreaDoComodoDaEscada = Min(largura, comprimento); // menor lado
    AreaDoComodoDaEscada = (M_PI * Raio) - (7.7)/2; // area do comodo da escada
    
    double AreaMax = (Raio * Raio * M_PI) - TEAR; // area da coroa

    Stack sector = initStack(sector, Raio);
    AddFloor(sector, Home, AreaDoComodoDaEscada, AreaMax, &NumFloor, Raio);
    ++NumFloor;

    printHouseInfo(sector, Home, AreaMax, NumFloor);
    printStack(sector);
    printFloor(Home, NumFloor);
}

void input()//Função para a entrada de largura, comprimento da área e nascer do sol
{

    firstInput();

    double largura = 0, comprimento = 0;

    do
    {
        printOutput();
        printf("O PROGRAMA ACEITARA APENAS LADOS MAIORES DO QUE 8.7 METROS\n");
        printEffect();
        printf("DIGITE UM VALOR PARA A LARGURA: ");
        scanf("%lf", &largura);
        if(largura < 0) largura = 0;
    } while (not validHouse(largura));
            
            
    do{
        printOutput();
        printf("O PROGRAMA ACEITARA APENAS LADOS MAIORES DO QUE 8.7 METROS\n");
        printEffect();
        printf("DIGITE UM VALOR PARA O COMPRIMENTO: ");
        scanf("%lf", &comprimento);
        if(comprimento < 0) comprimento = 0;
    }while(not validHouse(comprimento));


    do //Laço para a decisão do nascer do sol
    {
        printOutput();
        printf("NASCER DO SOL: (O PROGRAMA ACEITARA APENAS VALORES VALIDOS)\n");
        printEffect();

        printf("\t(1) - Norte\n"
              "\t(2) - Sul\n"
              "\t(3) - Leste\n"
              "\t(4) - Oeste\n");
        printEffect();
        printf("DIGITE SEU VALOR: ");
        scanf(" %c", &sun);
    } while (sun > '4' || sun < '1');


    loadScreen ();//Tela de carregamento, clássica
    system("clear || cls");

    BuildHouse(largura, comprimento);
        
}

void main(int argc, char **argv) //Cérebro
{

  input();  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(1200, 720); 
  glutCreateWindow("House Plan");
  glClearColor(1.0, 1.0, 1.0, 0.0); 
  gluOrtho2D(-600, 600, -360, 360); 
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

}