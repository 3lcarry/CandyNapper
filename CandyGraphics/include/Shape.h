/*
 * Polygon.h
 *
 *  Created on: 08/02/2012
 *      Author: kaseyo
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Color.h"
#include "GNode.h"
#include "CandyMath.h"
#include "OpenGL.h"

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */
	/**
	 * @class Polygon
	 * @brief Hereda de GNode y representa un poligono plano en el espacio.
	 */
	class Shape : public GNode {
	public:
		/**
		 * Constructor que recibe un numero de lados y un color
		 * @param numLados Numero de lados
		 * @param color Color del poligono
		 */
		Shape(int numLados, Color color);

		/**
		 * Destructor por defecto
		 */
		~Shape();

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		Shape(const Shape& cop);

		/**
		 * Operador asignacion
		 * @param cop Origen de la copia
		 * @return Resultado de la copia
		 */
		Shape& operator=(const Shape& cop);

		/**
		 * Metodo heredado de GNode que implementa Polygon
		 */
		void Render(bool seleccion);

		/**
		 * Settea la textura del poligono
		 * @param id ID de la textura en el gestor de recursos
		 */
		void setTexture(int id);

	private:
		/**
		 * Numero de lados del poligono
		 */
		int c_numLados;

		/**
		 * ID de la textura en el gestor de recursos
		 */
		int _idTextura;

		/**
		 * Color del poligono
		 */
		Color c_color;

		/**
		 * Funcion auxiliar que copia un objeto en otro
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const Shape& cop);
	};

} /* namespace candy */
#endif /* POLYGON_H_ */
