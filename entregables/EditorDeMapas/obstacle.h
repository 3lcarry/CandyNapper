#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Point.h"

class Obstacle{

private:
    Point p;
    int tipo;
public:
    Obstacle();
    ~Obstacle();
    void setCoords(float x, float y);
    void setType(int type);
    float getX();
    float getY();
    int getType();

};

#endif // OBSTACLE_H
