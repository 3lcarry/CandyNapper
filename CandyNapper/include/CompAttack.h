/*
 * CompAttack.h
 *
 *  Created on: 24/02/2012
 *      Author: kaseyo
 */

#ifndef COMPATTACK_H_
#define COMPATTACK_H_

#include "GameEntity.h"
#include "IComponent.h"
#include "Attack.h"

namespace candy {
	class GEDynamic;
	/**
	 * @class CompAttack
	 * @brief Componente encargado de gestionar el ataque en el player
	 * Componente, que hereda de IComponent, encargado del ataque del player. Debe diferenciar entre si estamos
	 * con un personaje o con otro.
	 */
	class CompAttack : public IComponent {
	public:
		/**
		 * Constructor por defecto (inicializa las variables)
		 */
		CompAttack(GEDynamic* entidad);

		/**
		 * Destructor por defecto
		 */
		~CompAttack();

		/**
		 * Metodo que hereda de IComponent y actualiza la logica de los ataques
		 * @param entidad Entidad que actualizamos
		 */
		void Update(GameEntity* entidad);

	private:
		int idSonido;

		/**
		 * Rango de ataque de Hans
		 */
		static const float RangoHans;

		/**
		 * Rango de ataque de Greta
		 */
		static const float RangoGreta;

		/**
		 * Fuerza de ataque de Hans
		 */
		static const float FuerzaHans;

		/**
		 * Fuerza de ataque de Greta
		 */
		static const float FuerzaGreta;

		/**
		 * Velocidad de ataque de Hans
		 */
		static const float VelocidadHans;

		/**
		 * Velocidad de ataque de Greta
		 */
		static const float VelocidadGreta;

		/**
		 * Cadencia de ataque de Hans
		 */
		static const float CadenciaHans;

		/**
		 * Cadencia de ataque de Greta
		 */
		static const float CadenciaGreta;

		/**
		 * Ataque Hans
		 */
		Attack* _attackHans;

		/**
		 * Ataque Greta
		 */
		Attack* _attackGreta;
	};

} /* namespace candy */
#endif /* COMPATTACK_H_ */
