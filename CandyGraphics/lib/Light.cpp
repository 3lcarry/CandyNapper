/*
 * Light.cpp
 *
 *  Created on: 08/02/2012
 *      Author: kaseyo
 */

#include "Light.h"

namespace candy {

const int Light::c_enumLuces[7] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4,
										GL_LIGHT5, GL_LIGHT6};
const int Light::MAX_LIGHTS = 7;


Light::Light(Vector3 posicion, Vector3 ambiente, Vector3 difusa, Vector3 especular, int numLuz)
	: GNode(GNode::E_Light)
{
	c_posicion = posicion;
	c_ambiente = ambiente;
	c_difusa = difusa;
	c_especular = especular;
	c_numLuz = numLuz;

	glEnable(c_enumLuces[numLuz]);

	setPosition(posicion);
	setAmbient(ambiente);
	setDiffuse(difusa);
	setSpecular(especular);

}

Light::~Light() {
	//Habria que hacer aqui un disable de GL_LIGHT+numLuz?

}

Light::Light(const Light& cop)
	: GNode(cop)
{
	copiarDesde(cop);

	//Habria que hacer aqui un enable del GL_LIGHT+numLuz?
}

Light&
Light::operator=(const Light& cop){
	if(this != &cop){
		this->~Light();
		GNode::copiarDesde(cop);
		copiarDesde(cop);
	}

	return *this;
}

void
Light::setAmbient(Vector3 ambiente){
	GLfloat amb[4] = {ambiente.getX(), ambiente.getY(), ambiente.getZ(), 1.0};

	glLightfv(c_enumLuces[c_numLuz], GL_AMBIENT, amb);
}

void
Light::setPosition(Vector3 posicion){
	GLfloat pos[4] = {posicion.getX(), posicion.getY(), posicion.getZ(), 1.0};

	glLightfv(c_enumLuces[c_numLuz], GL_POSITION, pos);
}

void
Light::setDiffuse(Vector3 difusa){
	GLfloat dif[4] = {difusa.getX(), difusa.getY(), difusa.getZ(), 1.0};

	glLightfv(c_enumLuces[c_numLuz], GL_DIFFUSE, dif);
}

void
Light::setSpecular(Vector3 especular){
	GLfloat esp[4] = {especular.getX(), especular.getY(), especular.getZ(), 1.0};

	glLightfv(c_enumLuces[c_numLuz], GL_SPECULAR, esp);
}

void
Light::enableLight(){
	glEnable(c_enumLuces[c_numLuz]);
}

void
Light::disableLight(){
	glDisable(c_enumLuces[c_numLuz]);
}

void
Light::copiarDesde(const Light& cop){
	c_posicion = cop.c_posicion;
	c_ambiente = cop.c_ambiente;
	c_difusa = cop.c_difusa;
	c_especular = cop.c_especular;
	c_numLuz = cop.c_numLuz;
}

void
Light::Render(bool seleccion){
	//No deberia hacer nada?
#ifdef _DEBUG_
	cout << "Renderizo la luz" << endl;
	cout << "Renderizo los hijos de la luz" << endl;
	cout << endl;
#endif
	RenderHijos(seleccion);
#ifdef _DEBUG_
	cout << endl;
	cout << "Vuelvo a la luz" << endl;
#endif
}


} /* namespace candy */
