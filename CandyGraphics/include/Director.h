/*
 * DirectedCamera.h
 *
 *  Created on: 20/02/2012
 *      Author: kaseyo
 */

#ifndef DIRECTEDCAMERA_H_
#define DIRECTEDCAMERA_H_

#include "GNode.h"
#include "CandyMath.h"
#include "OpenGL.h"
#include "MatrixStack.h"

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */
	/**
	 * @class Director
	 * @brief Hereda de GNode y dirige la camara hacia un punto en el mapa (por tanto, deberia de llamarse despues de settear
	 * una perspectiva)
	 */
	class Director : public GNode {
	public:
		/**
		 * Constructor
		 * @param direccion Direccion en la que miramos
		 * @param ojo Coordenadas del "ojo"
		 * @param up Up-Vector
		 */
		Director(Vector3 ojo, Vector3 direccion, Vector3 up);

		/**
		 * Destructor por defecto
		 */
		~Director();

		/**
		 * Metodo heredado de GNode
		 * @param seleccion Indica si estamos en modo seleccion
		 */
		void Render(bool seleccion);

		/**
		 * Setter de la direccion de la camara
		 * @param direccion Direccion
		 */
		void setReference(Vector3 direccion);

		/**
		 * Setter de las coordenadas del ojo
		 * @param ojo Coordenadas del ojo
		 */
		void setCenter(Vector3 ojo);

		/**
		 * Setter del up-vector
		 * @param up Up-vector
		 */
		void setUp(Vector3 up);

	private:
		/**
		 * Direccion en la que mira la camara
		 */
		Vector3 c_direccion;

		/**
		 * Coordenadas del ojo
		 */
		Vector3 c_ojo;

		/**
		 * Up-vector
		 */
		Vector3 c_up;

		/**
		 * Puntero a la pila de matrices
		 */
		MatrixStack* _pila;
	};

} /* namespace candy */
#endif /* DIRECTEDCAMERA_H_ */
