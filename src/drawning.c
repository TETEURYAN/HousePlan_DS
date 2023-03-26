#include <GL/glut.h>
#include <math.h>
#include "drawning.h"
#include "house.h"
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

void loadScreen () //Tela de carregamento
{
    for(int i = 0; i < 2; i++)
    {
        system("clear || cls");
        printf("Carregando programa\n");
        printf("o------");
        SleepSO(125);

        system("clear || cls");;
        printf("Carregando programa\n");
        printf("-o-----");
        SleepSO(125);

        system("clear || cls");
        printf("Carregando programa\n");
        printf("--o----");
        SleepSO(125);

        system("clear || cls");
        printf("Carregando programa\n");
        printf("---o---");
        SleepSO(125);

        system("clear || cls");
        printf("Carregando programa\n");
        printf("----o--");
        SleepSO(125);
        
        system("clear || cls");
        printf("Carregando programa\n");
        printf("-----o-");
        SleepSO(125);
        
        system("clear || cls");
        printf("Carregando programa\n");
        printf("------o");
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

void MakeRoom(listFloor * comodo, GLfloat x, GLfloat y, GLfloat radius)//Função que desenha o andar junto de cada cômodo
{

    MakeBackground(x, y, radius + 10, 160);//Chama a função de backgound
    
    //Drawn the room selected

    listFloor * aux = comodo;

    while (aux)
    {
        drawRoom(aux->comodo);
        aux = aux->next;
    }
    

    // if(comodoOne != NULL)
    //     drawRoom(comodoOne);
    //  if(comodoTwo != NULL)
    //     drawRoom(comodoTwo);
    //  if(comodoThree != NULL)
    //     drawRoom(comodoThree);

    MakeElipse(x, y, radius);// paredes andar ou terreo
    MakeElipse(x, y, radius - 5);// paredes andar ou terreo
    MakeElipse(x, y, (radius*0.4));// paredes andar ou terreo
    MakeElipse(x, y, (radius*0.4)-5);// paredes andar ou terreo
}

