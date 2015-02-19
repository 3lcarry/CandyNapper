/*
 * Problema.h
 *
 *  Created on: 29/03/2012
 *      Author: kaseyo
 */

#ifndef PROBLEMA_H_
#define PROBLEMA_H_

#include "Funcion.h"
#include "Matrix.h"
#include <vector>
#include <iostream>
using namespace std;

namespace candy {

	/**
	 * @class Problema
	 * Representa un problema de optimizacion (con una funcion objetivo, y una serie de restricciones)
	 */
	class Problema {
		/**
		 * Operador salida
		 * @param os Ostream de salida
		 * @param prob Problema que mostramos
		 * @return Ostream modificado
		 */
		friend ostream& operator<<(ostream& os, const Problema& prob);
	public:
		/**
		 * Enum que guarda el tipo de problema a resolver (MAXimizar o MINinimizar)
		 */
		enum TipoProblema{
			MAX,//!< MAX
			MIN, //!< MIN
			_MIN, //!< -MIN
		};

		/**
		 * Constructor por defecto
		 */
		Problema();

		/**
		 * Destructor
		 */
		~Problema();

		/**
		 * Constructor a partir de una serie de strings (el primero debe ser la funcion objetivo)
		 * @param problema Problema
		 */
		Problema(vector<string> problema);

		/**
		 * Constructor de copia
		 * @param prob Problema
		 */
		Problema(const Problema& prob);

		/**
		 * Operador asignacion
		 * @param prob Origen de la copia
		 * @return Resultado de la copia
		 */
		Problema& operator=(const Problema& prob);

		/**
		 * Anyade una restriccion al problema
		 * @param f Funcion
		 */
		void addRestriccion(const Funcion& f);

		/**
		 * Settea el tipo de problema
		 * @param tipo MAX o MIN
		 */
		void setObjetivo(TipoProblema tipo);

		/**
		 * Settea la funcion objetivo
		 * @param f Funcion
		 */
		void setFuncObjetivo(const Funcion& f);

		/**
		 * Devuelve las variables del problema
		 * @return Vector con los indices de las variables existentes en el problema
		 */
		list<int> getVariables() const;

		/**
		 * Normaliza el problema
		 */
		void Normalizar();

		/**
		 * Normaliza, multiplicando por -1, las restricciones mayoresque
		 * (para que quede identidad)
		 */
		void NormalizarDual();

		/**
		 * Devuelve la mejor base
		 * @return Devuelve la mejor base posible
		 */
		Matrix ObtenerBase();

		/**
		 * Devuelve las variables basicas para la primera base
		 * @return Vector de enteros con los indices de las variables basicas
		 */
		vector<int> ObtenerBasicas();

		/**
		 * Devuelve la matriz columna D
		 * @return
		 */
		Matrix ObtenerD() const;

		Matrix ObtenerColumna(int col) const;

		Rational ObtenerCoeficienteFuncion(int col) const;

		vector<int> ObtenerNoBasicas(vector<int> basicas) const;

		Funcion getFuncObjetivo() const;

		TipoProblema getTipoProblema() const;

		vector<int> getArtificiales() const;

		/**
		 * Calcula que variables forman parte de la base identidad
		 * En cada componente del vector, guardamos el numero de restriccion a la que pertenece
		 * la variable "identidad" (el uno de la identidad), o -1 si no pertenece a la base identidad
		 * @return
		 */
		vector<int> getIdentidadBase() const;

		/**
		 * Anyade variables artificiales al problema, de manera que tengamos la
		 * matriz identidad para empezar
		 */
		void addArtificiales();

		/**
		 * Indica si hay algun elemento negativo en d
		 * @return TRUE si se encuentra algun elem negativo
		 */
		bool hayNegEnD() const;

	private:
		/**
		 * Lee el problema desde una serie de strings
		 * @param Problema Problema abaseInv = baseInv.Inversa(); tratar
		 */
		void read(vector<string> Problema);

		/**
		 * Funcion auxiliar que copia
		 * @param p Origen de la copia
		 */
		void copiarDesde(const Problema& p);

		/**
		 * Array con las restricciones del problema
		 */
		vector<Funcion> _restricciones;

		/**
		 * Funcion objetivo
		 */
		Funcion _funcObjetivo;

		/**
		 * Tipo de problema (MAX o MIN)
		 */
		TipoProblema _tipo;

		/**
		 * Variables artificiales del problema (las marcamos para cuando haya que eliminarlas)
		 */
		vector<int> _artificiales;
	};

} /* namespace candy */
#endif /* PROBLEMA_H_ */
