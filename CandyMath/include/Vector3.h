/*
 * Point.h
 *
 *  Created on: 19/01/2012
 *      Author: kaseyo
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <iostream>

using namespace std;

namespace candy {
/**
 * @class Vector3
 * @brief Punto en el espacio 3D.
 * Punto en el espacio en 3D, es decir, que almacena tres componentes (x, y, z).
 */
class Vector3{
public:
	/**
	 * Sobrecarga del operador salida para la clase Position
	 * @param os Ostream de salida
	 * @param pos Position que imprimimos
	 * @return Ostream modificados
	 */
	friend ostream& operator<<(ostream& os, const Vector3& pos);

	/**
	 * Constructor por defecto, que inicializa las componentes a 0,0,0.
	 */
	Vector3();

	/**
	 * Constructor a partir de 3 coordenadas
	 * @param x Coordenada X
	 * @param y Coordenada Y
	 * @param z Coordenada Z
	 */
	Vector3(float x, float y, float z);

	/**
	 * Destructor por defecto
	 */
	~Vector3();

	/**
	 * Constructor de copia
	 * @param cop Origen de la copia
	 */
	Vector3(const Vector3& cop);

	/**
	 * Operador asignacion
	 * @param cop Origen de la copia
	 * @return Resultado de la copia
	 */
	Vector3& operator=(const Vector3& cop);

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
	 * Getter de la componente Z;
	 * @return Componente Z
	 */
    float getZ() const;

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
     * Setter de la componente Z
     * @param x Componente Z deseada
     */
    void setZ(float z);

    /**
     * Operador resta de Vector3
     * @param v2 Segundo operando
     * @return Resultado de la resta
     */
    Vector3 operator-(const Vector3& v2) const;

    /**
     * Operador suma de Vector3
     * @param v2 Segundo operando
     * @return Resultado de la suma
     */
    Vector3 operator+(const Vector3& v2) const;

    /**
     * Calcula el productor escalar entre dos vectores
     * @param v2 Segundo operando
     * @return Resultado del producto escalar
     */
    float operator*(const Vector3& v2) const;

    /**
     * Modulo del vector
     * @return Resultado del modulo
     */
    float Modulo() const;

    /**
     * Operador igualdad
     * @param v Vector con el que comparamos
     * @return TRUE si son iguales
     */
    bool operator==(const Vector3& v) const;

    /**
     * Operador diferencia
     * @param v Vector con el que comparamos
     * @return FALSE si son iguales
     */
    bool operator!=(const Vector3& v) const;

    /**
     * Calcula la distancia entre dos puntos
     * @param v2 Segundo operando
     * @return Distancia entre this y v2
     */
    float Distancia(const Vector3& v2) const;

    /**
     * Calcula el angulo entre dos vectores
     * @param v2 Segundo vector
     * @return Angulo en radianes entre los dos vectores
     */
    float Angulo(const Vector3& v2) const;

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
	 * Componente Z
	 */
    float c_z;

    /**
	 * Copia un objeto en otro
	 * @param cop Origen de la copia
	 */
    void copiarDesde(const Vector3 & cop);

};

} /* namespace candy */
#endif /* POINT_H_ */
