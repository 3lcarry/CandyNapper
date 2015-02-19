/*
 * InterfazPhysics.h
 *
 *  Created on: Nov 15, 2011
 *      Author: carrillo
 */

#ifndef INTERFAZPHYSICS_H_
#define INTERFAZPHYSICS_H_

#include <iostream>
using namespace std;

#include "Box2D/Box2D.h"
#include <math.h>

#include "GameEntity.h"

namespace candy {

/**
 * obtiene el resultado de un ray cast
 * utilizado en la funcion raycast, devuelve tanto entidades dinamicas como estaticas
 */
class RayCastCallback: public b2RayCastCallback {
public:
	RayCastCallback() {
		m_fixture = NULL;
	}

	void iniciar() {
		m_fixture = NULL;
		m_point = b2Vec2(0,0);
		m_normal = b2Vec2(0,0);
		m_fraction =0;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
			const b2Vec2& normal, float32 fraction) {
		m_fixture = fixture;
		m_point = point;
		m_normal = normal;
		m_fraction = fraction;
		/*if(fixture != NULL){
			if(((GameEntity*)fixture->GetBody()->GetUserData())->getTipo() == GameEntity::Player)
				fraction = -1;
		}*/
		return fraction;
	}
	b2Fixture* m_fixture;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	float32 m_fraction;
};

/**
 * obtiene el resultado de un ray cast
 * utilizado en la funcion obtaculo,
 * solo tiene encuenta las entidades dinámicas sirver para pathfinding ...
 */
class RayCastStaticCallback: public b2RayCastCallback {
public:
	RayCastStaticCallback() {
		m_fixture = NULL;
	}

	void iniciar() {
		m_fixture = NULL;
		m_point = b2Vec2(0,0);
		m_normal = b2Vec2(0,0);
		m_fraction =0;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
			const b2Vec2& normal, float32 fraction) {
		m_fixture = fixture;
		m_point = point;
		m_normal = normal;
		m_fraction = fraction;
		if(m_fixture != NULL){
			if(m_fixture->GetBody()->GetType() == b2_dynamicBody)
				m_fraction = -1;
		}

		return m_fraction;
	}
	b2Fixture* m_fixture;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	float32 m_fraction;
};


/**
 * Interfaz especifica para la box2D
 */
class InterfazPhysics {
public:
	/**
	 * Instancia de la interfaz de fisica
	 */
	static InterfazPhysics* getInstance();

	/**
	 * Destruye el mundo de la box2D
	 */
	~InterfazPhysics();
	/**
	 * Carga nuestro mundo (Nuestros personajes del juego), en el mundo del box2D
	 * para mover los personajes detectando colisiones.
	 * @param em EntityManager de donde extraemos la información de nuestro personaje
	 */
	void Init(int ancho, int alto);
	/**
	 * Actualiza las posiciones de los personajes de nuestro mundo en una iteración
	 * el tamaño de la itaracion es 1/60.s
	 */
	void Update(float timestep = 1 / 60.0);

	/**
	 * Devuelve el mundo creado en la interfaz
	 */
	b2World* getMundo();

	/**
	 * Para saber si entre dos puntos hay un obstaculo o no
	 * @param inicio punto inicio del rayo
	 * @param fin punto final del rayo
	 * @return true si hay obstaculos
	 */
	bool obstaculo(Vector3 inicio, Vector3 fin);

	/**
	 * Devuelve el id del objeto que se encuentra lanzando el rayo desde el punto indicado
	 * @param inicio  punto inicial del rayo
	 * @param angulo  angulo del rayo
	 * @return id del objeto encontrado, si no hay ninguno -1
	 */
	GameEntity* RayTracing(Vector3 inicio, float distancia, float angulo);

private:
	/**
	 * Contructor que inicializa el mundo de la box2D y prepara el motor para su uso.
	 * Singleton
	 */
	InterfazPhysics();

	/**
	 * puntero al mundo de la box2D
	 */
	b2World* _mundo;

	/**
	 * Puntero a la interfaz
	 */
	static InterfazPhysics* _instancia;
};

} /* namespace Candy */
#endif /* INTERFAZPHYSICS_H_ */
