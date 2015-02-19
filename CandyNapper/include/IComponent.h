/*
 * IComponent.h
 *
 *  Created on: 19/01/2012
 *      Author: kaseyo
 */

#ifndef ICOMPONENT_H_
#define ICOMPONENT_H_

//TODO: ver si se necesita un método Init, o se hace en el constructor, o que.

namespace candy {

	class GameEntity;

	/**
	 * @class IComponent
	 * @brief Interfaz para los componentes
	 * Interfaz  de la cual heredaran todos los componentes. Se compone unicamente de un método "update", que recibe a un
	 * GameEntity como parametro. Es posible que haya que añadir más métodos (como Init).
	 */
	class IComponent {
	public:
		/**
		 * Destructor virtual por defecto, sin codigo.
		 */
		virtual ~IComponent() {};

		/**
		 * Método principal de la interfaz para los componentes. No tiene codigo (habra que implementarlo en sus hijos).
		 * @param entity Entidad que recibe para "actualizarla". Normalmente será "this".
		 */
		virtual void Update(GameEntity* entity) = 0;
	};

} /* namespace candy */
#endif /* ICOMPONENT_H_ */
