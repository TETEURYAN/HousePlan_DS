#include "drawning.h"
#include <limits.h>
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

void printEffect(){
    printf("========================================================\n");
}

void printTeam(){
    printEffect();
    printf("  UM PROJETO DE MATHEUS RYAN, CAIO CESAR E JOAO GOMES\n");
}

void printHouseInfo(Stack stack, Piso * Home, double AreaMax, int NumFloor) {
    printEffect();
    printf("|                 CASA GERADA COM SUCESSO              |\n");
    printEffect();
    printf("| Area: %.2lf metros quadrados                         |\n", AreaMax);
    printf("| Andares: %i                                           |\n", NumFloor);
    printEffect();
    printf("\n");
}

void printChoose(){
    printf("\t(1) - Inserir valores da casa\n");
    printf("\t(2) - Sair do programa\n"); 
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

void printStack(Stack room)         
{  
    printf("\n");
    printEffect();
    printf("            PILHA DE COMODOS POR PRIORIDADE\n");
    printEffect();
    printf("|");
    for( int i = 0; i <= room.topo; i++)
    {
        printf(" %s", room.comodos[i].name);
        (i == room.topo) ? getchar() : printf(" |");
    }
    printf("\n");
     printEffect();
    printf("\n");
}

void printFloor(Piso Home[], int tam)
{
    int i = 0;
    printf("\n");
    printEffect();
    printf("                       ANDARES\n");
    printEffect();
    while(i < tam){
        if(Home[i].empty == false){
            printf("| Andar %d:", i+1);
            listFloor * aux = Home[i].firstComodo;
            while(aux){
                printf(" %s DE %.2lf M2", aux->comodo.name, aux->comodo.areaScreen);
                (i == tam) ? printf("\n") : printf(" |"); 
                aux = aux->next;
            }printf("\n"),i++;}
        else printf("Andar %d: Vazio!\n", i+1),i++;  
    }
    printEffect();
}

void printOutput(){
        clearScreen();
        WelcomeScreen();    
}

void loadScreen () //Tela de carregamento
{
    for(int i = 0; i < 2; i++)
    {
        system("clear || cls");
        printEffect();
        printf("                Carregando programa\n");
        printf("                      o------\n");
        printEffect();
        SleepSO(125);

        system("clear || cls");
        printEffect();
        printf("                Carregando programa\n");
        printf("                      -o-----\n");
        printEffect();
        SleepSO(125);

        system("clear || cls");
        printEffect();
        printf("                Carregando programa\n");
        printf("                      --o----\n");
        printEffect();
        SleepSO(125);

        system("clear || cls");
        printEffect();
        printf("                Carregando programa\n");
        printf("                      ---o---\n");
        printEffect();
        SleepSO(125);

        system("clear || cls");
        printEffect();
        printf("                Carregando programa\n");
        printf("                      ----o--\n");
        printEffect();
        SleepSO(125);
        
        system("clear || cls");
        printEffect();
        printf("                Carregando programa\n");
        printf("                      -----o-\n");
        printEffect();
        SleepSO(125);
        
        system("clear || cls");
        printEffect();
        printf("                Carregando programa\n");
        printf("                      ------o\n");
        printEffect();
        SleepSO(125);
    }
}

void WelcomeScreen()
{
    printTeam();
    printEffect();
    printf("██████╗  ██║     ███████╗  ████═╗ ██║ ████████╗ ███████╗\n");
    printf("██╔══██╗ ██║     ██╔══██║  ██║ ██║██║ ╚══██╔══╝ ██╔══██║\n");
    printf("██╔══██╗ ██║     ███████║  ██║ ██║██║    ██║    ███████║\n");
    printf("██████╔  ██║     ██╔══██║  ██║  ████║    ██║    ██╔══██║\n");
    printf("██╔═══╝  ██║     ██║  ██║  ██║   ███║    ██║    ██║  ██║\n");
    printf("██║      ██████╗ ██║  ██║  ██║    ██║    ██║    ██║  ██║\n");
    printf("╚═╝      ╚═════╝ ╚═╝  ╚═╝  ╚═╝    ╚═╝    ╚═╝    ╚═╝  ╚═╝\n");
    printf("      ██████╗   ███████╗ ██║  ██║   ██║  ███████╗       \n");
    printf("      ██╔══██╗  ██╔══██║ ██║   ██║ ██║   ██╔══██║       \n");
    printf("      ██████═╝  ███████║ ██║    ████║    ███████║       \n");
    printf("      ██╔═══██╗ ██╔══██║ ██║    ████║    ██╔══██║       \n");
    printf("      ██║   ██║ ██║  ██║ ██║   ██║  ██║  ██║  ██║       \n");
    printf("      ███████║  ██║  ██║ ██║  ██║    ██║ ██║  ██║       \n");
    printf("      ╚══════╝  ╚═╝  ╚═╝ ╚═╝  ╚═╝    ╚═╝ ╚═╝  ╚═╝       \n");
    printEffect();
}   

void clearScreen(){
    system("clear || cls");
}

bool validOP(int op){
    return (op == 1 or op == 2);
}

bool validHouse(double value){
    double min = 8.7;
    return (value > min);
}

bool isFloorOne(int level){
    return (level == 0);
}

void firstInput(){
    
    int op = INT_MAX;
    do
    {
        printOutput();

        printf("OPCOES: (O PROGRAMA ACEITARA APENAS VALORES VALIDOS)\n");
        printEffect();
        printChoose();
        printEffect();
        printf("DIGITE SUA ESCOLHA: ");
        
        scanf("%d", &op);

        if(op == 2){
            clearScreen();
            printEffect();
            printf("OBRIGADO POR USAR O PROGRAMA!\n");
            printEffect();
            exit(0);
        }
        
    } while (not validOP(op));
    
}

void AddZoom(){//Função que habilita o zoom

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(IndexZoom, IndexZoom, 1.0f);//Escala de zoom em função de duas variáveis globais de controle
    
}

void MoreZoom(){//Função que aumenta a escal de zoom
    if(IndexZoom >= 0) IndexZoom = IndexZoom + Zoom;
    else if (IndexZoom < 0) IndexZoom = 0;
}

void LessZoom(){//Função que diminui a escala de zoom
    if(IndexZoom >= 0) IndexZoom = IndexZoom - Zoom;
    else if (IndexZoom < 0) IndexZoom = 0;
}

void DrawName(float x, float y, char * string){//Função ainda não testada para a exibição de strings na tela

    float factor = 0.15;
    glRasterPos2f(x, y);
    
        glPushMatrix();
        glTranslatef(x, y, 1.0f);
        glScalef(0.1, 0.1, 1);
        for(int i = 0; i < strlen(string); i++) 
            glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);
        glPopMatrix();
}

void DrawLadderDoor(Room comodo, double raioDaCasa, double nextAngle){
    if (not strcmp("SALA DA ESCADA", comodo.name)) {
        double radius = comodo.r1;
                
        double anguloInicial = nextAngle;

        double anguloFinal = (comodo.areaScreen * 360) / (M_PI * raioDaCasa * raioDaCasa);
        anguloFinal += anguloInicial;

        glBegin(GL_LINE_STRIP);
            glColor3f(1.0, 0.0, 0.0);
            for(double i = (((anguloInicial + anguloFinal) / 2) - ((180 * 13) / (M_PI * comodo.r1))); i < ((anguloInicial + anguloFinal) / 2) + ((180 * 13) / (M_PI * comodo.r1)); i += 0.0005) {
                GLfloat angle = i * M_PI/ 180.0; // Converte graus para radianos
                glBegin(GL_LINE_LOOP);
                    glVertex2f(0 + radius * cos(angle), 0 + radius * sin(angle));
                    glVertex2f(0 + (radius + 5) * cos(angle), 0 + (radius + 5) * sin(angle));
                glEnd();
            }

        glEnd();
    }
}

void DrawCircleCrown(GLfloat x, GLfloat y, GLfloat radius)//Principal função para o desenho das elipses
{
    glBegin(GL_LINE_STRIP);
    //glBegin(GL_LINE_LOOP);
        for(double i=0; i<360; i += 0.1) {
            glColor3f(0.0, 0.0, 255.0); //O desenho das elipses é feito com base na geometria euclidiana
            GLfloat angle = i * M_PI/ 180.0; // Converte graus para radianos
            glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
            glVertex2f(x + (radius-5) * cos(angle), y + (radius-5) * sin(angle));
        }
    glEnd();
}

void DrawBackground(float x, float y, float r, int numPontos) {//Função que desenha o background branco da planta baixa.
    
    float angulo;
    int i;

    // Desenha círculo branco
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (i = 0; i <= numPontos; i++) {
        angulo = (GLfloat)i / (GLfloat)numPontos * 2.0 * M_PI;
        glVertex2f(x + r * sin(angulo), y + r * cos(angulo));
    }
    glEnd();

}

void DrawWhitePlane(double xOne, double yOne, double xTwo, double yTwo)
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xOne,yOne);
        glVertex2f(xTwo, yTwo);
    glEnd();
}

void DrawWindows(Room comodo, GLfloat radius){
    double anguloDoFinalDoComodo = (comodo.areaScreen * 360) / (M_PI * comodo.r1 * comodo.r1);
    
    glColor3f(1.0, 0.0, 1.0); //O desenho das elipses é feito com base na geometria euclidiana
    glBegin(GL_LINE_STRIP);    
    for(double i = (((comodo.angle + anguloDoFinalDoComodo) / 2) - ((180 * 30) / (M_PI * comodo.r1))); i < ((comodo.angle + anguloDoFinalDoComodo) / 2) + ((180 * 30) / (M_PI * comodo.r1)); i += 0.005) {
        GLfloat angle = i * M_PI/ 180.0; // Converte graus para radianos
        glBegin(GL_LINE_LOOP);
        glVertex2f(0 + radius * cos(angle), 0 + radius * sin(angle));
        glVertex2f(0 + (radius + 5) * cos(angle), 0 + (radius + 5) * sin(angle));
        glEnd();
    }

    glEnd();
}

Room DrawRoom(Room comodo, int level, double lastAngle){ //Função que desenha o cômodo

    int wall_pos = comodo.wall; //Recebe a posição da parede
    int option, f, pos = 0;
    double dangle = 0, deg, text_pos[2], angulo;
    double m, equ, x1, x2, y1, y2;
    double raio = comodo.r2 + comodo.r1;

    angulo = comodo.angle;

    angulo += dangle;
    deg = angulo * M_PI / 180;//Converte para radiano

    comodo.cobert[pos][0] = cos(deg) * comodo.r1; comodo.cobert[pos++][1] = sin(deg) * comodo.r1;

    x1 = comodo.cobert[wall_pos+1][0]; y1 = comodo.cobert[wall_pos+1][1];
    x2 = comodo.cobert[wall_pos+2][0]; y2 = comodo.cobert[wall_pos+2][1];

    option = (x1 >= 0) ? 1 : -1; //Caso o quadrante esteja negativo, o coeficiente angular será multiplicado por -1;
    m = coef(x1, x2, y1, y2);

    equ = y1 - m*x1;
    equ = equ + wall_pos*option*(5*(sqrt(1 + m*m)));//distancia entre linhas paralelas em 5

    //Magnitude de um vetor
    
    x1 = magnitude(m, option, equ, comodo.r1);
    y1 = reta(m, x1, equ);
    x2 = magnitude(m, option, equ, comodo.r2);
    y2 = reta(m, x2, equ);

    glColor3f(0.0, 0.0, 0.0);

    //Armazenando a magnitude do vetor para a linha paralela
    comodo.wallp[0][0] = x1; comodo.wallp[0][1] = y1;
    comodo.wallp[1][0] = x2; comodo.wallp[1][1] = y2;

    glBegin(GL_QUADS);//preenche a porta
        glColor3f(0.0, 0.0, 255.0);
        glVertex2f(cos(deg) * comodo.r1, sin(deg) * comodo.r1);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(cos(deg) * comodo.r2, sin(deg) * comodo.r2);
    glEnd();

    double x3 = magnitude(m, option, equ, (comodo.r1 +comodo.r2 - 20)/2);
    double y3 = reta(m, x3, equ);
    double x4 = magnitude(m, option, equ, (comodo.r1 +comodo.r2 + 20)/2);
    double y4 = reta(m, x4, equ);

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

    DrawWindows(comodo, comodo.r1);

    return comodo;
}

void MakeRoom(listFloor * comodo, GLfloat x, GLfloat y, int level, GLfloat radius, double raioDaCasa, char orientacao)//Função que desenha o andar junto de cada cômodo
{
    //Drawn the room selected
    listFloor * aux = comodo;
    DrawBackground(x, y, aux->comodo.r1, 360);//Chama a função de backgound

    double nextAngle;//Define a posicao dos quartos de acordo com o sol

    if (orientacao == '3') nextAngle = 269.999;
    if (orientacao == '4') nextAngle = 89.999;
    if (orientacao == '1') nextAngle = 359.999;
    if (orientacao == '2') nextAngle = 179.999;

    DrawCircleCrown(x, y, raioDaCasa * 50);// varia a parede externa conforme a area

    DrawCircleCrown(x, y, (1.57*50));// mantem a escada constante

    while (aux)
    {

        if (isFloorOne(level)) {
            DrawLadderDoor(aux->comodo, raioDaCasa, nextAngle);
        }

        aux->comodo.angle = nextAngle;
        aux->comodo = DrawRoom(aux->comodo, level, nextAngle);
        nextAngle += (aux->comodo.areaScreen * 360) / (M_PI * raioDaCasa * raioDaCasa); // angulo necessario para imprimir a area

        aux = aux->next;
    }
}
