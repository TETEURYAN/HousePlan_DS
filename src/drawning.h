#ifdef DRAWNING_H
#define DRAWNING_H

extern double IndexZoom;
extern double Zoom;

void AddZoom(void);
void MoreZoom(void);
oid LessZoom(void);
void MakeElipse(GLfloat x, GLfloat y, GLfloat radius);
void MakeRoom(Room * comodoOne, Room * comodoTwo, Room * comodoThree, GLfloat x, GLfloat y, GLfloat radius);

#endif // DRAWNING_H
