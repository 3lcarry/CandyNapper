/*
 * SimplexSolver.h
 *
 *  Created on: 22/03/2012
 *      Author: kaseyo
 */

#ifndef SIMPLEXSOLVER_H_
#define SIMPLEXSOLVER_H_

#include "Rational.h"
#include "Problema.h"
#include "Matrix.h"
#include "SimplexHeap.h"
#include <vector>
using namespace std;

namespace candy {

	/**
	 * @class SimplexSolver
	 * Resuelve el simplex
	 */
	class SimplexSolver {
	public:
		enum ResultadoSimplex{
			SolEncontrada,
			SolNoExiste,
			SolNoAcotada
		};

		/**
		 * Constructor por defecto
		 */
		SimplexSolver();

		/**
		 * Destructor
		 */
		~SimplexSolver();

		Rational getOptimoFinal() const;

		SimplexSolver::ResultadoSimplex getEstado() const;

		vector<Rational> getSoluciones() const;

		Rational SimplexSolve(const Problema& p);

		Rational PenalizacionesSolve(const Problema& p);

		Rational DualSimplexSolve(const Problema& p);

		Rational IntSimplexSolve(const Problema& p);

	private:
		void cambiarBase(int varSale, int varEntra);

		int getVariableSalida(int varEntra);

		int getVariableEntra();

		int getVariableSalidaDual();

		int getVariableEntradaDual(int varSale);

		vector<Rational> getZJCJ();

		vector<Rational> getSolTemporales(vector<int> varObjetivo);

		/**
		 * Comprueba si el problema necesita una restriccion artificial.
		 * Si la necesita, se la a–ade
		 */
		void checkRestriccionArtificial();

		/**
		 * Para Simplex de enteros!!
		 * Indica si el nodo actual es una solucion valida.
		 * Sera valida si las variables de la funcion objetivo son variables enteras
		 * @return
		 */
		bool EsSolucion(const SimplexNode& sn);

		/**
		 * Para Simplex de enteros!!
		 * Indica si el nodo actual es una solucion peor que la actual.
		 * @return TRUE si es aceptable
		 */
		bool Aceptable(const SimplexNode& sn, const Rational& mejorOptimo, const vector<Rational>& mejorSolucion);

		/**
		 * Para Simplex de enteros!!
		 * Expande el nodo actual
		 * @param sn Nodo que expandimos
		 * @return Vector de nodos expandidos
		 */
		vector<SimplexNode> Expandir(const SimplexNode& sn);

		Rational getOptimo();

		Matrix base;

		Matrix baseInv;

		Problema prob;

		Matrix xb;

		ResultadoSimplex estado;

		/**
		 * Vector con las soluciones al simplex en las variables de la funcion objetivo
		 */
		vector<Rational> soluciones;

		/**
		 * Ultimo optimo conseguido
		 */
		Rational optimo;

		vector<int> variablesUsadas;
	};

} /* namespace candy */
#endif /* SIMPLEXSOLVER_H_ */
