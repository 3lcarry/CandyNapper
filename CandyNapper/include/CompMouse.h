/*
 * MouseComponent.h
 *
 *  Created on: 16/02/2012
 *      Author: kaseyo
 */

#ifndef MOUSECOMPONENT_H_
#define MOUSECOMPONENT_H_

#include "Raton.h"
#include "IComponent.h"
#include "GameEntity.h"
#include "GEDynamic.h"
#include "InterfazGraphics.h" //Por acceder a la ventana
#include "CandyMath.h"

namespace candy {
	/**
	 * @class MouseComponent
	 * @brief Componente de raton para las entidades
	 * Componente, que se encarga de interactuar con el rato
	 */
	class CompMouse : public IComponent {
	public:
		/**
		 * Constructor por defecto
		 */
		CompMouse();

		/**
		 * Destructor por defecto
		 */
		~CompMouse();

		/**
		 * Update heredado de IComponent
		 * @param entidad Entidad que actualizamos
		 */
		void Update(GameEntity* entidad);

	private:
		/**
		 * Puntero al mouse
		 */
		/*Raton* c_mouse;*/

		/**
		 * Posicion anterior del mouse
		 */
		Vector2 c_centro;

		/**
		 * Puntero a ventana (por comodidad)
		 */
		Ventana* c_ventana;
	};

} /* namespace candy */
#endif /* MOUSECOMPONENT_H_ */
