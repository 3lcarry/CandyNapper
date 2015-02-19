/*
 * GameEntityStatic.h
 *
 *  Created on: Nov 8, 2011
 *      Author: carrillo
 */

#ifndef GAMEENTITYSTATIC_H_
#define GAMEENTITYSTATIC_H_

#include "GameEntity.h"

namespace candy {
/**
 * \addtogroup CandyEngine
 * @{
 */

	/**
	 * @class GEStatic
	 * @brief Entidad estática
	 * Hereda de la clase GameEntity. Representa a una entidad estática, es decir,
	 * que a lo largo del transcurso del juego no se movera (p. ej: un arbol).
	 */
	class GEStatic: public GameEntity {
	public:

		/**
		 * Enum con los tipos de entidades estaticas
		 */
		enum TipoStatic {
			Objeto,
			Obstaculo,
			NumObstaculos //Esto tiene que ir siempre al final!!!!!!!!!
		};


		TipoStatic getTipoStatic();

		/**
		 * Constructor de una entidad estatica
		 * @param tipo Tipo de entidad estatica
		 * @param posicion Posicion de la entidad estatica
		 */
		GEStatic(TipoStatic tipo, Vector3 posicion);

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		GEStatic(const GEStatic& cop);

		/**
		 * Operador asignacion
		 * @param cop Origen de la copia
		 * @return Devuelve una referencia al resultado
		 */
		GEStatic& operator= (const GEStatic& cop);

		/**
		 * Destructor por defecto
		 */
		virtual ~GEStatic();

		static const float tamanyo;

	private:
		/**
		 * Copia un objeto en otro
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const GEStatic& cop);

		/**
		 * Tipo de entidad estatica
		 */
		TipoStatic _tipoStatic;
	};

} /* namespace candy */
#endif /* GAMEENTITYSTATIC_H_ */
