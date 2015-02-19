/*
 * InterfazPathfinding.h
 *
 *  Created on: 22/03/2012
 *      Author: esteve
 */

#ifndef INTERFAZPATHFINDING_H_
#define INTERFAZPATHFINDING_H_
#include "IPathfinding.h"
#include "CandyMath.h"
#include "GEDynamic.h"
#include "CandyNapper.h"
#include "poly2tri/poly2tri.h"
#include "InterfazPhysics.h"


namespace candy {
using namespace CandyMath;

class InterfazPathfinding {
private:
	IPathfinding* _pathfinding;
	static InterfazPathfinding* _instance;
public:
	static InterfazPathfinding* getInstance();
	InterfazPathfinding();
	~InterfazPathfinding();
	/**
	 * Genera un grafo a partir de los obstaculos
	 */
	void GenerarGrafo();

	/**
	 * Obtener un Camino en coordenadas del juego
	 * @param posicion inicial (en coordenadas juego)
	 * @param posicion final (en coordenadas fuego)
	 * @return vector de posiciones que representan el camino
	 */
	vector<Vector3> ObtCamino(Vector3 init, Vector3 fin);

	/**
	 * Devuelve la siguiente posición a la que se puede ir directamente y modifica el camino recortando las posiciones inecesarias
	 * Lanza un -1 si el camino es vacio
	 * @param vector de posiciones que representan el camino
	 * @return siguiente posición a la que acceder directamente
	 */
	Vector3 Suavizado(vector<Vector3> &camino, GEDynamic* entity);

	/**
	 * Devuelve el angulo que se forma entre dos posiciones del juego con respecto al sistema de coordenadas del mismo
	 * @param posición inicial
	 * @param posición final
	 * @return ángulo en radianes
	 */
	double ObtAngulo(Vector3 init, Vector3 fin);


	/**
	 * Sirve para saber si una posición esta dentro del mapa transitable
	 * @param posicion (en coordenadas del juego)
	 * @return bool si esta dentro o no
	 */
	bool EsTransitable(Vector3 pos);


	/**
	 * Obtienes un puntero a IPathfinding
	 * @return IPathfinding*
	 */
	IPathfinding* getIPathfinding();

	/**
	 * Adapta las coordenadas del pathfinding al juego
	 * @param coordenadas del pathfinding
	 * @return coordenadas del juego
	 */
	Vector3 AdapCoordP2J(Vector2 v);

	/**
	 * Adapta las coordenadas del juego al pathfinding
	 * @param coordenadas del juego
	 * @return coordenadas del pathfinding
	 */
	Vector2 AdapCoordJ2P(Vector3 v);

	/**
	 * Adapta las coordenadas del pathfinding al juego
	 * @param coordenadas del pathfinding
	 * @return coordenadas del juego
	 */
	Vector3* AdapCoordP2J(Vector2 *v);

	/**
	 * Adapta las coordenadas del juego al pathfinding
	 * @param coordenadas del juego
	 * @return coordenadas del pathfinding
	 */
	Vector2* AdapCoordJ2P(Vector3 *v);


};

}

#endif /* INTERFAZPATHFINDING_H_ */
