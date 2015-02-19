/*
 * Nodo.cpp
 *
 *  Created on: 23/02/2012
 *      Author: esteve
 */

#include "Nodo.h"

namespace candy{

Nodo::Nodo(double x, double y, bool v){
	_pos.setX(x);
	_pos.setY(y);
	visitado = v;
}

Nodo::Nodo(Vector2 pos, bool v){
	_pos = pos;
	v = false;
}

Nodo::Nodo(const Nodo& n){
	if(this != &n){
		_pos = n._pos;
		visitado = n.visitado;
	}
}

Nodo& Nodo::operator=(const Nodo& n){
	if (this != &n) {
		_pos = n._pos;
		visitado = n.visitado;
	}
	return *this;
}

Nodo::~Nodo(){

}

void Nodo::AddNodo(Nodo* nodo){
	NodosAdy.push_back(nodo);
}

void Nodo::Visitado(bool v){
	visitado = v;
}

bool Nodo::EstaVisitado(){
	return visitado;
}

Vector2 Nodo::getPosition(){
	return _pos;
}

void Nodo::setPosition(Vector2 pos){
	_pos = pos;
}

vector<Nodo*> Nodo::getNodosAdy(){
	return NodosAdy;
}

bool Nodo::AdyVisitados(){
	bool visitados = false;
	for(unsigned i = 0; i < NodosAdy.size() && !visitados; i++){
		visitados = visitados && NodosAdy[i]->visitado;
	}
	return visitados;
}
}
