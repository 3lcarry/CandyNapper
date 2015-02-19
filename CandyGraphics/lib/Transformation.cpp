/*
 * Transformation.cpp
 *
 *  Created on: 17/11/2011
 *      Author: kaseyo
 */

#include "Transformation.h"
using namespace candy;

MatrixStack* Transformation::c_pila = MatrixStack::getInstance();

Transformation::Transformation():
		GNode(GNode::E_Transformation)
{
	c_order = false;
}

Transformation::~Transformation() {

}

Transformation::Transformation(const Transformation &cop):
		GNode(cop)
{
	copiarDesde(cop);
}

Transformation&
Transformation::operator=(const Transformation& cop){
	if(this != &cop){
		this->~Transformation();
		GNode::copiarDesde(cop);
		copiarDesde(cop);
	}

	return *this;
}

void
Transformation::Render(bool seleccion){
	//glPushMatrix(); //Guardamos la matriz que llevabamos hasta el momento
	c_pila->Push();
		//Le pasamos a OpenGL el puntero de nuestra matriz en formato "OpenGL"
		glMultMatrixf(c_matriz.getMatrix());
		c_pila->setActual(c_matriz);

		//LLamamos en preorden a sus hijos
#ifdef _DEBUG_
		cout << "Renderizo la transformacion" << endl;
		cout << "Renderizo los hijos de la transformacion(" << hijos.size() << ")" << endl;
		cout << endl;
#endif
		RenderHijos(seleccion);
#ifdef _DEBUG_
		cout << endl;
		cout << "Vuelvo a la transformacion" << endl;
#endif
	//glPopMatrix();
	c_pila->Pop();
}

void
Transformation::copiarDesde(const Transformation& cop){
	c_matRotacion = cop.c_matRotacion;
	c_matEscalado = cop.c_matEscalado;
	c_matTranslacion = cop.c_matTranslacion;
}

void
Transformation::Translate(Vector3 p){
	Translate(p.getX(), p.getY(), p.getZ());
}

void
Transformation::Translate(Vector2 p){
	Translate(p.getX(), p.getY());
}

void
Transformation::Translate(float x, float y, float z){

	//La multiplicamos por la actual y actualizamos la de opengl
	c_matTranslacion = getTranslateMatrix(x, y, z) * c_matTranslacion;

	//Actualizamos c_matriz
	if(c_order){
		c_matriz = c_matTranslacion * c_matriz;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::Rotate(int eje, float grados){
	//La multiplicamos por la actual y actualizamos la de opengl
	c_matRotacion = getRotateMatrix(eje, grados) * c_matRotacion;

	//Actualizamos c_matriz
	if(c_order){
		c_matriz = c_matRotacion * c_matriz;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::Rotate(Vector3 eje, float grados){
	c_matRotacion = getRotateMatrix(eje, grados) * c_matRotacion;

	//Actualizamos c_matriz
	if(c_order){
		c_matriz = c_matRotacion * c_matriz;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::Scale(Vector3 p){
	Scale(p.getX(), p.getY(), p.getZ());
}

void
Transformation::Scale(Vector2 p){
	Scale(p.getX(), p.getY());
}

void
Transformation::Scale(float x, float y, float z){
	//La multiplicamos por la actual y actualizamos la de opengl
	c_matEscalado = getScaleMatrix(x, y, z) * c_matEscalado;

	//Actualizamos c_matriz
	if(c_order){
		c_matriz = c_matEscalado * c_matriz;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

Mat4
Transformation::getMatrix(){
	return (c_matriz);
}

Mat4
Transformation::getRotateMatrix(int eje, float grados){
	//Creamos nuestra matriz de rotacion
	Mat4 rotacion;

	float cos = cosf(grados);
	float sin = sinf(grados);

	switch(eje){
	case 0:
		//Eje X
		rotacion(1, 1) = cos;
		rotacion(1, 2) = -sin;
		rotacion(2, 1) = sin;
		rotacion(2, 2) = cos;
		break;

	case 1:
		//Eje Y
		rotacion(0, 0) = cos;
		rotacion(0, 2) = sin;
		rotacion(2, 0) = -sin;
		rotacion(2, 2) = cos;
		break;

	case 2:
		//Eje Z
		rotacion(0, 0) = cos;
		rotacion(0, 1) = -sin;
		rotacion(1, 0) = sin;
		rotacion(1, 1) = cos;
		break;

	default:
		//No cambiamos nada (se queda la identidad)
		break;
	}

	return rotacion;
}

Mat4
Transformation::getRotateMatrix(Vector3 eje, float grados){
	Mat4 rotacion;

	//Calculamos lo basico
	float u = eje.getX();
	float v = eje.getY();
	float w = eje.getZ();

	float cos_g = cos(grados);
	float sin_g = sin(grados);

	float u2 = u*u;
	float v2 = v*v;
	float w2 = w*w;

	//Calculamos cosas que se repiten
	float denominador = u2 + v2 + w2;
	float radicando = sqrt(u2 + v2 + w2) * sin_g;

	//Coef de los elementos 0,1 y 1,0
	float coeficiente_1 = (u*v*(1 - cos_g) + w*radicando)/denominador;
	//Coef de los elementos 0,2 y 2,0
	float coeficiente_2 = (u*w*(1 - cos_g) - v*radicando)/denominador;
	//Coef de los elementos 2,1 y 1,2
	float coeficiente_3 = (v*w*(1 - cos_g) + u*radicando)/denominador;

	//Diagonal
	rotacion(0, 0) = (u2 + (v2 + w2)*cos_g)/denominador;
	rotacion(1, 1) = (v2 + (u2 + w2)*cos_g)/denominador;
	rotacion(2, 2) = (w2 + (u2 + v2)*cos_g)/denominador;

	//Resto de elementos
	rotacion(0, 1) = coeficiente_1;
	rotacion(1, 0) = coeficiente_1;

	rotacion(0, 2) = coeficiente_2;
	rotacion(2, 0) = coeficiente_2;

	rotacion(2, 1) = coeficiente_3;
	rotacion(1, 2) = coeficiente_3;

	return rotacion;
}

Mat4
Transformation::getScaleMatrix(float x, float y, float z){
	//Hacemos nuestra matriz de escalado
	Mat4 escalado;

	escalado(0, 0) = x;
	escalado(1, 1) = y;
	escalado(2, 2) = z;

	return escalado;
}

Mat4
Transformation::getScaleMatrix(Vector3 p){
	return getScaleMatrix(p.getX(), p.getY(), p.getZ());
}

Mat4
Transformation::getScaleMatrix(Vector2 p){
	return getScaleMatrix(p.getX(), p.getY());
}

Mat4
Transformation::getTranslateMatrix(float x, float y, float z){
	//Hacemos nuestra matriz de traslacion con la posicion p
	Mat4 translacion;

	translacion(0, 3) = x;
	translacion(1, 3) = y;
	translacion(2, 3) = z;

	return translacion;
}

Mat4
Transformation::getTranslateMatrix(Vector3 p){
	return getTranslateMatrix(p.getX(), p.getY(), p.getZ());
}

Mat4
Transformation::getTranslateMatrix(Vector2 p){
	return getTranslateMatrix(p.getX(), p.getY());
}

void
Transformation::setTranslation(Vector3 translacion){
	c_matTranslacion = getTranslateMatrix(translacion);

	if(c_order){
		c_matriz = c_matRotacion * c_matEscalado * c_matTranslacion;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::setTranslation(Vector2 translacion){
	c_matTranslacion = getTranslateMatrix(translacion);

	if(c_order){
		c_matriz = c_matRotacion * c_matEscalado * c_matTranslacion;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}


void
Transformation::setTranslation(float x, float y, float z){
	c_matTranslacion = getTranslateMatrix(x, y, z);

	if(c_order){
		c_matriz = c_matRotacion * c_matEscalado * c_matTranslacion;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::setRotation(int eje, float grados){
	c_matRotacion = getRotateMatrix(eje, grados);

	if(c_order){
		c_matriz = c_matRotacion * c_matEscalado * c_matTranslacion;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::setRotation(Vector3 eje, float grados){
	c_matRotacion = getRotateMatrix(eje, grados);

	if(c_order){
		c_matriz = c_matRotacion * c_matEscalado * c_matTranslacion;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::setScalation(Vector3 escalado){
	c_matEscalado = getScaleMatrix(escalado);

	if(c_order){
		c_matriz = c_matRotacion * c_matEscalado * c_matTranslacion;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::setScalation(Vector2 escalado){
	c_matEscalado = getScaleMatrix(escalado);

	if(c_order){
		c_matriz = c_matRotacion * c_matEscalado * c_matTranslacion;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::setScalation(float x, float y, float z){
	c_matEscalado = getScaleMatrix(x, y, z);

	if(c_order){
		c_matriz = c_matRotacion * c_matEscalado * c_matTranslacion;
	}else{
		c_matriz = c_matTranslacion * c_matEscalado * c_matRotacion;
	}
}

void
Transformation::setOrder(bool order){
	c_order = order;
}
