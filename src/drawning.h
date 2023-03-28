#ifdef DRAWNING_H
#define DRAWNING_H

extern double IndexZoom;
extern double Zoom;

void AddZoom(void);
void MoreZoom(void);
void LessZoom(void);
void _draw_arc(float , float , float , int );
void printComodo(double Xtext, double Ytext, char * name, double area, int level, bool key);
void DrawWhitePlane(double, double, double, double);
void MakeElipse(GLfloat x, GLfloat y, GLfloat radius);
void MakeRoom(listFloor *, GLfloat x, GLfloat y, int level, GLfloat radius, double);
void WelcomeScreen();
void loadScreen ();
void SleepSO(int tempoMS);
void drawName(float x, float y, char * string);

#endif // DRAWNING_H
