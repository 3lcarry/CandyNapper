/*
 * Transformation.h
 *
 *  Created on: 17/11/2011
 *      Author: kaseyo
 */

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include "GNode.h"
#include "MatrixStack.h"
#include "CandyMath.h"
#include "OpenGL.h"

namespace candy {
/**
 * \addtogroup CandyGraphics
 * @{
 */
	/**
	 * @class Transformation
	 * Representa las transformaciones que se le realizar�n a un Object (o varios) en nuestro motor gr�fico,
	 * tales como traslaciones, escalados, etc.
	 */
	class Transformation: public GNode
	{
	public:
		/**
		 * Constructor por defecto
		 */
		Transformation();

		/**
		 * Destructor por defect
		 */
		~Transformation();

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		Transformation(const Transformation& cop);

		/**
		 * Operador asignacion del constructor de copia
		 * @param cop Origen de la copia
		 * @return Referencia al resultado de la copia
		 */
		Transformation& operator=(const Transformation& cop);

		/**
		 * Metodo que hereda de GraphicalNode. Hace un glPushMatrix y carga la matriz actual
		 */
		void Render(bool seleccion);

		/**
		 * Multiplica la matriz actual por una de traslacion a la posicion actual + p
		 * @param p Distancia que nos trasladamos
		 */
		void Translate(Vector3 p);

		/**
		 * Multiplica la matriz actual por una de traslacion a la posicion actual + p (Version 2D)
		 * @param p Distancia que nos trasladamos
		 */
		void Translate(Vector2 p);

		/**
		 * Multiplica la matriz actual por una de traslacion a la posicion actual + p
		 * @param x Distancia x
		 * @param y Distancia y
		 * @param z Distancia z
		 */
		void Translate(float x, float y, float z = 0);

		/**
		 * Multiplica la matriz actual por una de rotacion, indicando el eje y los angulos
		 * @param eje Indica en que eje rotamos (puede ser 0-x, 1-y o 2-z).
		 * @param grados Grados que rotamos
		 */
		void Rotate(int eje, float grados);

		/**
		 * Rota alrededor de un eje generico
		 * @param eje Vector que representa el eje
		 * @param grados Grados que rotamos
		 */
		void Rotate(Vector3 eje, float grados);

		/**
		 * Multiplica la matriz actual por una de escalado, indicandole mediante una Position lo que escalamos.
		 * @param p Escalado en cada Eje
		 */
		void Scale(Vector3 p);

		/**
		 * Multiplica la matriz actual por una de escalado, indicandole mediante una Position lo que escalamos. (Version 2D)
		 * @param p Escalado en cada Eje
		 */
		void Scale(Vector2 p);

		/**
		 * Multiplica la matriz actual por una de escalado, indicandole mediante una Position lo que escalamos.
		 * @param x Escalado en x
		 * @param y Escalado en y
		 * @param z Escalado en z
		 */
		void Scale(float x, float y, float z = 1);

		/**
		 * Devuelve la matriz actual (no la formato OpenGL)
		 * @return Matrix actual
		 */
		Mat4 getMatrix();

		/**
		 * Devuelve una matriz de escalado (pero no la aplica ni nada)
		 * @param p Vector de escalado
		 * @return Matriz de 4x4 con la transformacion
		 */
		static Mat4 getScaleMatrix(Vector3 p);

		/**
		 * Devuelve una matriz de escalado (pero no la aplica ni nada) (version 2D)
		 * @param p Vector de escalado
		 * @return Matriz de 4x4 con la transformacion
		 */
		static Mat4 getScaleMatrix(Vector2 p);

		/**
		 * Devuelve una matriz de escalado (pero no la aplica ni nada)
		 * @param x Escalado en X
		 * @param y Escalado en Y
		 * @param z Escalado en Z
		 * @return Matriz de 4x4 con la transformacion
		 */
		static Mat4 getScaleMatrix(float x, float y, float z = 1);

		/**
		 * Devuelve una matriz de translacion (pero no la aplica)
		 * @param p Vector de translacion
		 * @return Matriz de 4x4 con la transformacion
		 */
		static Mat4 getTranslateMatrix(Vector3 p);

		/**
		 * Devuelve una matriz de translacion (pero no la aplica) (version 2D)
		 * @param p Vector de translacion
		 * @return Matriz de 4x4 con la transformacion
		 */
		static Mat4 getTranslateMatrix(Vector2 p);

		/**
		 * Devuelve una matriz de translacion (pero no la aplica)
		 * @param x Translacion en X
		 * @param y Translacion en Y
		 * @param z Translacion en Z
		 * @return Matriz de 4x4 con la transformacion
		 */
		static Mat4 getTranslateMatrix(float x, float y, float z = 0);

		/**
		 * Devuelve una matriz de rotacion (pero no la aplica)
		 * @param eje Eje sobre el que rotamos
		 * @param grados Grados que rotamos
		 * @return
		 */
		static Mat4 getRotateMatrix(int eje, float grados);

		/**
		 * Genera una matriz que rota alrededor de un eje generico
		 * @param eje Vector que representa nuestro eje
		 * @param grados Grados que rotamos alrededor del eje
		 * @return Matriz creada
		 */
		static Mat4 getRotateMatrix(Vector3 eje, float grados);

		/**
		 * Permite mover a una posicion directamente (no incremental, como Translate).
		 * @param translacion Posicion deseada
		 */
		void setTranslation(Vector3 translacion);

		/**
		 * Permite mover a una posicion directamente (no incremental, como Translate) (version 2D)
		 * @param translacion Posicion deseada
		 */
		void setTranslation(Vector2 translacion);

		/**
		 * Permite mover a una posicion directamente (no incremental, como Translate).
		 * @param x Coordenada X de la posicion
		 * @param y Coordenada Y de la posicion
		 * @param z Coordenada Z de la posicion
		 */
		void setTranslation(float x, float y, float z = 0);

		/**
		 * Permite rotar la transformacion a un angulo especifico.
		 * @param eje Eje sobre el que rotamos
		 * @param grados Grados que rotamos
		 */
		void setRotation(int eje, float grados);

		/**
		 * Permite rotar la transformacion a un angulo especifico sobre un eje generico.
		 * @param eje Eje sobre el que rotamos
		 * @param grados Grados que rotamos
		 */
		void setRotation(Vector3 eje, float grados);

		/**
		 * Permite escalar la transformacion a una proporcion especifica
		 * @param escalado Vector de escalado
		 */
		void setScalation(Vector3 escalado);

		/**
		 * Permite escalar la transformacion a una proporcion especifica (version 2D)
		 * @param escalado Vector de escalado
		 */
		void setScalation(Vector2 escalado);

		/**
		 * Permite escalar la transformacion a una proporcion especifica
		 * @param x Componente X del escalado
		 * @param y Componente Y del escalado
		 * @param z Componente Z del escalado
		 */
		void setScalation(float x, float y, float z = 1);

		/**
		 * Setter del flag de order
		 * @param order TRUE si queremos que importe el orden
		 */
		void setOrder(bool order);

	private:
		/**
		 * Matriz que almacena la transformacion compuesta
		 */
		Mat4 c_matriz;
		/**
		 * Matriz que guarda la traslacion actual
		 */
		Mat4 c_matTranslacion;

		/**
		 * Matriz que guarda la rotaciona actual
		 */
		Mat4 c_matRotacion;

		/**
		 * Matriz que guarda el escalado actual
		 */
		Mat4 c_matEscalado;

		/**
		 * Puntero a la pila de matrices
		 */
		static MatrixStack* c_pila;

		/**
		 * Funcion auxiliar que copia un objeto en otro
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const Transformation& cop);

		/**
		 * Flag que indica si queremos que importe o no el orden en que indicamos las transformaciones
		 */
		bool c_order;

	};

} /* namespace candy */
#endif /* TRANSFORMATION_H_ */
