#include "drawning.h"

//Global variables
double IndexZoom = 1.0f;
GLfloat Zoom = 0.1;

//Choosing SO
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#define WALL 0.15

void SleepSO(int tempoMS)
{
#ifdef __linux__
    usleep(tempoMS * 1000);
#elif __WIN32
    Sleep(tempoMS);
#else

#endif        
}

void loadScreen () //Tela de carregamento
{
    for(int i = 0; i < 2; i++)
    {
        system("clear || cls");
        printf("Carregando programa\n");
        printf("o------\n");
        SleepSO(125);

        system("clear || cls");;
        printf("Carregando programa\n");
        printf("-o-----\n");
        SleepSO(125);

        system("clear || cls");
        printf("Carregando programa\n");
        printf("--o----\n");
        SleepSO(125);

        system("clear || cls");
        printf("Carregando programa\n");
        printf("---o---\n");
        SleepSO(125);

        system("clear || cls");
        printf("Carregando programa\n");
        printf("----o--\n");
        SleepSO(125);
        
        system("clear || cls");
        printf("Carregando programa\n");
        printf("-----o-\n");
        SleepSO(125);
        
        system("clear || cls");
        printf("Carregando programa\n");
        printf("------o\n");
        SleepSO(125);
    }
}

void WelcomeScreen()
{
     printf("\n\t-----------------------------\n"
            "\n\tPROJETO DE ESTRUTURA DE DADOS\n"
            "\n\t-----------------------------\n");

}
void clearScreen(){
    system("clear || cls");
}

void AddZoom()//Função que habilita o zoom
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(IndexZoom, IndexZoom, 1.0f);//Escala de zoom em função de duas variáveis globais de controle
    
}

void MoreZoom()//Função que aumenta a escal de zoom
{
    if(IndexZoom >= 0) IndexZoom = IndexZoom + Zoom;
    else if (IndexZoom < 0) IndexZoom = 0;
}

void LessZoom()//Função que diminui a escala de zoom
{
    if(IndexZoom >= 0) IndexZoom = IndexZoom - Zoom;
    else if (IndexZoom < 0) IndexZoom = 0;
}

void drawName(float x, float y, char * string)//Função ainda não testada para a exibição de strings na tela
{
    float factor = 0.15;
    glRasterPos2f(x, y);
    
        glPushMatrix();
        glTranslatef(x, y, 1.0f);
        glScalef(0.1, 0.1, 1);
        for(int i = 0; i < strlen(string); i++) 
            glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);
        glPopMatrix();
}

void MakeElipse(GLfloat x, GLfloat y, GLfloat radius)//Principal função para o desenho das elipses
{

    glBegin(GL_LINE_LOOP);
        for(int i=0; i<360; i++) {
            glColor3f(0.0, 0.0, 0.0); //O desenho das elipses é feito com base na geometria euclidiana
            GLfloat angle = i * M_PI/ 180.0; // Converte graus para radianos

        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
        }
    glEnd();
}


void MakeBackground(float x, float y, float r, int numPontos) {//Função que desenha o background branco da planta baixa.
    float angulo;
    int i;

    // Desenha círculo branco
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (i = 0; i <= numPontos; i++) {
        angulo = 2 * M_PI * i / numPontos;
        glVertex2f(x + (r + 0.05) * cos(angulo), y + (r + 0.05) * sin(angulo));
    }
    glEnd();

}

void printComodo(double Xtext, double Ytext, char * name,  double area, int level, bool key)//Função para printar o nome do comodo
{
    char frase[50];
    if(key)sprintf(frase, "%s %.2f m²",name, area);
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2f(Xtext, Ytext); // Define a posição para começar a desenhar a string
        if(key)glutBitmapString(GLUT_BITMAP_8_BY_13, frase); // Imprime a string
    glFlush();
}

void DrawWhitePlane(double xOne, double yOne, double xTwo, double yTwo)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xOne,yOne);
        glVertex2f(xTwo, yTwo);
    glEnd();
}

Room drawRoom(Room comodo, int level, double lastAngle) //Função que desenha o cômodo
{
    int wall_pos = comodo.wall; //Recebe a posição da parede
    int option, f, pos = 0;
    double dangle = 0, deg, text_pos[2], angulo;
    double m, equ, x1, x2, y1, y2;
    double raio = comodo.r2 + comodo.r1;

    angulo = comodo.angle;


    angulo += dangle;
    deg = angulo * M_PI / 180;//Converte para radiano

    comodo.cobert[pos][0] = cos(deg) * comodo.r1; comodo.cobert[pos++][1] = sin(deg) * comodo.r1;

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);//Desenha os pontos da primeira parede
        glVertex2f(cos(deg) * comodo.r1, sin(deg) * comodo.r1);
        glVertex2f(cos(deg) * comodo.r2, sin(deg) * comodo.r2);
    glEnd();

    x1 = comodo.cobert[wall_pos+1][0]; y1 = comodo.cobert[wall_pos+1][1];
    x2 = comodo.cobert[wall_pos+2][0]; y2 = comodo.cobert[wall_pos+2][1];

    option = (x1 >= 0) ? 1 : -1; //Caso o quadrante esteja negativo, o coeficiente angular será multiplicado por -1;
    m = coef(x1, x2, y1, y2);

    equ = y1 - m*x1;
    equ = equ + wall_pos*option*(5*(sqrt(1 + m*m)));//distancia entre linhas paralelas em 5


    //Magnitude de um vetor
    x1 = (-2*m*equ + option*sqrt(4*m*m*equ*equ - 4*(1 + m*m)*(equ*equ - pow(comodo.r1,2))))/(2*(1 + m*m));
    y1 = reta(m, x1, equ);
    x2 = (-2*m*equ + option*sqrt(4*m*m*equ*equ - 4*(1 + m*m)*(equ*equ - pow(comodo.r2,2))))/(2*(1 + m*m));
    y2 = reta(m, x2, equ);

    //Armazenando a magnitude do vetor para a linha paralela
    comodo.wallp[0][0] = x1; comodo.wallp[0][1] = y1;
    comodo.wallp[1][0] = x2; comodo.wallp[1][1] = y2;

    glBegin(GL_LINE_LOOP); // printa a linha parelela da parede, a de baixo
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();

    
    // glBegin(GL_LINE_LOOP); // traço vermelho superior
    // glColor3f(1.0, 0.0, 0.0);
    // glVertex2f(cos(deg) * ((comodo.r2 + comodo.r1 - 20) / 2), sin(deg) * ((comodo.r2 + comodo.r1 - 20) / 2));
    // glVertex2f(cos(deg) * ((comodo.r2 + comodo.r1 + 20) / 2), sin(deg) * ((comodo.r2 + comodo.r1 + 20) / 2));
    // glEnd();

    double x3 =(-2*m*equ + option*sqrt(4*m*m*equ*equ - 4*(1 + m*m)*(equ*equ - pow((comodo.r1 +comodo.r2 - 20)/2,2))))/(2*(1 + m*m));
    double y3 = reta(m, x3, equ);
    double x4 = (-2*m*equ + option*sqrt(4*m*m*equ*equ - 4*(1 + m*m)*(equ*equ - pow((comodo.r1 +comodo.r2 + 20)/2,2))))/(2*(1 + m*m));
    double y4 = reta(m, x4, equ);

    // glBegin(GL_LINE_LOOP);//Segundo traço vermelho
    //     glColor3f(1.0, 0.0, 0.0);
    //     glVertex2f(x3, y3);
    //     glVertex2f(x4, y4);
    // glEnd();

    glBegin(GL_QUADS);//preenche a porta
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x4, y4);
        glVertex2f(x3, y3);
        glVertex2f(cos(deg) * ((comodo.r2 + comodo.r1 - 20) / 2), sin(deg) * ((comodo.r2 + comodo.r1 - 20) / 2));
        glVertex2f(cos(deg) * ((comodo.r2 + comodo.r1 + 20) / 2), sin(deg) * ((comodo.r2 + comodo.r1 + 20) / 2));
    glEnd();

    double MidAngle = (comodo.angle/2) * M_PI/180; // meio do angulo em rad
   
    double Xtext = (cos(MidAngle) * (comodo.r1 + comodo.r2)/2);
    double Ytext = (sin(MidAngle) * (comodo.r1 + comodo.r2)/2);

    printComodo(Xtext, Ytext, comodo.name, comodo.areaScreen,level, true);

    double anguloDoFinalDoComodo = (comodo.areaScreen * 360) / (M_PI * comodo.r1 * comodo.r1);


    glColor3f(1.0, 0.0, 1.0); //O desenho das elipses é feito com base na geometria euclidiana
    GLfloat radius = comodo.r1;

    glBegin(GL_LINE_STRIP);

        for(double i = (((comodo.angle + anguloDoFinalDoComodo) / 2) - ((180 * 30) / (M_PI * comodo.r1))); i < ((comodo.angle + anguloDoFinalDoComodo) / 2) + ((180 * 30) / (M_PI * comodo.r1)); i += 0.005) {
            GLfloat angle = i * M_PI/ 180.0; // Converte graus para radianos
            glBegin(GL_LINE_LOOP);
            glVertex2f(0 + radius * cos(angle), 0 + radius * sin(angle));
            glVertex2f(0 + (radius + 5) * cos(angle), 0 + (radius + 5) * sin(angle));
            glEnd();
        }

    glEnd();

    return comodo;
}

void MakeRoom(listFloor * comodo, GLfloat x, GLfloat y, int level, GLfloat radius, double raioDaCasa, char orientacao)//Função que desenha o andar junto de cada cômodo
{

    MakeBackground(x, y, radius + 10, 160);//Chama a função de backgound
    
    //Drawn the room selected

    listFloor * aux = comodo;

    double nextAngle;

    if (orientacao == '3') nextAngle = 269.999;
    if (orientacao == '4') nextAngle = 89.999;
    if (orientacao == '1') nextAngle = 359.999;
    if (orientacao == '2') nextAngle = 179.999;

    MakeElipse(x, y, raioDaCasa * 50);// varia a parede externa conforme a area
    MakeElipse(x, y, (raioDaCasa * 50) - 5);
    MakeElipse(x, y, (1.57*50));// mantem a escada constante
    MakeElipse(x, y, (1.57*50)-5);

    while (aux)
    {
        if (level == 0) {
            if (!strcmp("SALA DA ESCADA", aux->comodo.name)) {
                radius = aux->comodo.r1;
                
                double anguloInicial = nextAngle;

                double anguloFinal = (aux->comodo.areaScreen * 360) / (M_PI * raioDaCasa * raioDaCasa);
                anguloFinal += anguloInicial;

                glBegin(GL_LINE_STRIP);
                    glColor3f(1.0, 0.0, 0.0);
                    for(double i = (((anguloInicial + anguloFinal) / 2) - ((180 * 13) / (M_PI * aux->comodo.r1))); i < ((anguloInicial + anguloFinal) / 2) + ((180 * 13) / (M_PI * aux->comodo.r1)); i += 0.0005) {
                        GLfloat angle = i * M_PI/ 180.0; // Converte graus para radianos
                        glBegin(GL_LINE_LOOP);
                            glVertex2f(0 + radius * cos(angle), 0 + radius * sin(angle));
                            glVertex2f(0 + (radius + 5) * cos(angle), 0 + (radius + 5) * sin(angle));
                        glEnd;
                    }

                glEnd();
            }
        }

        aux->comodo.angle = nextAngle;
        aux->comodo = drawRoom(aux->comodo, level, nextAngle);
        nextAngle += (aux->comodo.areaScreen * 360) / (M_PI * raioDaCasa * raioDaCasa); // angulo necessario para imprimir a area

        aux = aux->next;
    }
}


