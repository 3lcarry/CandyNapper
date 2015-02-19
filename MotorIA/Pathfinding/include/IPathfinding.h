/*
 * IPathfinding.h
 *
 *  Created on: 24/02/2012
 *      Author: esteve
 */

#ifndef IPATHFINDING_H_
#define IPATHFINDING_H_
#include "Grafo.h"
#include "poly2tri/poly2tri.h"
#include "Vector2.h"
#include "Polygon.h"
#include "CandyGraphics.h"

namespace candy{
class IPathfinding {
private:
	double exp;

	Polygon _contorno;

	Grafo* grafo;

	vector<Polygon> Obstaculos;

	//static IPathfinding* pInstance;

	//IPathfinding();
	/**
	 * Inicializa el mapa a un ancho y un alto
	 * @param mapX_ Ancho
	 * @param mapY_ Alto
	 * @param exp_ Expansion
	 */
	void Init(double mapX_, double mapY_,double exp_);

public:

	/**
	 * Constructor
	 * @param anchura del mapa
	 * @param altura del mapa
	 * @expansion de los polígonos
	 */
	IPathfinding(double mapX_, double mapY_, double exp_ = 1);

	/**
	 * Devuelve la instancia de la interfaz
	 * @return Puntero a la Interfaz
	 */
	//static IPathfinding* Instance();

	/**
	 * Destructor
	 */
	~IPathfinding();

	/**
	 * Anyade un obstaculo a la lista de obstaculos
	 * @param obstaculo Lista de points que componen el obstaculo
	 */
	void AddObstaculo(Polygon obstaculo);

	/**
	 * Genera el grafo de navegacion
	 */
	void GenerarGrafo();

	/**
	 * Calcula el camino entre dos Vector3
	 * @param init Inicio
	 * @param fin Fin
	 * @return Vector con el camino
	 */
	vector<Nodo*> CalcularCamino(Vector2 init, Vector2 fin);

	/**
	 * Devuelve el grafo generado
	 * @return Puntero al grafo generado
	 */
	Grafo* getGrafo() const;

	/**
	 * Devuelve los obstaculos
	 * @return Vector de obstaculos
	 */
	vector<Polygon> getObstaculos() const;

	/**
	 * Devuelve un puntero al contorno actual del mapa
	 * @return Puntero al contorno
	 */
	Polygon getContorno() const;
};

}

#endif /* IPATHFINDING_H_ */
