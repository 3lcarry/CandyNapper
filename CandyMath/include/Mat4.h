/*
 * Mat4.h
 *
 *  Created on: 09/02/2012
 *      Author: kaseyo
 */

#ifndef MAT4_H_
#define MAT4_H_

#include <iostream>
using namespace std;

namespace candy {
	/**
	 * @class Mat4
	 * @brief Matriz de 4x4 pensada para el motor grafico.
	 * Matriz de 4x4 hecha para el motor grafico. Usa solo floats y punteros, por lo que es muy rapida.
	 */
	class Mat4 {
		friend ostream& operator<<(ostream& os, const Mat4& mat);
	public:
		/**
		 * Constructor por defecto que construye la matriz identidad
		 */
		Mat4();

		/**
		 * Constructor dando los valores de la matriz
		 * @param m00 Elem 0,0
		 * @param m01 Elem 0,1
		 * @param m02 Elem 0,2
		 * @param m03 Elem 0,3
		 * @param m10 Elem 1,0
		 * @param m11 Elem 1,1
		 * @param m12 Elem 1,2
		 * @param m13 Elem 1,3
		 * @param m20 Elem 2,0
		 * @param m21 Elem 2,1
		 * @param m22 Elem 2,2
		 * @param m23 Elem 2,3
		 * @param m30 Elem 3,0
		 * @param m31 Elem 3,1
		 * @param m32 Elem 3,2
		 * @param m33 Elem 3,3
		 */
		Mat4(float m00, float m01, float m02, float m03
				, float m10, float m11, float m12, float m13
				, float m20, float m21, float m22, float m23
				, float m30, float m31, float m32, float m33);

		/**
		 * Constructor de copia a partir de una matriz 4x4
		 * @param cop Origen de la copia
		 */
		Mat4(const Mat4& cop);

		/**
		 * Sobrecarga del operador asignacion
		 * @param cop Origen de la copia
		 * @return Resultado de la asignacion
		 */
		Mat4& operator=(const Mat4& cop);

		/**
		 * Destructor
		 */
		~Mat4();

		/**
		 * Devuelve la matriz como un puntero
		 * @return Puntero al array
		 */
		float* getMatrix();

		/**
		 * Devuelve el numero que ocupa la posicion i,j en la matriz. 0 por defecto.
		 * @param i Numero de fila
		 * @param j Numero de columna
		 * @return Numero en la posicion [i,j]
		 */
		 float operator()(int i, int j) const;

		 /**
		  * Inserta un numero en la posicion i, j. Si se pasa de rango devuelve el float "c_error".
		  * @param i Numero de fila
		  * @param j Numero de columna
		  */
		 float& operator()(int i, int j);

		 /**
		  * Operador suma de matrices
		  * @param m1 Matriz que sumamos
		  * @return Resultado de la suma
		  */
		 Mat4 operator+(const Mat4& m1) const;

		 /**
		  * Operador resta de matrices
		  * @param m1 Matriz que restamos
		  * @return Resultado de la resta
		  */
		 Mat4 operator-(const Mat4& m1) const;

		 /**
		  * Operador producto por un escalar (un racional)
		  * @param r1 Escalar que multiplicamos
		  * @return Resultado de la operacion
		  */
		 Mat4 operator*(float r1) const;

		 /**
		  * Operador producto por otra matriz
		  * @param m1 Matriz que multiplicamos
		  * @return Resultado de la multiplicacion
		  */
		 Mat4 operator*(const Mat4& m1) const;

	private:
		/**
		 * Funcion auxiliar que copia un objeto en otro
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const Mat4& cop);

		/**
		 * Dadas dos coordenadas, las traduce al sistema del array (de 2D a 1D)
		 * @param i Coordenada x
		 * @param j Coordenada y
		 * @return Coordenada en array
		 */
		int posicion(int i, int j) const;

		/**
		 * Variable auxiliar que se guarda la matriz
		 */
		float* c_mat4x4;

		/**
		 * Referencia a error (para cuando i, j se excede)
		 */
		static float c_error;
	};

} /* namespace candy */
#endif /* MAT4_H_ */
