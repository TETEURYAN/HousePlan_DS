#include <GL/glut.h>
#include <math.h>
#include "drawning.h"
#include "house.h"
#include <stdbool.h>
#include <iso646.h>
#include <string.h>
#include <stdio.h>

double IndexZoom = 1.0f;
GLfloat Zoom = 0.1;

void SleepSO(int tempoMS)
{
#ifdef __linux__
    usleep(tempoMS * 1000);
#elif __WIN32
    Sleep(tempoMS);
#else

#endif        
}

#define WALL 0.15

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

void _draw_arc(float angle_start, float angle_end, float radius, int num_segments)
{

    float theta = (angle_end - angle_start) / (float)num_segments;
    float tangetial_factor = tan(theta);
    float radial_factor = cos(theta);

    float x = radius * cos(angle_start);
    float y = radius * sin(angle_start);

    glBegin(GL_LINE_STRIP);
    glColor3f(1.6, 1.0, 0.0);
    for(int i = 0; i <= num_segments; i++)
    {
        glVertex2f(x, y);

        float tx = -y;
        float ty = x;

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
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

void printComodo(double Xtext, double Ytext, char * name, double area, int level, bool key)//Função para printar o nome do comodo
{
    char frase[50];
    char andar[12][30] = {"Primeiro andar", "Segundo andar", "Terceiro andar", "Quarto andar", "Quinto andar", "Sexto andar", "Setimo andar", "Oitavo andar", "Nono andar", "Decimo andar", "Decimo primeiro andar", "Decimo segundo andar"};
    if(key)sprintf(frase, "%s %.2f m²",name, area);
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2f(Xtext, Ytext); // Define a posição para começar a desenhar a string
        if(key)glutBitmapString(GLUT_BITMAP_8_BY_13, frase); // Imprime a string
        if(not key)glutBitmapString(GLUT_BITMAP_8_BY_13, andar[level]); // Imprime a string
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

void makeDoor (Room comodo) {
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0);

    glVertex2f(comodo.wallp[0][0], comodo.wallp[0][1]);
    glVertex2f(comodo.wallp[1][0], comodo.wallp[1][1]);

    glEnd();
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


    MakeElipse(x, y, raioDaCasa * 50);// varia a parede externa conforme o angulo
    MakeElipse(x, y, (raioDaCasa * 50) - 5);
    MakeElipse(x, y, (1.57*50));// mantem a escada constante
    MakeElipse(x, y, (1.57*50)-5);
    
    while (aux)
    {
        aux->comodo = drawRoom(aux->comodo, level);
        aux->comodo.angle = nextAngle;
        //printf("comodo: %s, wallpos: %lf %lf %lf %lf\n\n", aux.comodo.name, aux.comodo.wallp[0][0], aux.comodo.wallp[0][1], aux.comodo.wallp[1][0], aux.comodo.wallp[1][1]);
        nextAngle += (aux->comodo.areaScreen * 360) / (M_PI * raioDaCasa * raioDaCasa); // angulo necessario para imprimar a area
        aux = aux->next;
    }
}
