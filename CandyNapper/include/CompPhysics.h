/*
 * ObjectPhysics.h
 *
 *  Created on: Nov 15, 2011
 *      Author: carrillo
 */

#ifndef OBJECTPHYSICS_H_
#define OBJECTPHYSICS_H_

#include "IComponent.h"
#include "InterfazPhysics.h"
#include "CandyMath.h"
#include "Box2D/Box2D.h"


namespace candy {

class GameEntity;

/**
* @class ObjectPhysics
* @brief Clase contenedora de objetos físicos
* Contiene la información clave sobre un objeto
*/
class CompPhysics: public candy::IComponent {
private:

	b2Shape *forma;
	b2Body *cuerpo;
	b2BodyDef *cuerpo_def;
	GameEntity *_entidad;

public:
	/**
	 * @brief Constructor
	 */
	CompPhysics(GameEntity* entidad);

	/**
	 * @brief Destructor
	 */
	~CompPhysics();


	/**
	 * Implementacion de la funcion virtual pura de IComponent.
	 * @param entidad Entidad que actualizamos
	 */
	void Update(GameEntity* entidad);



	/**
	 * @brief Devuelve la forma del objeto (tipo abstraco, hacer downcasting)
	 * @return puntero a la forma
	 */
	b2Shape* getShape();

	/**
	 * @brief Devuelve el cuerpo de los objetos
	 * @return puntero al cuerpo
	 */
	b2Body* getCuerpo();

	/**
	 * @brief Devuelve la definición del cuerpo del objeto
	 * @return puntero a la definición del cuerpo
	 */
	b2BodyDef* getCuerpoDef();

	/**
	 * @brief se indica la forma que tiene el cuerpo
	 * @para forma del cuerpo
	 */
	void setShape(b2Shape* s);

	/**
	 * @brief se le añade el cuerpo al objeto
	 * @param cuerpo del objeto
	 */
	void setCuerpo(b2Body* b);

	/**
	 * @brief se le añade la definición del cuerpo del objeto
	 * @param definición del cuerpo
	 */
	void setCuerpoDef(b2BodyDef* bd);

	/**
	 * Ajusta la velocidad de un objeto de la box2D, segun la entidad del entity manager
	 * @param entity entidad de la que queremos extraer la velocidad
	 * @param body body a la que le insertaremos la velocidad
	 */
	void ajustarVelocidad();

	/**
	 * Ajusta el angulo de la entidad hacia donde mira
	 * @param entity  endidad a la que afeta
	 * @param body objeto fisico al que afecta
	 */
	void ajustarAngulo();

};

} /* namespace candy */
#endif /* OBJECTPHYSICS_H_ */
