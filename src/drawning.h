#ifndef DRAWNING_H
#define DRAWNING_H

#include "house.h"

extern double IndexZoom;
extern GLfloat Zoom;

//Functions
void SleepSO(int);
void loadScreen (void);
void WelcomeScreen(void);
void clearScreen(void);
void AddZoom(void);
void MoreZoom(void);
void LessZoom(void);
void drawName(float, float, char *);
void MakeElipse(GLfloat, GLfloat, GLfloat);
void printComodo(double, double, char *, double, int, bool );
Room drawRoom(Room, int, double );
void MakeRoom(listFloor *, GLfloat, GLfloat, int, GLfloat, double, char);

#endif // DRAWNING_H
