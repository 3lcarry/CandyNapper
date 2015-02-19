/*
 * Attack.h
 *
 *  Created on: 02/03/2012
 *      Author: carrillo
 */

#ifndef ATTACK_H_
#define ATTACK_H_
#include <iostream>
using namespace std;
#include "Timer.h"
#include "GameEntity.h"

namespace candy {

class GEDynamic;

class Attack {
public:
	Attack();
	Attack(GEDynamic* entidad);
	virtual ~Attack();

	float getRango();
	float getFuerza();
	float getCadencia();
	float getVelocidad();
	GEDynamic* getEntidad();
	int getDistVisP();
	int getDistVisM();
	float getCampVision();

	void setRango(float rango);
	void setFuerza(float fuerza);
	void setCadencia(float cadencia);
	void setVelocidad(float velocidad);
	void setEntidad(GEDynamic* entidad);
	void setDistVisP(int dist);
	void setDistVisM(int dist);
	void setCampVision(float angulo);
	void setModificador(float porcentaje);
	bool isAttacking();
	void isAttacking(bool a);

	//bool Atacar(int idDestino);
	/**
	 * Ataque de la entidad
	 * @param idDestino: id de a quien atacas
	 * @param TipoEndidad: tipo de la entidad a la que atacas (Player/Enemigo)
	 */
	bool Atacar(int idDestino, GameEntity::TipoEntidad tipo);

private:
	/**
	 * Modificador ataque
	 */
	float _modificador;

	/**
	 * Rango de ataque
	 */
	float _rangoAtaque;

	/**
	 * Coeficiente de ataque
	 */
	float _fuerzaAtaque;

	/**
	 * Cadencia del ataque. Tiempo que tarda en volver a atacar.
	 */
	float _cadenciaAtaque;

	/**
	 * Tiempo que tarda en llegar el ataque al enemigo
	 */
	float _velocidadAtaque;

	/**
	 * Instante del ultimo ataque (para controlar la velocidad)
	 */
	unsigned int _ultimoAtaque;

	/**
	 * Distancia de vision cuando está parado;
	 */
	int _distVisionParado;

	/**
	 * Distancia de visión cuando se mueve;
	 */
	int _distVisionMovimiento;

	/**
	 * Ángulo que indica la amplitud del campo de visión
	 */
	float _campVision;


	GEDynamic* _entidad;

	bool _isAttacking;

};

} /* namespace candy */
#endif /* ATTACK_H_ */
