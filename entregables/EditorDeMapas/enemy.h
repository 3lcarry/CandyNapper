#ifndef ENEMY_H
#define ENEMY_H
#include "Point.h"

class Enemy{

private:
    Point coords;
    int id;
    int tipo;

public:
    Enemy();
    ~Enemy();
    void setCoords(float x, float y);
    void setId(int id);
    void setType(int type);
    float getX();
    float getY();
    int getId();
    int getType();

};

#endif // ENEMY_H
