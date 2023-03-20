<<<<<<< Updated upstream
#ifdef HOUSE_H
#define HOUSE_H

void MakeElipse(GLfloat, GLfloat, GLfloat);
void MakeFirstRoom(GLfloat x, GLfloat y, GLfloat radius);

#endif // HOUSE_H
=======
#ifndef HOUSE_H
#define HOUSE_H

typedef struct Room{
    char name[15];
    double area;
    double angle;
    double delta;
    double r1;
    double r2;
    int wall;
    double cobert[4][2]; 
    double wallp[2][2]; 
    struct Room * next;

} Room;


Room * newRoom(char *, double, double, double, int, double);
void drawRoom(Room *);

#endif // HOUSE_H
>>>>>>> Stashed changes
