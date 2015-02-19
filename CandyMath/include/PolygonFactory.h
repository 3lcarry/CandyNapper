/*
 * PolygonFactory.h
 *
 *  Created on: 17/03/2012
 *      Author: kaseyo
 */

#ifndef POLYGONFACTORY_H_
#define POLYGONFACTORY_H_

#include "Vector2.h"
#include "Polygon.h"

namespace candy {

	/**
	 * @class PolygonFactory
	 * Factoria de polygonos que permite hacer formas simples
	 */
	class PolygonFactory {
	public:
		/**
		 * Devuelve un poligono con forma rectangular (con un ancho y un alto)
		 * @param centro Centro de la figura
		 * @param alto Alto de la figura
		 * @param ancho Ancho de la figura
		 * @return Poligono ya setteado con forma de cuadrado
		 */
		static Polygon Cuadrado(Vector2 centro, float ancho, float alto);

		/**
		 * Devuelve un poligono con forma circular (con un radio)
		 * @param centro Centro del circulo
		 * @param radio Radio del circulo
		 * @return Poligono ya setteado con forma de circulo
		 */
		static Polygon Circulo(Vector2 centro, float radio);

		/**
		 * Devuelve un poligono generico con un numero de segmentos arbitrario
		 * @param centro Centro del poligono
		 * @param radio Radio del poligono (hasta los vertices)
		 * @param num_lados Numero de lados
		 * @return Polygono ya setteado
		 */
		static Polygon Poligono(Vector2 centro, float radio, int num_lados);
	};

} /* namespace candy */
#endif /* POLYGONFACTORY_H_ */
