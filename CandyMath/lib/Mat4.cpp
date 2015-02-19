/*
 * Mat4.cpp
 *
 *  Created on: 09/02/2012
 *      Author: kaseyo
 */

#include "Mat4.h"

#include <iostream>
using namespace std;

namespace candy {

ostream&
operator<<(ostream& os, const Mat4& mat){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			cout << mat.c_mat4x4[j*4 + i] << "\t";
		}
		cout << endl;
	}

	return os;
}

float Mat4::c_error = 0.0;

Mat4::Mat4() {
	c_mat4x4 = new float[16];

	for(int i = 0; i < 4; i ++){
		for(int j = 0; j < 4; j++){
			if(i==j){
				c_mat4x4[posicion(j, i)] = 1;
			}else{
				c_mat4x4[posicion(j, i)] = 0;
			}
		}
	}
}

Mat4::Mat4(float m00, float m01, float m02, float m03
			, float m10, float m11, float m12, float m13
			, float m20, float m21, float m22, float m23
			, float m30, float m31, float m32, float m33)
{
	c_mat4x4 = new float[16];

	c_mat4x4[0] = m00;
	c_mat4x4[1] = m10;
	c_mat4x4[2] = m20;
	c_mat4x4[3] = m30;

	c_mat4x4[4] = m01;
	c_mat4x4[5] = m11;
	c_mat4x4[6] = m21;
	c_mat4x4[7] = m31;

	c_mat4x4[8] = m02;
	c_mat4x4[9] = m12;
	c_mat4x4[10] = m22;
	c_mat4x4[11] = m32;

	c_mat4x4[12] = m03;
	c_mat4x4[13] = m13;
	c_mat4x4[14] = m23;
	c_mat4x4[15] = m33;

}

Mat4::~Mat4() {
	if(c_mat4x4 != NULL){
		delete[] c_mat4x4;
		c_mat4x4 = NULL;
	}
}

Mat4::Mat4(const Mat4& cop){
	c_mat4x4 = NULL;
	copiarDesde(cop);
}

Mat4&
Mat4::operator=(const Mat4& cop){
	if(this != &cop){
		this->~Mat4();
		copiarDesde(cop);
	}

	return *this;
}

void
Mat4::copiarDesde(const Mat4& cop){
	//Comprobamos los NULL x si acaso
	if(cop.c_mat4x4 != NULL){
		if(c_mat4x4 == NULL){
			c_mat4x4 = new float[16];
		}

		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				c_mat4x4[posicion(i, j)] = cop.c_mat4x4[posicion(i, j)];
			}
		}
	}
}

int
Mat4::posicion(int i, int j) const{
	return i*4+j;
}

float*
Mat4::getMatrix(){
	return c_mat4x4;
}

float
Mat4::operator ()(int i, int j) const{
	float res = 0.0;

	if(i < 4){
		if(j < 4){
			res = c_mat4x4[posicion(j, i)];
		}
	}

	return res;
}

float&
Mat4::operator ()(int i, int j){
	c_error = 0.0;

	if(i < 4){
		if(j < 4){
			return c_mat4x4[posicion(j, i)];
		}
	}

	return c_error;
}


Mat4
Mat4::operator +(const Mat4& m2) const{
	return Mat4(c_mat4x4[0] + m2.c_mat4x4[0], c_mat4x4[1] + m2.c_mat4x4[1], c_mat4x4[2] + m2.c_mat4x4[2], c_mat4x4[3] + m2.c_mat4x4[3],
				c_mat4x4[4] + m2.c_mat4x4[4], c_mat4x4[5] + m2.c_mat4x4[5], c_mat4x4[6] + m2.c_mat4x4[6], c_mat4x4[7] + m2.c_mat4x4[7],
				c_mat4x4[8] + m2.c_mat4x4[8], c_mat4x4[9] + m2.c_mat4x4[9], c_mat4x4[10] + m2.c_mat4x4[10], c_mat4x4[11] + m2.c_mat4x4[11],
				c_mat4x4[12] + m2.c_mat4x4[12], c_mat4x4[13] + m2.c_mat4x4[13], c_mat4x4[14] + m2.c_mat4x4[14], c_mat4x4[15] + m2.c_mat4x4[15]);
}

Mat4
Mat4::operator -(const Mat4& m2) const{
	return Mat4(c_mat4x4[0] - m2.c_mat4x4[0], c_mat4x4[1] - m2.c_mat4x4[1], c_mat4x4[2] - m2.c_mat4x4[2], c_mat4x4[3] - m2.c_mat4x4[3],
				c_mat4x4[4] - m2.c_mat4x4[4], c_mat4x4[5] - m2.c_mat4x4[5], c_mat4x4[6] - m2.c_mat4x4[6], c_mat4x4[7] - m2.c_mat4x4[7],
				c_mat4x4[8] - m2.c_mat4x4[8], c_mat4x4[9] - m2.c_mat4x4[9], c_mat4x4[10] - m2.c_mat4x4[10], c_mat4x4[11] - m2.c_mat4x4[11],
				c_mat4x4[12] - m2.c_mat4x4[12], c_mat4x4[13] - m2.c_mat4x4[13], c_mat4x4[14] - m2.c_mat4x4[14], c_mat4x4[15] - m2.c_mat4x4[15]);
}


Mat4
Mat4::operator *(float r1) const{
	return Mat4(c_mat4x4[0] * r1, c_mat4x4[1] * r1, c_mat4x4[2] * r1, c_mat4x4[3] * r1,
				c_mat4x4[4] * r1, c_mat4x4[5] * r1, c_mat4x4[6] * r1, c_mat4x4[7] * r1,
				c_mat4x4[8] * r1, c_mat4x4[9] * r1, c_mat4x4[10] * r1, c_mat4x4[11] * r1,
				c_mat4x4[12] * r1, c_mat4x4[13] * r1, c_mat4x4[14] * r1, c_mat4x4[15] * r1);
}

Mat4
Mat4::operator *(const Mat4& m1) const{
	Mat4 res;
	float* resPtr = res.getMatrix();

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			*resPtr = c_mat4x4[posicion(0, j)] * m1.c_mat4x4[posicion(i, 0)]
					+ c_mat4x4[posicion(1, j)] * m1.c_mat4x4[posicion(i, 1)]
					+ c_mat4x4[posicion(2, j)] * m1.c_mat4x4[posicion(i, 2)]
					+ c_mat4x4[posicion(3, j)] * m1.c_mat4x4[posicion(i, 3)];
			resPtr++;
		}
	}

	return res;
}


} /* namespace candy */
