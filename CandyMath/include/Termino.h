/*
 * Termino.h
 *
 *  Created on: 22/03/2012
 *      Author: kaseyo
 */

#ifndef TERMINO_H_
#define TERMINO_H_

#include "Rational.h"
#include <stdlib.h>

#include <iostream>
using namespace std;

namespace candy {

	/**
	 * @class Termino
	 * Termino de una funcion, compuesto de un coeficiente y una variable
	 */
	class Termino {
		friend ostream& operator<<(ostream& os, const Termino& ter);
	public:
		/**
		 * Constructor a partir de un coeficiente y una variable
		 * @param coef Coeficiente
		 * @param var Variable
		 */
		Termino(int coef, int var);

		/**
		 * Constructor a partir de un string
		 * @param termino Cadena con el termino
		 */
		Termino(string termino);

		/**
		 * Destructor
		 */
		~Termino();

		/**
		 * Constructor de copia
		 * @param ter Termino
		 */
		Termino(const Termino& ter);

		/**
		 * Operador asignacion
		 * @param ter Termino
		 * @return Resultado de la asignacion
		 */
		Termino& operator=(const Termino& ter);

		Termino operator-() const;

		/**
		 * Devuelve el indice de la variable
		 * @return Indice de la variable
		 */
		int getVarIndex() const;

		/**
		 * Devuelve el coeficiente de la variable
		 * @return Coeficiente de la variable
		 */
		Rational getCoef() const;

	private:
		/**
		 * Coeficiente del termino
		 */
		Rational _coeficiente;

		/**
		 * Indice de la variable
		 */
		int _variable;
	};

} /* namespace candy */
#endif /* TERMINO_H_ */
