/*
 * Grafp.h
 *
 *  Created on: 23/02/2012
 *      Author: esteve
 */

#ifndef GRAFP_H_
#define GRAFP_H_
#include "Nodo.h"
#include "poly2tri/poly2tri.h"

namespace candy{
	/**
	 * @class Grafo
	 *
	 */
	class Grafo {
	private:
		/**
		 * Vector de triangulos que componen el grafo
		 */
		vector<p2t::Triangle*> Triangulos;

		/**
		 * Vector de nodos que componen el grafo
		 */
		vector<Nodo*> Nodos;

		/**
		 * Funcion que genera el grafo en base a los incentros de los triangulos
		 */
		void GenerarGrafo();

		/**
		 * Busca una posicion en el grafo
		 * @param pos Posicion en la que deberia estar el nodo
		 * @return Puntero al nodo
		 */
		Nodo* existeNodo(Vector2 pos);

	public:

		/**
		 * Genera el grafo en base
		 * @param t
		 * @param obs
		 */
		Grafo(vector<p2t::Triangle*> t);

		/**
		 * Constructor de copia
		 * @param g
		 */
		Grafo(const Grafo& g);

		/**
		 * Operador asignacion
		 * @param g Origen de la copia
		 * @return Resultado de la asignacion
		 */
		Grafo& operator=(const Grafo &g);

		/**
		 * Destructor
		 */
		~Grafo();

		/**
		 * Devuelve los nodos del grafo
		 * @return Vector de punteros a nodos
		 */
		vector<Nodo*> getGrafo();

		/**
		 * Devuelve un vector de triangulos
		 * @return Vector de triangulos
		 */
		vector<p2t::Triangle*> getTriangulos();

		/**
		 * Pone todos los nodos a no-visitados
		 */
		void Reset();

		/**
		 * Funcion auxiliar que copia un grafo en otro
		 * @param g Origen de la copia
		 */
		void copiarDesde(const Grafo& g);

	};
}

#endif /* GRAFP_H_ */
