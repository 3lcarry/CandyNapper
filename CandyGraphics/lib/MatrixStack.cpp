/*
 * MatrixStack.cpp
 *
 *  Created on: 12/02/2012
 *      Author: kaseyo
 */

#include "MatrixStack.h"

namespace candy {

MatrixStack* MatrixStack::c_instance = NULL;

MatrixStack::MatrixStack() {

}

MatrixStack::~MatrixStack() {

}

MatrixStack*
MatrixStack::getInstance(){
	if(c_instance == NULL){
		c_instance = new MatrixStack();
	}

	return c_instance;
}

void
MatrixStack::Pop(){
	if(!c_pilaMatrices.empty()){
		c_matrizActual = c_pilaMatrices.top();
		//Cargamos en OpenGL la cima, y la extraemos de la pila
		glLoadMatrixf(c_matrizActual.getMatrix());

		c_pilaMatrices.pop();
	}
}

void
MatrixStack::Push(){
	c_pilaMatrices.push(c_matrizActual);
}

Mat4
MatrixStack::Top(){
	Mat4 cima;
	if(!c_pilaMatrices.empty()){
		cima = c_pilaMatrices.top();
	}
	return cima;
}

Mat4
MatrixStack::Actual(){
	return c_matrizActual;
}

void
MatrixStack::setActual(const Mat4& actual){
	c_matrizActual = actual;
}

void
MatrixStack::Init(){
	Mat4 id;
	c_matrizActual = id;

	while(!c_pilaMatrices.empty()){
		c_pilaMatrices.pop();
	}
}

} /* namespace candy */
