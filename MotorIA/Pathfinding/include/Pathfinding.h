/*
 * Pathfinding.h
 *
 *  Created on: 24/02/2012
 *      Author: esteve
 */

#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include "Grafo.h"
#include "CandyMath.h"
#include "Timer.h"

namespace candy{
	/**
	 * @class Pathfinding
	 * Clase encargada de hacer el A*
	 */
	class Pathfinding {
	private:
		/**
		 * Estructura para el A*
		 */
		struct nodoAStar {
			Nodo* nodo;
			nodoAStar* padre;
			float F; // G + H
			float G; //distancia desde la posicion inicial al nodo
			float H; //estimacion de la distancia al final
			nodoAStar();
			nodoAStar(const nodoAStar &n);
			nodoAStar(Nodo* nodo_, nodoAStar* padre_, float F_, float G_, float H_);
			void setG(float G_);
			void setH(float H_);
			bool empty();
		};

		/**
		 * Grafo sobre el que ejecutamos el pathfinding
		 */
		Grafo* _grafo;

		/**
		 * Camino resultante
		 */
		vector<Nodo*> _camino;

		/**
		 * tiempo maximo a emplear en la busqueda del camino
		 */
		static const int tiempMax;

		/**
		 * Calcula el siguiente nodo a visitar en el CaminoVoraz
		 * @param nodo actual
		 * @param nodo final
		 * @return siguiente nodo
		 */
		Nodo* NodoFuturo(Nodo* n, Nodo* fin);

		/**
		 * Calcula un camino voraz que se utiliza para recotar las posibilidades del A*
		 * @param nodo inicial
		 * @param nodo final
		 * @return distancia del camino
		 */
		double CaminoVoraz(Nodo* init, Nodo* fin);

		/**
		 * Devuelve el nodoAStar buscado en la lista
		 * @param lista donde buscar
		 * @param nodo que buscar
		 * @return nodo encontrado
		 */
		nodoAStar getNodo(list<nodoAStar> lista, nodoAStar n);

		/**
		 * Inserta ordenado en la lista
		 * @param lista en la que insertar
		 * @param nodo que insertar
		 */
		void InsertarOrdenado(list<nodoAStar> &lista, nodoAStar nodo);

		/**
		 * Borra un nodo de la lista
		 * @param lista de la que borrar
		 * @param nodo que borrar
		 */
		void Borrar(list<nodoAStar> &lista, nodoAStar nodo);


	public:
		/**
		 * Constructor del pathfinding a partir del grafo
		 * @param grafo Grafo a partir del cual construimos
		 */
		Pathfinding(Grafo* grafo);

		/**
		 * Destructor
		 */
		~Pathfinding();

		/**
		 * Calcula el pathfinding entre dos puntos con A*
		 * @param init Punto inicio
		 * @param fin Punto fin
		 */
		void Calcular(Vector2 init, Vector2 fin);

		/**
		 * Devuelve el camino obtenido en el pathfinding
		 * @return Vector de nodos con el camino
		 */
		vector<Nodo*> getCamino();
	};
}

#endif /* PATHFINDING_H_ */
