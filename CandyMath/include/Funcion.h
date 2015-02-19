/*
 * Function.h
 *
 *  Created on: 22/03/2012
 *      Author: kaseyo
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "Termino.h"
#include "Rational.h"

#include <iostream>
#include <list>
#include <vector>
using namespace std;

namespace candy {

	/**
	 * @class Function
	 * Representa una funcion matematica, con una serie de terminos (coeficientes + variables), un tipo (<, <=, >, >= o =) y un resultado.
	 * Permite leerse desde un string (parseandolo) con la siguiente sintaxis:
	 * 	coef1*Xvar1 + coef2*Xvar2 - coef3*Xvar3 + ... + coefN*XvarN [= | < | <= | > | >= ] resultado
	 */
	class Funcion {
		friend ostream& operator<<(ostream& os, const Funcion& func);

	public:

		/**
		 * Tipo de la funcion
		 * @return Tipo de funcion (>, <, <=, >= o =)
		 */
		enum TipoFuncion{
			MayorQue,
			MayorIgual,
			MenorQue,
			MenorIgual,
			Igual,
			Nada
		};

		/**
		 * Constructor por defecto
		 */
		Funcion();

		/**
		 * Constructor a partir de un string (parseando)
		 * @param funcion String de la funcion
		 */
		Funcion(string funcion);

		/**
		 * Constructor a partir de los terminos de una funcion
		 * @param terminos
		 */
		Funcion(const list<Termino>& terminos);

		/**
		 * Destructor
		 */
		~Funcion();

		/**
		 * Constructor de copia
		 * @param func Origen de la copia
		 */
		Funcion(const Funcion& func);

		/**
		 * Operador asignacion
		 * @param func Origen de la copia
		 * @return Resultado de la copia
		 */
		Funcion& operator=(const Funcion& func);

		/**
		 * Niega la funcion
		 * @return Funcion negada
		 */
		Funcion operator-() const;

		/**
		 * Devuelve la lista ordenada de indices de variables
		 * @return Lo de arriba
		 */
		list<int> getVariables() const;

		TipoFuncion getTipo() const;

		void setTipo(TipoFuncion tipo);

		void setResultado(Rational r);

		void addTermino(const Termino& ter);

		Rational getCoeficiente(int var) const;

		Rational getResultado() const;

		Rational getResultado(vector<int> indices, vector<Rational> valores) const;

	private:
		/**
		 * Funcion auxiliar que nos copia una funcion
		 * @param func Origen de la copia
		 */
		void copiarDesde(const Funcion& func);

		/**
		 * Parsea un string en el formato indicado
		 * @param funcion String de la funcion
		 */
		void read(string funcion);

		/**
		 * Parte una cadena
		 * @param cadena Cadena a partir
		 * @param separador Separador por el que partimos
		 * @return Vector con los cachos separados
		 */
		vector<string> split(string cadena, char separador);

		/**
		 * Lista de terminos, que componen la funcion
		 */
		list<Termino> _funcion;

		/**
		 * Resultado de la funcion
		 */
		Rational _resultado;

		/**
		 * Tipo de funcion
		 */
		TipoFuncion _tipo;

	};

} /* namespace candy */
#endif /* FUNCTION_H_ */
