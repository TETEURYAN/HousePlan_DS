#ifndef DRAWNING_H
#define DRAWNING_H

#include "house.h"
extern double IndexZoom;
extern GLfloat Zoom;

//Functions
void SleepSO(int);
void printEffect(void);
void printComodo(double, double, char *, double, int, bool );
void printStack(Stack );
void printFloor(Piso [], int);
void printHouseInfo(Stack, Piso *, double, int);
void firstInput(void);
void loadScreen (void);
void WelcomeScreen(void);
void clearScreen(void);
bool validHouse(double);
void printOutput(void);
void AddZoom(void);
void MoreZoom(void);
void LessZoom(void);
void DrawName(float, float, char *);
void DrawCircleCrown(GLfloat, GLfloat, GLfloat);
Room DrawRoom(Room, int, double );
void MakeRoom(listFloor *, GLfloat, GLfloat, int, GLfloat, double, char);

#endif // DRAWNING_H
