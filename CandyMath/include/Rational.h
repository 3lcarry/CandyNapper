/*
 * Rational.h
 *
 *  Created on: 10/01/2012
 *      Author: kaseyo
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <iostream>
#include <vector>
using namespace std;

#include "Common.h"

namespace candy {
/**
 * @class Rational
 * Numero racional almacenado como fraccion
 */
class Rational {
public:
	/**
	 * Operador salida via ostream.
	 * @param os Ostream de salida
	 * @param rat Rational que imprimimos
	 * @return Referencia al ostream resultante
	 */
	friend ostream& operator<<(ostream& os, const Rational& rat);

	/**
	 * Rational precreado que representa el cero
	 */
	static const Rational Cero;

	/**
	 * Rational precreado que representa el uno
	 */
	static const Rational Uno;

	/**
	 * Constructor por defecto que inicializa los valores a 0/1
	 */
	Rational();

	/**
	 * Constructor a partir de un numerador y un denominador
	 * @param numerador Numerador de la fraccion
	 * @param denominador Denominador de la fraccion
	 */
	Rational(long long numerador, long long denominador);

	/**
	 * Constructor a partir de un solo entero (numerador/1). Sirve para castear desde entero.
	 * @param numerador Numerador de la fracci�n
	 */
	Rational(long long numerador);

	/**
	 * Constructor a partir de un entero
	 * @param numerador Numerador
	 */
	Rational(int numerador);

	/**
	 * Constructor a partir de float. Es decir, pasa de float a fraccion.
	 * @param decimal Float en decimal del que queremos obtener la fraccion.
	 */
	Rational(float decimal);

	/**
	 * Constructor a partir de double. Es decir, pasa de double a fraccion. Es necesaria, por que si no especificamos,
	 * un numero con punto es Double. No obstante, hace lo mismo que a partir de float
	 * @param decimal Double en decimal del que queremos obtener la fraccion.
	 */
	Rational(double decimal);

	/**
	 * Destructor por defecto
	 */
	~Rational();

	/**
	 * Constructor de copia.
	 * @param cop Origen de la copia.
	 */
	Rational(const Rational& cop);

	/**
	 * Operador asignacion.
	 * @param cop Origen de la copia.
	 * @return Referencia al resultado de la copia.
	 */
	Rational& operator=(const Rational& cop);

	/**
	 * Operador de casting a float. Si c_den es 0, devolvera 0 y mostrar� un error.
	 * @return Devuelve la division entre c_num y c_den
	 */
	operator float () const;

	/**
	 * Operador suma
	 * @param otro Segundo sumando
	 * @return Resultado de la suma
	 */
	Rational operator+(const Rational& otro) const;

	void operator+=(const Rational& otro);

	/**
	 * Operador resta
	 * @param otro Segunda parte de la operacion
	 * @return Resultado de la resta
	 */
	Rational operator-(const Rational& otro) const;

	void operator-=(const Rational& otro);


	/**
	 * Operador '-' para negar un rational
	 * @return Rational en negativo
	 */
	Rational operator-() const;

	/**
	 * Operador producto
	 * @param otro Segunda parte de la multiplicacion
	 * @return Resultado del producto
	 */
	Rational operator*(const Rational& otro) const;

	void operator*=(const Rational& otro);


	/**
	 * Operador division
	 * @param otro Segunda parte de la division
	 * @return Resultado de la division
	 */
	Rational operator/(const Rational& otro) const;

	void operator/=(const Rational& otro);


	/**
	 * Operador division
	 * @param otro Segunda parte de la division
	 * @return Resultado de la division
	 */
	Rational operator/(long long otro) const;

	void operator/=(long long otro);


	/**
	 * Crea el rational inverso
	 * @return La fraccion inversa
	 */
	Rational Inversa() const;

	/**
	 * Compara un rational con otro
	 * @param otro Rat con el que comparamos
	 * @return TRUE si son iguales
	 */
	bool operator==(const Rational& otro) const;

	/**
	 * Compara un rational con otro
	 * @param otro Rat con el que comparamos
	 * @return TRUE si son distintos
	 */
	bool operator!=(const Rational& otro) const;

	/**
	 * Compara un rational con otro
	 * @param otro Rat con el que comparamos
	 * @return TRUE si es menor o igual
	 */
	bool operator<=(const Rational& otro) const;

	bool operator<(const Rational& otro) const;

	/**
	 * Compara un rational con otro
	 * @param otro Rat con el que comparamos
	 * @return TRUE si es mayor o igual
	 */
	bool operator>=(const Rational& otro) const;

	bool operator>(const Rational& otro) const;

	/**
	 * Obtiene el numerador de la fraccion
	 */
	long long getNumerador() const;

	/**
	 * Obtiene el denominador de la fraccion
	 */
	long long getDenominador() const;

	/**
	 * Redondea al valor minimo
	 * @param r Valor que redondeamos
	 * @return Redondeo al minimo
	 */
	Rational RoundMin() const;

	/**
	 * Redondea al valor maximo
	 * @param r Valor que redondeamos
	 * @return Redondeo al maximo
	 */
	Rational RoundMax() const;

	/**
	 * Indica si el rational es entero (den == 1)
	 * @return TRUE si es entero
	 */
	bool isEntero() const;

private:
	/**
	 * Numerador de la fraccion
	 */
	long long c_num;

	/**
	 * Denominador de la fraccion
	 */
	long long c_den;

	/**
	 * Mensaje de error de division por 0 (1� parte)
	 */
	static const string ERROR_1;

	/**
	 * Mensaje de error de division por 0 (2� parte)
	 */
	static const string ERROR_2;

	/**
	 * Numero de decimales que se consideran a la hora de pasar
	 * de un float a una fraccion
	 */
	static const int NUM_DEC;

	/**
	 * Funcion auxiliar que copia un objeto Rational en el nuestro
	 * @param cop Origen de la copia
	 */
	void copiarDesde(const Rational& cop);

	/**
	 * Simplifica la fraccion
	 */
	void simplificar();
};

} /* namespace candy */
#endif /* RATIONAL_H_ */
