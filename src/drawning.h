#ifdef DRAWNING_H
#define DRAWNING_H

extern double IndexZoom;
extern double Zoom;

void AddZoom(void);
void MoreZoom(void);
void LessZoom(void);
void MakeElipse(GLfloat x, GLfloat y, GLfloat radius);
void MakeRoom(listFloor *, GLfloat x, GLfloat y, GLfloat radius);
void WelcomeScreen();
void loadScreen ();
void SleepSO(int tempoMS);
drawName(float x, float y, char * string);

#endif // DRAWNING_H
