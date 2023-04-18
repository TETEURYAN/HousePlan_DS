#include "house.h"

#define WALL 0.15
#define MAXFLOOR 12


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

void insertInStack (Stack * pilhaDeComodos, char *name, double min, double max, double area, double areaScreen, double raioOne, double raioTwo, int wall_pos, double angulo)// Insere o comodo na pilha
{
    pilhaDeComodos->topo += 1;
    pilhaDeComodos->comodos[pilhaDeComodos->topo] = newRoom( name, min, max,  area,  areaScreen,  raioOne,  raioTwo, wall_pos,  angulo);

}

Stack initStack (Stack pilhaDeComodos, double raioDaCasa) {//Inicializa a pilha de comodos
    
    pilhaDeComodos.topo = -1;

    double areaScreen = 0;

    insertInStack(&pilhaDeComodos, "SALA DE GINASTICA", 25.0, 40.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 240);
    insertInStack(&pilhaDeComodos, "CLOSET", 3.0, 4.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 200 );
    insertInStack(&pilhaDeComodos, "QUARTO 3", 12.0, 30.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 160 );
    insertInStack(&pilhaDeComodos, "BANHEIRO 2", 3.0, 8.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 40);
    insertInStack(&pilhaDeComodos, "QUARTO 2", 12.0, 30.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 120 );
    insertInStack(&pilhaDeComodos, "BANHEIRO 1", 3.0, 8.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 0);
    insertInStack(&pilhaDeComodos, "QUARTO 1", 12.0, 30.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 80 );
    insertInStack(&pilhaDeComodos, "AREA DE SERVIÇO", 6.0, 10.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 30);
    insertInStack(&pilhaDeComodos, "COZINHA", 10.0, 15.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 50);
    insertInStack(&pilhaDeComodos, "SALA DE JANTAR", 15.0, 20.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 60);
    insertInStack(&pilhaDeComodos, "BANHEIRO SOCIAL", 3.0, 8.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 110);
    insertInStack(&pilhaDeComodos, "SALA DE ESTAR", 30.0, 40.0, 0, areaScreen, (raioDaCasa * 50) - 5, 1.57*50, -1, 135);
                                                            //   L largura na tela L traço tela      L angulo com o circulo
                                                                                            //  L regula a distancia da segunda linha, apenas valores negativos
    return pilhaDeComodos; //Retorna a pilha já preenchida com os comodos
}


listFloor * getTear(double AreaTear, double raioDaCasa)//Adiciona a escada em cada andar
{
    listFloor * aux = malloc(sizeof(listFloor));
    strcpy(aux->comodo.name, "SALA DA ESCADA");
    aux->comodo.areaMax = AreaTear;
    aux->comodo.areaMin = AreaTear;
    aux->comodo.areaScreen = AreaTear;

    aux->comodo.r1 = (raioDaCasa * 50) - 5; 
    aux->comodo.r2 = 1.57*50;
    aux->comodo.angle = 0;

    aux->comodo.wall = -1;

    aux->next = NULL;

    return aux;

}

void AddFloor(Stack sector, Piso floor[],double AreaTear, double AreaMax, int * FloorNum, double raioDaCasa)//Algoritmo para organizar os comodos em cada andar
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
                    floor[i].firstComodo = getTear(AreaTear, raioDaCasa);
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

    floor[i+1].firstComodo = getTear(AreaTear, raioDaCasa);
    floor[i+1].firstComodo->next = getRoom(sector.comodos[sector.topo]);
    floor[i+1].empty = false;

    *FloorNum = i+1;
}
