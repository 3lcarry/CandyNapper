/*
 * Enemy.h
 *
 *  Created on: 01/03/2012
 *      Author: kaseyo
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "GEDynamic.h"

namespace candy {
/**
 * \addtogroup CandyEngine
 * @{
 */

	/**
	 * @class Enemy
	 * @brief Enemy que hereda de GEDynamic
	 * Hereda de la clase GEDynamic y representa a un enemy. Con sus componentes especificos y su logica especifica
	 */
	class Enemy : public GEDynamic {
	public:
		enum TipoEnemigo{
			Oso,
			Gengibre,
			Melon,
			NumTipoEnemigos
		};

		/**
		 * Constructor por defecto (especificamos la pos, y el tipo de enemigo)
		 */                
		Enemy(Vector3 posicion, TipoEnemigo enem);

		/**
		 * Destructor por defecto
		 */
		~Enemy();

		/**
		 * Se Obtiene el tipo del enemigo
		 */
		TipoEnemigo getTipoEnemigo();

		static const float VelocidadEnemigo;
	private:
		/**
		 * Lo guardamos para que se autoasigne el id (un id diferente a cada enemigo)
		 */
		static int _numEnemigos;

		/**
		 * Tipo de enemigo (de los que hay en el enum)
		 */
		TipoEnemigo _tipoEnem;
	};

} /* namespace candy */
#endif /* ENEMY_H_ */
