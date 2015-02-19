#include "obstacle.h"

Obstacle::Obstacle(){}

Obstacle::~Obstacle(){}

int Obstacle::getType(){
    return tipo;
}

void Obstacle::setType(int type){
    tipo=type;
}

float Obstacle::getX(){
    return p.getX();
}

float Obstacle::getY(){
    return p.getY();
}

void Obstacle::setCoords(float x, float y){
    p.setX(x);
    p.setY(y);
}
