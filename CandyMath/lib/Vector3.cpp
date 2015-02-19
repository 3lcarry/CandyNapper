/*
 * Point.cpp

 *
 *  Created on: 19/01/2012
 *      Author: kaseyo
 */

#include "Vector3.h"
#include "Common.h"
#include <cmath>

namespace candy {

ostream&
operator<<(ostream& os, const Vector3& pos){
	os << "(" << pos.c_x << " , " << pos.c_y << " , " << pos.c_z << ")";

	return os;
}

Vector3::Vector3() {
	c_x = 0;
	c_y = 0;
	c_z = 0;
}

Vector3::Vector3(float x, float y, float z){
	c_x = x;
	c_y = y;
	c_z = z;
}

Vector3::~Vector3() {
	c_x = 0.0;
	c_y = 0.0;
	c_z = 0.0;
}

Vector3::Vector3(const Vector3 & cop){
	copiarDesde(cop);
}

Vector3 &
Vector3::operator =(const Vector3 & cop){
	if(this != &cop){
		copiarDesde(cop);
	}

	return *this;
}

float
Vector3::getX() const{
	return c_x;
}

float
Vector3::getY() const{
	return c_y;
}

float
Vector3::getZ() const{
	return c_z;
}

void
Vector3::setX(float x){
	c_x = x;
}

void
Vector3::setY(float y){
	c_y = y;
}

void
Vector3::setZ(float z){
	c_z = z;
}


void
Vector3::copiarDesde(const Vector3 & cop){
	c_x = cop.c_x;
	c_y = cop.c_y;
	c_z = cop.c_z;
}

Vector3
Vector3::operator +(const Vector3& v2) const{
	return Vector3(c_x + v2.c_x, c_y + v2.c_y, c_z + v2.c_z);
}

Vector3
Vector3::operator -(const Vector3& v2) const{
	return Vector3(c_x - v2.c_x, c_y - v2.c_y, c_z - v2.c_z);
}

float
Vector3::operator *(const Vector3& v2) const{
	return (c_x*v2.c_x + c_y*v2.c_y + c_z*v2.c_z);
}

bool
Vector3::operator==(const Vector3& v) const {
	return (c_x == v.c_x && c_y == v.c_y && c_z == v.c_z);
}

bool
Vector3::operator!=(const Vector3& v) const {
	return (!(*this == v));
}

float
Vector3::Modulo() const{
	return sqrt(c_x*c_x + c_y*c_y + c_z*c_z);
}

float
Vector3::Distancia(const Vector3& v2) const{
	return (*this - v2).Modulo();
}

float
Vector3::Angulo(const Vector3& v2) const{
	return acos(CandyMath::grad2rad(this->operator *(v2) / (this->Modulo() * v2.Modulo())));
}

} /* namespace candy */
