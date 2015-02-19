/*
 * gameentity.h
 *
 *  Created on: Nov 7, 2011
 *      Author: carrillo
 */

#ifndef GAMEENTITY_H_
#define GAMEENTITY_H_

#include <iostream>
#include <list>
using namespace std;

#include "IComponent.h"
#include "CandyMath.h"

namespace candy {
/** @addtogroup CandyEngine
 * @{
 */
	/**
	 * @brief Definicion Basica de las entidades
	 * Interfaz de la que deberan heredar todas les entidades que creemos para el juego
	 * Aqui especificamos las funciones básicas que deberan poder realizar las entidades del juego.
	 * Todas las entidades deberan tener in id para poder identificarlas.
	 */
	class GameEntity {
	public:

		/**
		 * Enum con los diferentes tipos de entidades que tenemos
		 */
		enum TipoEntidad{
			Player,  //!< Player
			Enemigo, //!< Enemigo
			Estatica,//!< Obstaculo
		};

		/**
		 * Obligamos a que se conozcan siempre todos los parametros basicos de un GameEntity
		 * @param tipo Tipo de Entidad (Estatica, Dinamica, jugador, enemigo, etc)
		 * @param posicion Posicion de la entidad
		 * @param id Identificador unico de la entidad
		 */
		GameEntity(TipoEntidad tipo, int id, Vector3 posicion);

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		GameEntity(const GameEntity& cop);

		/**
		 * Operador asignacion
		 * @param cop Origen de la asignacion.
		 * @return Referencia al resultado de la asignacion.
		 */
		GameEntity& operator=(const GameEntity& cop);

		/**
		 * Destructor por defecto
		 */
		virtual ~GameEntity();

		/**@brief Obtiene la posicion de una entidad
		 * @return Devuelve la posicion X,Y,Z en un Vector3
		 */
		Vector3 getPosicion();

		/**
		 * Devuelve el recubrimiento de la entidad
		 * @return Polygono con los puntos del recubrimiento
		 */
		Polygon getConvexHull();

		/**
		 * Devuelve el ID de la entidad
		 * @return Devuelve el ID
		 */
		int getID();

		/**
		 * Devuelve el tipo de objeto
		 * @return Tipo de objeto
		 */
		TipoEntidad getTipo();

		/**
		 * Metodo que recorre toda la lista de componentes llamando al metodo Update de cada una.
		 */
		virtual void Update();

		/**
		 * A�ade un nuevo componente a la entidad.
		 * @param componente Componente que a�adimos
		 */
		void AddComponent(IComponent* componente);

		/**
		 * Devuelve TRUE si es una entidad dinamica
		 * @return TRUE si es dinamica
		 */
		bool isDynamic();

		/**
		 * Devuelve TRUE si es una entidad estatica
		 * @return TRUE si es estatica
		 */
		bool isStatic();

		/**
		 * Indica que la entidad se tiene que destruir
		 */
		void setDestroy();

		/**
		 * Recupera si hay que destruir o no la entidad
		 * @return
		 */
		bool getDestroy();

	protected:

		bool _destruir;

		/**
		 * Funcion privada que copia una entidad en otra
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const GameEntity& cop);

		/**
		 * ID de la entidad (id unico de la entidad).
		 */
		int c_id;

		/**
		 * Posicion de la entidad
		 */
		Vector3 c_posicion;

		/**
		 * Tipo de entidad.
		 */
		TipoEntidad c_tipo;

		/**
		 * Lista que almacena todos los componentes.
		 */
		list<IComponent*> c_componentes;

		/**
		 * Recubrimiento de las entidades (para la fisica, IA, etc)
		 */
		Polygon _convexHull;
	};


/**
 * @}
 */
} /* namespace candy */
#endif /* GAMEENTITY_H_ */
