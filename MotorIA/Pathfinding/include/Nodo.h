/*
 * Nodo.h
 *
 *  Created on: 23/02/2012
 *      Author: esteve
 */

#ifndef NODO_H_
#define NODO_H_
#include <iostream>
#include <vector>
using namespace std;

#include "CandyMath.h"

namespace candy{
class Nodo {
private:
	Vector2 _pos;
	vector<Nodo*> NodosAdy;
	bool visitado;
public:
	Nodo(double x, double y, bool visitado = false);
	Nodo(Vector2 pos, bool vis = false);
	Nodo(const Nodo& n);
	Nodo& operator=(const Nodo& n);
	~Nodo();
	void AddNodo(Nodo*);
	void Visitado(bool v);
	bool EstaVisitado();
	Vector2 getPosition();
	void setPosition(Vector2 pos);
	vector<Nodo*> getNodosAdy();
	bool AdyVisitados();
};
}

#endif /* NODO_H_ */
