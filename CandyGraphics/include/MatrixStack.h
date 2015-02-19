/*
 * MatrixStack.h
 *
 *  Created on: 12/02/2012
 *      Author: kaseyo
 */

#ifndef MATRIXSTACK_H_
#define MATRIXSTACK_H_

#include <stack>
#include <iostream>
#include "CandyMath.h"
#include "OpenGL.h"
using namespace std;

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */

	/**
	 * @class MatrixStack
	 * @brief Pila de matrices
	 * Pila de matrices, similar a las implementadas por OpenGL con glPush y glPop, pero implementada por nosotros
	 * y sin ningun limite. Ademas, guarda cual es la matriz "actual". Dado que debe ser accesible desde muchos puntos
	 * del codigo, es Singleton.
	 */
	class MatrixStack {
	public:
		/**
		 * Destructor por defecto
		 */
		~MatrixStack();

		/**
		 * Extra la cabeza de la pila. Este metodo se encarga
		 * tambien de pasarsela a OpenGL como la matriz actual
		 */
		void Pop();

		/**
		 * Guarda en la pila la matriz actual que usa OpenGL
		 */
		void Push();

		/**
		 * Devuelve la cima de la pila
		 * @return Cima de la pila
		 */
		Mat4 Top();

		/**
		 * Devuelve la matriz actual, es decir, la que esta usando OpenGL en estos momentos
		 * @return Matriz actualmente usada por OpenGL
		 */
		Mat4 Actual();

		/**
		 * Settea la matriz actual usada por OpenGL
		 * @param actual
		 */
		void setActual(const Mat4& actual);

		/**
		 * Devuelve un puntero a la pila de matrices
		 * @return
		 */
		static MatrixStack* getInstance();

		/**
		 * Inicializa la pila (similar a glLoadIdentity)
		 */
		void Init();

	private:
		/**
		 * Constructor por defecto, inicializa la pila. Lo metemos en
		 * private por que la clase es singleton.
		 */
		MatrixStack();

		/**
		 * Puntero que guarda la instancia actual
		 */
		static MatrixStack* c_instance;

		/**
		 * Variable que guarda la matriz actual
		 */
		Mat4 c_matrizActual;

		/**
		 * Variable que guarda la pila de matrices
		 */
		stack<Mat4> c_pilaMatrices;

	};

} /* namespace candy */
#endif /* MATRIXSTACK_H_ */
