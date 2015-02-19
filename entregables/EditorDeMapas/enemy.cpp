#include "enemy.h"

Enemy::Enemy(){}

Enemy::~Enemy(){}

void Enemy::setCoords(float x, float y){
    coords.setX(x);
    coords.setY(y);
}

float Enemy::getX(){
    return coords.getX();
}

float Enemy::getY(){
    return coords.getY();
}

void Enemy::setId(int id){
    this->id=id;
}

void Enemy::setType(int type){
    tipo=type;
}

int Enemy::getId(){
    return id;
}

int Enemy::getType(){
    return tipo;
}
