/*
 * GameEntityDynamic.cpp
 *
 *  Created on: Nov 8, 2011
 *      Author: carrillo
 */

#include "GEDynamic.h"

using namespace candy;

const float GEDynamic::VelocidadNormal = 15; //4 km/h

GEDynamic::GEDynamic(TipoEntidad tipo, int id, Vector3 posicion)
	: GameEntity(tipo, id, posicion)
{
	//INIT DE ALGUNOS PARAMETROS DE LA ENTIDAD
	c_anguloMovimiento = 0.0; //En principio se "mueve" hacia delante
	c_visionX = 0.0; //En principio "mira" hacia delante
	c_visionY = 0.0; // mira recto, hacia el centro
	c_velocidad = 0.0;
	c_modificado = false;
	_modificadorVelocidad = 1.0;

	//Cosas a inicializar en Player y Enemy
	_radio = 0;
	_vidaRestante = 0;
	_vidaTotal = 0;
	_muerto = false;
	_ataque = new Attack(this);
}

GEDynamic::GEDynamic(const GEDynamic & cop): GameEntity(cop){
	copiarDesde(cop);
}

GEDynamic &
GEDynamic::operator =(const GEDynamic & cop){
	if(this !=  &cop){
		copiarDesde(cop);
	}

	return *this;
}

GEDynamic::~GEDynamic() {

}

void candy::GEDynamic::setModificadorVelocidad(float fraccion)
{
	_modificadorVelocidad = fraccion;
}

void
GEDynamic::copiarDesde(const GEDynamic & cop){
	GameEntity::copiarDesde(cop);
}

void
GEDynamic::setPosicion(Vector3 posicion){
	c_posicion = posicion;
	c_modificado = true;

	_convexHull = PolygonFactory::Circulo(Vector2(posicion.getX(), -posicion.getZ()), _radio);
}

bool
GEDynamic::isModificado(){
	return c_modificado;
}

void
GEDynamic::setModificado(bool mod){
	c_modificado = mod;
}

float
GEDynamic::getAnguloMovimiento(){
	return c_anguloMovimiento;
}

float
GEDynamic::getVisionX(){

	return c_visionX;
}

float
GEDynamic::getVisionY(){
	return c_visionY;
}

float
GEDynamic::getVelocidad(){
	return _modificadorVelocidad*c_velocidad;
}

void
GEDynamic::setAnguloMovimiento(float angulo){
	c_anguloMovimiento = angulo;

	while(c_anguloMovimiento < 0){
		c_anguloMovimiento += 2*M_PI;
	}
	while(c_anguloMovimiento> 2*M_PI){
		c_anguloMovimiento -= 2*M_PI;
	}

	c_modificado = true;
}

void
GEDynamic::setVisionX(float angulo){
	c_visionX = angulo;

	while(c_visionX < 0){
		c_visionX += 2*M_PI;
	}
	while(c_visionX > 2*M_PI){
		c_visionX -= 2*M_PI;
	}

	c_modificado = true;
}

void
GEDynamic::setVisionY(float angulo){
	c_visionY = angulo;
	c_modificado = true;
}

void
GEDynamic::setVelocidad(float velocidad){
	c_velocidad = velocidad;
	c_modificado = true;
}

void
GEDynamic::setVidaRestante(int vida){
	_vidaRestante = vida;
	if(_vidaRestante <= 0)
		_muerto = true;
}

void
GEDynamic::setAttack(Attack *a){
	_ataque =  a;
}

void
GEDynamic::incVida(int x){
	_vidaRestante += x;
}

void
GEDynamic::RecibirAtaque(float attack){
	_vidaRestante -= attack;
	if(_vidaRestante <= 0){
		_muerto = true;
	}
}

int
GEDynamic::getVidaRestante(){
	return _vidaRestante;
}

int
GEDynamic::getVidaTotal(){
	return _vidaTotal;
}

bool
GEDynamic::isMuerto(){
	return _muerto;
}

int
GEDynamic::getRadio(){
	return _radio;
}

Attack*
GEDynamic::getAttack(){
	return _ataque;
}
