
#include "Point.h"

Point::Point(){x=0; y=0;};

Point::~Point(){};

void Point::setX(float x){
    this->x=x;
}

void Point::setY(float y){
    this->y=y;
}

float Point::getX(){
    return x;
}

float Point::getY(){
    return y;
}
