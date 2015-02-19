/*
 * HealthComponent.h
 *
 *  Created on: 01/03/2012
 *      Author: kaseyo
 */

#ifndef HEALTHCOMPONENT_H_
#define HEALTHCOMPONENT_H_

#include "IComponent.h"
#include "InterfazGraphics.h"

namespace candy {
	class GameEntity;

	/**
	 * @class CompHealth
	 * Componente encargado de gestionar la vida de la entidad y de dibujar, si hay que hacerlo, su vida restante
	 */
	class CompHealth : public IComponent {
	public:
		/**
		 * Constructor por defecto
		 * @param entidad Entidad duenya del componente
		 */
		CompHealth(GameEntity* entidad);

		/**
		 * Destructor por defecto
		 */
		~CompHealth();

		/**
		 * Metodo encargado de actualizar la entidad
		 * @param entidad Entidad que actualizamos
		 */
		void Update(GameEntity* entidad);

	private:
		/**
		 * Transformacion del texto
		 */
		Transformation* _tTexto;

		/**
		 * Texto donde mostramos la vida restante (se supone que esto es temporal)
		 */
		Text* _textoVidaRestante;
	};

} /* namespace candy */
#endif /* HEALTHCOMPONENT_H_ */
