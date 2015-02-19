/*
 * Grafp.cpp
 *
 *  Created on: 23/02/2012
 *      Author: esteve
 */

#include "Grafo.h"

namespace candy{

void Grafo::GenerarGrafo(){

	for(unsigned i=0; i<Triangulos.size();i++)
	{
		p2t::Point *p = Triangulos[i]->getIncentro();

		Vector2 incentro_actual(p->x, p->y);
		Nodo* nodo_actual = existeNodo(incentro_actual);
		if(nodo_actual == NULL){
			nodo_actual = new Nodo(incentro_actual);
			Nodos.push_back(nodo_actual);
		}

		int num_vecinos = 0;
		for(unsigned j = 0; j < 3; j++){
			p2t::Triangle* vecino = Triangulos[i]->GetNeighbor(j);
			if(vecino != NULL && vecino->IsInterior()){
				p2t::Point* incentro = vecino->getIncentro();

				Vector2 incentro_vec(incentro->x, incentro->y);

				Nodo* nodo_ady = existeNodo(incentro_vec);
				if(nodo_ady == NULL){
					nodo_ady = new Nodo(incentro_vec);
					Nodos.push_back(nodo_ady);
				}

				nodo_actual->AddNodo(nodo_ady);

				num_vecinos++;
			}
		}
	}
}

Grafo::Grafo(vector<p2t::Triangle*> t) {
	for(unsigned i = 0; i < t.size(); i++){
		Triangulos.push_back(new p2t::Triangle(*(t[i])));
	}

	GenerarGrafo();
}

Grafo::Grafo(const Grafo& g){
	copiarDesde(g);
}

Grafo& Grafo::operator=(const Grafo &g){
	if (this != &g) {
		this->~Grafo();
		copiarDesde(g);
	}
	return *this;
}

Grafo::~Grafo() {
	for(unsigned i = 0; i < Triangulos.size(); i++){
		delete Triangulos[i];
		Triangulos[i] = NULL;
	}

	Triangulos.clear();
}

void
Grafo::copiarDesde(const Grafo& g){
	for(unsigned i = 0; i < g.Triangulos.size(); i++){
		Triangulos.push_back(new p2t::Triangle(*(g.Triangulos[i])));
	}

	for(unsigned i = 0; i < g.Nodos.size(); i++){
		Nodos.push_back(new Nodo(*(g.Nodos[i])));
	}
}

vector<Nodo*> Grafo::getGrafo(){
	return Nodos;
}

vector<p2t::Triangle*> Grafo::getTriangulos(){
	return Triangulos;
}

void Grafo::Reset(){
	for(unsigned i = 0; i < Nodos.size(); i++){
		Nodos[i]->Visitado(false);
	}
}

Nodo* Grafo::existeNodo(Vector2 pos){
	bool encontrado = false;
	Nodo* nodo = NULL;

	for(unsigned i = 0; i < Nodos.size() && !encontrado; i++){
		if(Nodos[i]->getPosition() == pos){
			encontrado = true;
			nodo = Nodos[i];
		}
	}

	return nodo;
}

}
