/*
 * Player.h
 *
 *  Created on: 24/02/2012
 *      Author: kaseyo
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GEDynamic.h"
#include "GameEntity.h"

namespace candy {
/**
 * \addtogroup CandyEngine
 * @{
 */

	/**
	 * @class Player
	 * @brief Player que hereda de GEDynamic
	 * Hereda de la clase GEDynamic y representa a nuestro player. Con sus componentes especificos y su logica especifica
	 */
	class Player : public GEDynamic {
	public:

		enum Personaje{
			Hans,
			Greta
		};

		/**
		 * Constructor del player (encargado de meterle los componentes)
		 * @param posicion Posicion del player
		 */
		Player(Vector3 posicion);

		/**
		 * Destructor del player
		 */
		~Player();

		/**
		 * Setter del personaje actual
		 * @param pj Personaje actual
		 */
		void setPersonaje(Personaje pj);

		/**
		 * Indica si estamos usando a Hans o no
		 * @return TRUE si estamos usando a Hans
		 */
		bool isHans();

		/**
		 * Indica si estamos usando a Greta o no
		 * @return TRUE si estamos usando a Greta
		 */
		bool isGreta();

		/**
		 * Intercambia el personaje actual con el otro
		 */
		void switchPersonaje();

		/**
		 * Setter del modo apuntando
		 * @param apuntando TRUE si cambiamos a modo apuntando
		 */
		void setApuntando(bool apuntando);

		/**
		 * Indica si estamos en modo apuntar
		 * @return TRUE si estamos apuntando
		 */
		bool isApuntando();

		/**
		 * Indica si el player esta atacando
		 * @return TRUE si esta atacando
		 */
		bool isAttacking();

		/**
		 * Setter de atacando
		 * @param atacando TRUE si queremos que ataque
		 */
		void setAttacking(bool atacando);

		/**
		 * Setter Modo a tope
		 */
		void setModoATope(bool modo);

		/**
		 * getter modo
		 */
		bool getModoATope();


	protected:
		/**
		 * Personaje actual (de esto depende el modelo que cargamos y sus ataques)
		 */
		Personaje _personaje;

		/**
		 * Indica si estamos en modo apuntar o no
		 */
		bool _apuntando;

		/**
		 * Indica si esta atacando
		 */
		bool _atacando;

		/**
		 * Modo a tope
		 */
		bool _modoAtope;
	};

} /* namespace candy */
#endif /* PLAYER_H_ */
