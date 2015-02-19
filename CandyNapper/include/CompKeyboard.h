/*
 * KeyComponent.h
 *
 *  Created on: 19/01/2012
 *      Author: kaseyo
 */

#ifndef KEYCOMPONENT_H_
#define KEYCOMPONENT_H_

#include "IComponent.h"
#include "CandyGraphics.h" //Por el teclado.h

#include <map>
using namespace std;

namespace candy {
	class GameEntity;

	/**
	 * @class KeyComponent
	 * Componente dedicado a la entrada por teclado
	 */
	class CompKeyboard: public candy::IComponent {
	public:
		/**
		 * Enum que guarda las posibles acciones del player
		 */
		enum Accion{
			Adelante, //!< Adelante
			Derecha,  //!< Derecha
			Izquierda,//!< Izquierda
			Atras,    //!< Atras
			Apuntando,
			CambioPersonajes
		};

		/**
		 * Constructor por defecto
		 */
		CompKeyboard();

		/**
		 * Constructor por defecto
		 */
		~CompKeyboard();

		/**
		 * Constructor de copia
		 * @param kc Origen de la copia
		 */
		CompKeyboard(const CompKeyboard& kc);

		/**
		 * Operador asignacion
		 * @param kc Origen de la copia
		 * @return Resultado de la asignacion
		 */
		CompKeyboard& operator=(const CompKeyboard& kc);

		/**
		 * Implementacion de la funcion virtual pura de IComponent.
		 * @param entidad Entidad que actualizamos
		 */
		void Update(GameEntity* entidad);

	private:

		/**
		 * Funcion auxiliar que copia un objeto en otro
		 * @param kc Origen de la copia
		 */
		void copiarDesde(const CompKeyboard& kc);

		/**
		 * Controlador de teclado
		 */
		Teclado c_teclado;

		/**
		 * Map que guarda el binding de cada tecla con cada accion
		 */
		map<Teclado::Tecla, Accion> c_mapAccion;

		/**
		 * Map que guarda el estado de cada accion
		 */
		map<Accion, bool> c_mapEstado;

		/**
		 * Instante del ultimo cambio de personaje (para que con una pulsacion cambie solo una vez)
		 */
		long int _cambioPj;

	};

} /* namespace candy */
#endif /* KEYCOMPONENT_H_ */
