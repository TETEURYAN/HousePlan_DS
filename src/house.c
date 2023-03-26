#include "calcs.h"
#include "drawning.h"
#include "house.h"
#include <GL/freeglut.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <iso646.h>
#include <stdio.h>

#define WALL 0.15
#define MAXFLOOR 12

double coef(double, double, double, double);
double reta(double, double, double);
double AreaCircle(double largura, double comprimento);

listFloor * getRoom(Room exp)
{
    listFloor * aux = malloc(sizeof(listFloor));
    aux->comodo = exp;
    aux->next = NULL;

    return aux;
}

Room newRoom(char * name, double min, double max, double area, double areaScreen, double raioOne, double raioTwo, int wall_pos, double angulo) // Função que retorna um ponteiro com as informações alocadas para cada cômodo
{
    Room comodo;

    strcpy(comodo.name, name);//Copia o nome
    comodo.area = area;//Copia a área de píxel
    comodo.areaMin = min;//Copia a área mínima
    comodo.areaMax = max;//Copia a área máxima
    comodo.areaScreen = min; // Copia a área a ser exibida
    comodo.delta = -1;
    comodo.r1 = raioOne; // Raio da maior elipse
    comodo.r2 = raioTwo; //Raio da menor elipse
    comodo.angle = angulo; //Ângulo em função do ponto 0
    comodo.wall = wall_pos; // Pontos de encontro de cada elipse

    return comodo;

}

void insertInStack (Stack * pilhaDeComodos, char *name, double min, double max, double area, double areaScreen, double raioOne, double raioTwo, int wall_pos, double angulo) 
{
    pilhaDeComodos->topo += 1;
    pilhaDeComodos->comodos[pilhaDeComodos->topo] = newRoom( name, min, max,  area,  areaScreen,  raioOne,  raioTwo, wall_pos,  angulo);

}

Stack initStack (Stack pilhaDeComodos) {
    
    pilhaDeComodos.topo = -1;

    double areaScreen = 0;

    insertInStack(&pilhaDeComodos, "SALA DE GINASTICA", 25.0, 40.0, 550, areaScreen, 150-5, 150*0.4, -1, 240);
    insertInStack(&pilhaDeComodos, "CLOSET", 3.0, 4.0, 550, areaScreen, 150-5, 150*0.4, -1, 200 );
    insertInStack(&pilhaDeComodos, "QUARTO 3", 12.0, 30.0, 550, areaScreen, 150-5, 150*0.4, -1, 160 );
    insertInStack(&pilhaDeComodos, "QUARTO 2", 12.0, 30.0, 550, areaScreen, 150-5, 150*0.4, -1, 120 );
    insertInStack(&pilhaDeComodos, "QUARTO 1", 12.0, 30.0, 550, areaScreen, 150-5, 150*0.4, -1, 80 );
    insertInStack(&pilhaDeComodos, "BANHEIRO 2", 3.0, 8.0, 550, areaScreen, 150-5, 150*0.4, -1, 40);
    insertInStack(&pilhaDeComodos, "BANHEIRO 1", 3.0, 8.0, 550, areaScreen, 150-5, 150*0.4, -1, 0);
    insertInStack(&pilhaDeComodos, "AREA DE SERVIÇO", 6.0, 10.0, 550, areaScreen, 150-5, 150*0.4, -1, 30);
    insertInStack(&pilhaDeComodos, "COZINHA", 10.0, 15.0, 550, areaScreen, 150-5, 150*0.4, -1, 50);
    insertInStack(&pilhaDeComodos, "SALA DE JANTAR", 15.0, 20.0, 550, areaScreen, 150-5, 150*0.4, -1, 60);
    insertInStack(&pilhaDeComodos, "BANHEIRO SOCIAL", 3.0, 8.0, 550, areaScreen, 150-5, 150*0.4, -1, 110);
    insertInStack(&pilhaDeComodos, "SALA DE ESTAR", 30.0, 40.0, 550, areaScreen, 150-5, 150*0.4, -1, 360);

    return pilhaDeComodos;
}


listFloor * getTear(double AreaTear)
{
    listFloor * aux = malloc(sizeof(listFloor));
    strcpy(aux->comodo.name, "ESCADA");
    aux->comodo.areaMax = AreaTear;
    aux->comodo.areaMin = AreaTear;
    aux->comodo.areaScreen = AreaTear;

    aux->next = NULL;

    return aux;

}

void AddFloor(Stack sector, Piso floor[],double AreaTear, double AreaMax, int * FloorNum)
{
    int flag = false;
    int i = 0;
    int CountFloor = 0;
    for(int k = 0; k < MAXFLOOR; k++)
        floor[k].empty = true;

    for(i = 0; i < MAXFLOOR-1; i++)
    {
        floor[i].firstComodo = NULL;
        double AreaFilled = 0; //area construida
        
        int count = 0;//Contador de comodos
        while(AreaMax > AreaFilled ){
            if(flag) break;

            if(AreaFilled + sector.comodos[sector.topo].areaScreen < AreaMax){
                if(floor[i].firstComodo == NULL){
                    floor[i].firstComodo = getTear(AreaTear);
                    AreaFilled += AreaTear;
                }else{
                    listFloor * aux = floor[i].firstComodo;
                    while(aux->next){
                        aux = aux->next;
                    }
                    aux->next = getRoom(sector.comodos[sector.topo]);
                    AreaFilled += sector.comodos[sector.topo].areaScreen; //alterar area mim posteriormente
                    sector.topo--;
                    count++;
                }
            }
            else{
                double AreaDif = (AreaMax - AreaFilled);//Diferença de área cosntruida com área total
                listFloor * aux = floor[i].firstComodo;
                while(aux){
                    if(not count) break;
                    double MaxPossible = aux->comodo.areaMax - aux->comodo.areaMin;

                    if(AreaDif > MaxPossible){
                        aux->comodo.areaScreen += MaxPossible;
                        AreaDif -= MaxPossible;
                        AreaFilled += MaxPossible;
                    }
                    else{
                        aux->comodo.areaScreen += AreaDif;
                        AreaFilled += AreaDif;
                        break;
                    }
                    aux = aux->next;
                }
            }
            flag = (sector.topo < 1);
            if(flag) break;
        }
        floor[i].empty = false;//Vetor foi preenchido
        if(flag) break;
    }

    floor[i+1].firstComodo = getRoom(sector.comodos[sector.topo]);
    floor[i+1].empty = false;

    *FloorNum = i+1;
}

void printStack(Stack room)         
{   
    printf("Lista de comodos por nome: ");
    for( int i = 0; i <= room.topo; i++)
    {
        printf("%s ", room.comodos[i].name);
    }
    printf("\n");
}

void drawRoom(Room comodo) //Função que desenha o cômodo
{
    int wall_pos = comodo.wall; //Recebe a posição da parede
    int option, f, pos = 0;
    double dangle = 0, deg, text_pos[2], angulo;
    double m, equ, x1, x2, y1, y2;

    angulo = comodo.angle;
    for(int i = -1; i < 2; i+=2) // Desenha o cômodo
    {

        glColor3f(0.0, 0.0, 0.0);

        angulo += dangle;
        deg = angulo * M_PI / 180;//Converte para radiano

        comodo.cobert[pos][0] = cos(deg) * comodo.r1; comodo.cobert[pos++][1] = sin(deg) * comodo.r1;

        glBegin(GL_LINE_LOOP);//Desenha os pontos em um laço FOR
        glVertex2f(cos(deg) * comodo.r1, sin(deg) * comodo.r1);
        glVertex2f(cos(deg) * comodo.r2, sin(deg) * comodo.r2);
        glEnd();

        if(i == -1)
        {
            dangle = (360 * comodo.area)/(M_PI * (comodo.r2 - comodo.r1) * (comodo.r2 + comodo.r1));
            comodo.delta = dangle;
        }
    }

    x1 = comodo.cobert[wall_pos+1][0]; y1 = comodo.cobert[wall_pos+1][1];
    x2 = comodo.cobert[wall_pos+2][0]; y2 = comodo.cobert[wall_pos+2][1];

    option = (x1 >= 0) ? 1 : -1;
    m = coef(x1, x2, y1, y2);

    equ = y1 - m*x1;
    equ = equ + wall_pos*option*(5*(sqrt(1 + m*m)));


    //Encontra a interssecção das elipses maiore e menores
    x1 = (-2*m*equ + option*sqrt(4*m*m*equ*equ - 4*(1 + m*m)*(equ*equ - pow(comodo.r1,2))))/(2*(1 + m*m));
    y1 = reta(m, x1, equ);
    x2 = (-2*m*equ + option*sqrt(4*m*m*equ*equ - 4*(1 + m*m)*(equ*equ - pow(comodo.r2,2))))/(2*(1 + m*m));
    y2 = reta(m, x2, equ);

    //salva os valores da interssecção
    comodo.wallp[0][0] = x1; comodo.wallp[0][1] = y1;
    comodo.wallp[1][0] = x2; comodo.wallp[1][1] = y2;

    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}
