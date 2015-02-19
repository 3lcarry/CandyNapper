/*
 * Obstaculo.h
 *
 *  Created on: 10/05/2012
 *      Author: gustavo
 */

#ifndef OBSTACULO_H_
#define OBSTACULO_H_

#include "GEStatic.h"

namespace candy{

	class Obstaculo : public GEStatic{
	public:
		enum TipoObstaculo{
			Algodon,
			Chupachups,
			Tarta,
			NumTipoObstaculos
		};

		Obstaculo(TipoObstaculo tipo, Vector3 posicion);

		~Obstaculo();

		TipoObstaculo getTipoObstaculo();

	private:

		TipoObstaculo _tipoObstaculo;
	};

}


#endif /* OBSTACULO_H_ */
