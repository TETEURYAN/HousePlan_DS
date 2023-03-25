#ifdef DRAWNING_H
#define DRAWNING_H

extern double IndexZoom;
extern double Zoom;

void AddZoom(void);
void MoreZoom(void);
void LessZoom(void);
void MakeElipse(GLfloat x, GLfloat y, GLfloat radius);
void MakeRoom(Room * comodoOne, Room * comodoTwo, Room * comodoThree, GLfloat x, GLfloat y, GLfloat radius);
<<<<<<< Updated upstream
=======
void MakeBackground(float x, float y, float r, int numPontos);
>>>>>>> Stashed changes

#endif // DRAWNING_H
