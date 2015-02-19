/*
 * Box.h
 *
 *  Created on: 29/02/2012
 *      Author: kaseyo
 */

#ifndef BOX_H_
#define BOX_H_

#include "GNode.h"
#include "Plane.h"

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */
	/**
	 * @class Box
	 * Representa una caja, con una textura pegada por dentro. Es util para hacer SkyBoxes y cosas por el estilo.
	 * Es de tamanyo 1x1x1
	 */
	class Box : public GNode {
	public:
		/**
		 * Enum que representa las caras de la caja
		 */
		enum Face {
			Front, //!< Front
			Back,  //!< Back
			Top,   //!< Top
			Bottom,//!< Bottom
			Left,  //!< Left
			Right  //!< Right
		};

		/**
		 * Constructor por defecto (pone las texturas a -1)
		 */
		Box();

		/**
		 * Constructor pasandole las texturas
		 * @param idFront ID de la textura del frente
		 * @param idBack ID de la textura de detras
		 * @param idTop ID de la textura de arriba
		 * @param idBottom ID de la textura de bottom
		 * @param idLeft ID de la textura de la izquierda
		 * @param idRight ID de la textura de la derecha
		 */
		Box(int idFront, int idBack, int idTop, int idBottom, int idLeft, int idRight);

		/**
		 * Destructor por defecto
		 */
		~Box();

		/**
		 * Metodo heredado de IComponent
		 * @param seleccion Indica si estamos en modo seleccion
		 */
		void Render(bool seleccion);

		/**
		 * Setter del color por defecto si no hay textura
		 * @param color Color
		 */
		void setColor(Color color);

	private:
		/**
		 * Vector que guarda las texturas de la caja
		 */
		Plane* _planos[6];

		/**
		 * Metodo encargado de iniciar los planos
		 */
		void init();
	};

} /* namespace candy */
#endif /* BOX_H_ */
