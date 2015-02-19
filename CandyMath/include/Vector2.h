/*
 * Vector2.h
 *
 *  Created on: 14/02/2012
 *      Author: kaseyo
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_
#include <iostream>

#include "Vector3.h"

using namespace std;

namespace candy {
	/**
	 * @class Position
	 * @brief Punto en el espacio 3D.
	 * Punto en el espacio en 3D, es decir, que almacena tres componentes (x, y, z).
	 */
	class Vector2{
	public:
		/**
		 * Sobrecarga del operador salida para la clase Position
		 * @param os Ostream de salida
		 * @param pos Position que imprimimos
		 * @return Ostream modificados
		 */
		friend ostream& operator<<(ostream& os, const Vector2& pos);

		/**
		 * Constructor por defecto, que inicializa las componentes a 0,0,0.
		 */
		Vector2();

		/**
		 * Constructor a partir de 3 coordenadas
		 * @param x Coordenada X
		 * @param y Coordenada Y
		 */
		Vector2(float x, float y);

		/**
		 * Destructor por defecto
		 */
		~Vector2();

		/**
		 * Constructor de copia
		 * @param cop Origen de la copia
		 */
		Vector2(const Vector2& cop);

		/**
		 * Operador asignacion
		 * @param cop Origen de la copia
		 * @return Resultado de la copia
		 */
		Vector2& operator=(const Vector2& cop);

		/**
		 * Getter de la componente X;
		 * @return Componente X
		 */
		float getX() const;

		/**
		 * Getter de la componente Y;
		 * @return Componente Y
		 */
		float getY() const;

		/**
		 * Setter de la componente X
		 * @param x Componente X deseada
		 */
		void setX(float x);

		/**
		 * Setter de la componente Y
		 * @param x Componente Y deseada
		 */
		void setY(float y);

		/**
		 * Compara dos Vector2
		 * @param v Vector que comparamos
		 * @return TRUE si son iguales
		 */
		bool operator==(const Vector2& v);

		/**
		 * Compara dos vectores
		 * @param v Vector que comparamos
		 * @return TRUE si son distintos
		 */
		bool operator!=(const Vector2& v);

	    /**
	     * Operador resta de Vector2
	     * @param v2 Segundo operando
	     * @return Resultado de la resta
	     */
	    Vector2 operator-(const Vector2& v2) const;

	    /**
	     * Operador suma de Vector2
	     * @param v2 Segundo operando
	     * @return Resultado de la suma
	     */
	    Vector2 operator+(const Vector2& v2) const;

		/**
		 * Calcula el modulo (distancia) entre dos puntos
		 * @param v Punto con el que comparamos
		 * @return Distancia entre nosotros y el punto
		 */
		float Distancia(const Vector2& v) const;

		/**
		 * Modulo del vector
		 * @return Modulo
		 */
		float Modulo() const;

		/**
		 * Operador de casting a Vector3
		 */
		operator Vector3 () const;

	private:
		/**
		 * Componente X
		 */
		float c_x;

		/**
		 * Componente Y
		 */
		float c_y;

		/**
		 * Copia un objeto en otro
		 * @param cop Origen de la copia
		 */
		void copiarDesde(const Vector2 & cop);

	};
}
#endif /* VECTOR2_H_ */
