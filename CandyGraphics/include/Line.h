/*
 * Line.h
 *
 *  Created on: 17/02/2012
 *      Author: kaseyo
 */

#ifndef LINE_H_
#define LINE_H_

#include "GNode.h"
#include "CandyMath.h"
#include "Color.h"
#include "OpenGL.h"

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */
	/**
	 * @class Line
	 * Representa una linea normal dibujada con OpenGL. Util para hacer la mirilla
	 */
	class Line : public GNode {
	public:
		/**
		 * Constructor
		 * @param puntoFinal Punto final (desde el origen) hacia el que se dirige la recta
		 * @param color Color de la recta
		 */
		Line(Vector3 puntoFinal, Color color, bool punteada);

		/**
		 * Sobrecarga del constructor. Pinta una linea entre dos puntos
		 * @param puntoInit Punto inicial
		 * @param puntoFinal Punto final
		 * @param color Color de la linea
		 * @param punteada Punteada o no
		 */
		Line(Vector3 puntoInit, Vector3 puntoFinal, Color color, bool punteada);

		/**
		 * Destructor
		 */
		~Line();

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		Line(const Line& cop);

		/**
		 * Asignacion
		 * @param cop Origen de la asignacion
		 * @return Referencia al resultado
		 */
		Line& operator=(const Line& cop);

		/**
		 * Metodo que renderiza la linea dibujandola desde el origen al punto final.
		 * @param seleccion Indica si estamos renderizando en modo seleccion
		 */
		void Render(bool seleccion);

		/**
		 * Settea el color de la linea
		 * @param color Color de la linea
		 */
		void setColor(Color color);

		/**
		 * Settea el punto final de la linea
		 * @param puntoFinal Punto final de la linea
		 */
		void setPuntoFinal(Vector3 puntoFinal);

		/**
		 * Settea si queremos la linea punteada o no
		 * @param punteada TRUE si la queremos punteada
		 */
		void setPunteada(bool punteada);

		/**
		 * Settea el ancho de la linea
		 * @param width Ancho
		 */
		void setWidth(float width);

	private:
		/**
		 * Punto final hacia el que se dirige la recta (desde el origen)
		 */
		Vector3 c_final;

		/**
		 * Punto inicial
		 */
		Vector3 c_inicial;

		/**
		 * Color de la linea
		 */
		Color c_color;

		/**
		 * Ancho de la linea
		 */
		float _width;

		/**
		 * Indica si la linea la dibujamos punteada o no
		 */
		bool c_punteada;

		/**
		 * Funcion auxiliar que copia un objeto en otro
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const Line& cop);

	};

} /* namespace candy */
#endif /* LINE_H_ */
