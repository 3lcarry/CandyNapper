/*
 * Plane.h
 *
 *  Created on: 09/03/2012
 *      Author: kaseyo
 */

#ifndef PLANE_H_
#define PLANE_H_

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
	 * @class Plane
	 * @brief Hereda de GNode y representa un plano (un cuadrado)
	 */
	class Plane : public GNode{
	public:
		/**
		 * Constructor por defecto
		 */
		Plane();

		/**
		 * Destructor por defecto
		 */
		~Plane();

		/**
		 * Renderiza el plano
		 * @param seleccion
		 */
		void Render(bool seleccion);

		/**
		 * Setter del id de la textura
		 * @param id ID de la texturas
		 */
		void setTexture(int id);

		/**
		 * Setter del color
		 * @param c Color
		 */
		void setColor(Color c);

	private:

		/**
		 * Color del plano
		 */
		Color _color;

		/**
		 * Textura (por si tuviera una textura)
		 */
		int _idTextura;
	};

} /* namespace candy */
#endif /* PLANE_H_ */
