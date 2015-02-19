/*
 * Attack.cpp
 *
 *  Created on: 02/03/2012
 *      Author: carrillo
 */

#include "Attack.h"
#include "GEDynamic.h"
#include "CandyNapper.h"

namespace candy {

Attack::Attack() {
	_entidad = NULL;
	_cadenciaAtaque = 0;
	_fuerzaAtaque = 0;
	_rangoAtaque = 0;
	_velocidadAtaque = 0;
	_ultimoAtaque = 0;
	_distVisionMovimiento = 0;
	_distVisionParado = 0;
	_campVision = 0.0;
	_modificador = 1.0;
	//_ultimoAtaque = Timer::getTimeElapsed();
}

Attack::Attack(GEDynamic* entidad) {
	_entidad = entidad;
	if (_entidad != NULL) {
		if (entidad->getTipo() == GameEntity::Enemigo) {
			Enemy* enemy = ((Enemy*) entidad);
			if (enemy->getTipoEnemigo() == Enemy::Oso) {
				_cadenciaAtaque = 1500;
				_fuerzaAtaque = 15;
				_rangoAtaque = 10;
				_velocidadAtaque = 20;
				_distVisionMovimiento = 80;
				_distVisionParado = 120;
				_campVision = 150 * M_PI / 180; //150 grados
			} else if (enemy->getTipoEnemigo() == Enemy::Melon) {
				_cadenciaAtaque = 1250;
				_fuerzaAtaque = 25;
				_rangoAtaque = 10;
				_velocidadAtaque = 20;
				_distVisionMovimiento = 80;
				_distVisionParado = 100;
				_campVision = 100 * M_PI / 180; //100 grados
			} else if (enemy->getTipoEnemigo() == Enemy::Gengibre) {
				_cadenciaAtaque = 1000;
				_fuerzaAtaque = 5;
				_rangoAtaque = 10;
				_velocidadAtaque = 15;
				_distVisionMovimiento = 60;
				_distVisionParado = 100;
				_campVision = 150 * M_PI / 180; //100 grados
			}
		} else {
			_cadenciaAtaque = 0;
			_fuerzaAtaque = 0;
			_rangoAtaque = 0;
			_velocidadAtaque = 0;
			_distVisionMovimiento = 0;
			_distVisionParado = 0;
			_campVision = 0.0;
		}

	}

	_modificador = 1.0;
	_ultimoAtaque = Timer::getTimeElapsed();
	_isAttacking = false;
}

Attack::~Attack() {
}

float Attack::getRango() {
	return _rangoAtaque;
}

float Attack::getFuerza() {
	return _fuerzaAtaque;
}

float Attack::getCadencia() {
	return _cadenciaAtaque;
}

float Attack::getVelocidad() {
	return _velocidadAtaque;
}

void Attack::setRango(float rango) {
	_rangoAtaque = rango;
}

void Attack::setFuerza(float fuerza) {
	_fuerzaAtaque = fuerza;
}

void Attack::setCadencia(float cadencia) {
	_cadenciaAtaque = cadencia;
}

void Attack::setVelocidad(float velocidad) {
	_velocidadAtaque = velocidad;
}

GEDynamic* Attack::getEntidad() {
	return _entidad;
}

int Attack::getDistVisP() {
	return _distVisionParado;
}
int Attack::getDistVisM() {
	return _distVisionMovimiento;
}

float Attack::getCampVision() {
	return _campVision;
}

void Attack::setEntidad(GEDynamic *entidad) {
	_entidad = entidad;
}

void Attack::setDistVisP(int dist) {
	_distVisionParado = dist;
}

void Attack::setDistVisM(int dist) {
	_distVisionMovimiento = dist;
}

void Attack::setCampVision(float angulo) {
	_campVision = angulo;
}

void Attack::setModificador(float porcentaje) {
	_modificador = porcentaje;
}

bool Attack::isAttacking(){
	return _isAttacking;
}

void Attack::isAttacking(bool a){
	_isAttacking = a;
}

bool Attack::Atacar(int idDestino, GameEntity::TipoEntidad tipo) {
	bool resultado = true;

	if (idDestino != -1) {
		GEDynamic* enem;

		if (tipo == GameEntity::Player)
			enem = CandyNapper::getInstancia()->getEm()->getPlayer();
		else
			enem = CandyNapper::getInstancia()->getEm()->getEnemy(idDestino);

		if (enem != NULL && _entidad != NULL) {
			Vector3 mi_pos = _entidad->getPosicion();
			Vector3 enem_pos = enem->getPosicion();

			if (mi_pos.Distancia(enem_pos) <= _rangoAtaque) {
				//Atacar con fuerza X en tiempo Y
				unsigned int time = Timer::getTimeElapsed();

				if (time - _ultimoAtaque > _cadenciaAtaque) {
					_ultimoAtaque = time;
					//cout << "[Attack.cpp] MODIFICADOR " << _modificador << endl;
					enem->RecibirAtaque(_fuerzaAtaque*_modificador);
					resultado = true;
				} else {
					resultado = false;
				}
			}
		}
	}
	_isAttacking = resultado;
	return resultado;
}

} /* namespace candy */
