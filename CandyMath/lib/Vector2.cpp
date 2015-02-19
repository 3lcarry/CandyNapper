/*
 * Vector2.cpp
 *
 *  Created on: 14/02/2012
 *      Author: kaseyo
 */

#include "Vector2.h"
#include <cmath>

namespace candy {

ostream&
operator<<(ostream& os, const Vector2& pos){
	os << "(" << pos.c_x << " , " << pos.c_y << ")";

	return os;
}

Vector2::Vector2() {
	c_x = 0;
	c_y = 0;
}

Vector2::Vector2(float x, float y){
	c_x = x;
	c_y = y;
}

Vector2::~Vector2() {
	c_x = 0.0;
	c_y = 0.0;
}

Vector2::Vector2(const Vector2 & cop){
	copiarDesde(cop);
}

Vector2 &
Vector2::operator =(const Vector2 & cop){
	if(this != &cop){
		this->~Vector2();
		copiarDesde(cop);
	}

	return *this;
}

float
Vector2::getX() const{
	return c_x;
}

float
Vector2::getY() const{
	return c_y;
}

void
Vector2::setX(float x){
	c_x = x;
}

void
Vector2::setY(float y){
	c_y = y;
}


void
Vector2::copiarDesde(const Vector2 & cop){
	c_x = cop.c_x;
	c_y = cop.c_y;
}

bool
Vector2::operator ==(const Vector2 &v){
	return (c_x == v.c_x && c_y == v.c_y);
}

bool
Vector2::operator !=(const Vector2 &v){
	return (c_x != v.c_x || c_y != v.c_y);
}

Vector2::operator Vector3() const{
	return Vector3(c_x, c_y, 0);
}

float
Vector2::Distancia(const Vector2& v) const{
	return (*this - v).Modulo();
}

float
Vector2::Modulo() const{
	return sqrt(c_x*c_x + c_y*c_y);
}

Vector2
Vector2::operator +(const Vector2& v2) const{
	return Vector2(c_x + v2.c_x, c_y + v2.c_y);
}

Vector2
Vector2::operator -(const Vector2& v2) const{
	return Vector2(c_x - v2.c_x, c_y - v2.c_y);
}

} /* namespace candy */
