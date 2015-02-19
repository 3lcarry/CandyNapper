/*
 * Pathfinding.cpp
 *
 *  Created on: 24/02/2012
 *      Author: esteve
 */

#include "Pathfinding.h"
#include <cmath>

namespace candy{

////////// Struct nodoAStar ///////////

Pathfinding::nodoAStar::nodoAStar(){
	nodo = NULL;
	padre = NULL;
	F = 0.0;
	G = 0.0;
	H = 0.0;
}

Pathfinding::nodoAStar::nodoAStar(const nodoAStar &n){
	nodo = n.nodo;
	padre = n.padre;
	F = n.F;
	G = n.G;
	H = n.H;
}

Pathfinding::nodoAStar::nodoAStar(Nodo* nodo_, nodoAStar* padre_, float F_, float G_, float H_){
	nodo = nodo_;
	padre = padre_;
	F = F_;
	G = G_;
	H = H_;
}

void Pathfinding::nodoAStar::setG(float G_){
	G = G_;
	F = H + G;
}

void Pathfinding::nodoAStar::setH(float H_){
	H = H_;
	F = H + G;
}

bool Pathfinding::nodoAStar::empty(){
	return (nodo == NULL && padre == NULL && F == 0.0 && G == 0.0 && H == 0.0);
}

///////// Clase Pathfinding ///////////

const int Pathfinding::tiempMax = 50;

Nodo* Pathfinding::NodoFuturo(Nodo* n, Nodo* fin){
	vector<Nodo*> na = n->getNodosAdy();

		Nodo* nn = NULL;
		if(!na.empty()){
			double min = INFINITY;

			for(unsigned i = 0; i < na.size(); i++){
				double min_aux = na[i]->getPosition().Distancia(fin->getPosition());
				if(min_aux < min && !na[i]->EstaVisitado()){
					nn = na[i];
					min = min_aux;
				}

			}
		}

		return nn;
}

double Pathfinding::CaminoVoraz(Nodo* primero, Nodo* ultimo){
	double dist = INFINITY;

	if(_grafo != NULL){
		vector<Nodo*> nodos = _grafo->getGrafo();

		if(!nodos.empty()){

			if(primero != ultimo){

				_camino.push_back(primero);	//Metemos el primer nodo al camino
				Nodo* actual = primero;		//y lo marcamos como actual
				if(actual != NULL) {
					actual->Visitado(true);	//y visitado
				}

				while(actual != ultimo && !_camino.empty() && actual != NULL){  //mientras el nodo actual no sea el ultimo
																				//y no este el camino vacio y nodo actual se distinto a null
					actual = NodoFuturo(actual, ultimo);	//obtenemos el siguiente nodo
					if(actual != NULL){	//si existe...
						actual->Visitado(true);	//lo marcamos como visitado y lo mentemos al camino
						_camino.push_back(actual);
					}
					else{	//sino ...
						if(!_camino.empty()){	//si el camino no esta vacio... (si esta vacio es que no hay camino)
							_camino.erase(_camino.end()-1); //borro el ultimo nodo del camino
							actual = _camino.back();	//y marco como actual el que ahora es el ultimo nodo,
							actual->Visitado(true);		//es decir no hay camino por el  nodo que ibamos y volvemos al anterior
						}
					}

				}
				//Calculo la distancia del camino
				dist = 0;
				for(int i = 1; i < _camino.size(); i++)
					dist += _camino[i-1]->getPosition().Distancia(_camino[i]->getPosition());

			}

		}
	}
	return dist;
}




Pathfinding::nodoAStar Pathfinding::getNodo(list<nodoAStar> lista, nodoAStar nas){
	bool esta = false;
	nodoAStar result;

	list<nodoAStar>::iterator i;
	for(i = lista.begin(); i != lista.end() && !esta; i++){
		if(i->nodo == nas.nodo) {
			esta = true;
			result = (*i);
		}
	}

	return result;
}

void Pathfinding::InsertarOrdenado(list<nodoAStar> &lista, nodoAStar n){
	bool insertado = false;

	list<nodoAStar>::iterator i;
	for(i = lista.begin(); i != lista.end() && !insertado; i++){
		if(i->F > n.F) {
			lista.insert(i, n);
			insertado = true;
		}
	}

	if(!insertado)
		lista.push_back(n);
}

void Pathfinding::Borrar(list<nodoAStar> &lista, nodoAStar n){
	bool borrado = false;

	list<nodoAStar>::iterator i;
	for(i = lista.begin(); i != lista.end() && !borrado; i++){
		if(i->nodo == n.nodo){
			lista.erase(i);
			borrado = true;
		}
	}
}

Pathfinding::Pathfinding(Grafo* grafo) {
	_grafo = grafo;
}

Pathfinding::~Pathfinding() {
	// TODO Auto-generated destructor stub
}

void Pathfinding::Calcular(Vector2 init, Vector2 fin){
	//cout<<"Pathfinding: Calcular"<<endl;

	int momentEnt = Timer::getTimeElapsed();
	bool cancelado =  false;


	if(_grafo != NULL) {

		vector<Nodo*> grafo = _grafo->getGrafo();
		//cout<<"Pathfinding: Numero de nodos "<<grafo.size()<<endl;
		//cout<<"Pathfinding: Momento de entrada "<<momentEnt<<endl;

		if(!grafo.empty()) {
			//Obtengo los nodos mas cercanos a init y a fin
			Nodo* primero = grafo[0];
			Nodo* ultimo = grafo[0];

			double min = init.Distancia(grafo[0]->getPosition());
			double min2 = fin.Distancia(grafo[0]->getPosition());

			for(unsigned i = 1; i < grafo.size(); i++){
				double min_aux = init.Distancia(grafo[i]->getPosition());
				double min_aux2 = fin.Distancia(grafo[i]->getPosition());
				if(min_aux < min){
					primero = grafo[i];
					min = min_aux;
				}
				if(min_aux2 < min2){
					ultimo = grafo[i];
					min2 = min_aux2;
				}
			}

			double distVoraz = CaminoVoraz(primero, ultimo); //obtenemos un camino voraz para recortar nodos

			if(primero != ultimo){
				//EMPIEZA EL ALGORITMO
				list<nodoAStar> listaAbierta;

				listaAbierta.push_back(nodoAStar(primero, NULL, 0.0, 0.0, 0.0)); //Añado el nodo primero a la lista abierta

				while(!listaAbierta.empty() && listaAbierta.front().nodo != ultimo){

					if(Timer::getTimeElapsed() - momentEnt > tiempMax){ //evitamos que el calculo del camino dure demasiado
						//cout<<"Pathfinding: cancelado"<<endl;
						cancelado = true;
						break;
					}

					nodoAStar nas = listaAbierta.front();
					listaAbierta.pop_front();				//saco el primer nodo de la listaAbierta y lo borro


					vector<Nodo*> ady = nas.nodo->getNodosAdy();


					for(unsigned i = 0; i < ady.size(); i++){
						nodoAStar* padre = new nodoAStar(nas);
						float G = nas.G + nas.nodo->getPosition().Distancia(ady[i]->getPosition());
						float H = ady[i]->getPosition().Distancia(ultimo->getPosition());
						float F = G + H;
						nodoAStar candidato(ady[i], padre, F, G, H); //se crea un nodoAStar a partir del adyacente

						if(candidato.nodo == ultimo){ //se hace esto por el error de la como flotante que no reconce los valores como iguales
							candidato.setG(candidato.G - 0.001);
						}

						if(candidato.G <= distVoraz){ //Compruebo que el camino llevado hasta el momento sea menor que la distancia del camino voraz
							//cout<<"Pathfinding: ENTRA"<<endl;
							nodoAStar la_nas = getNodo(listaAbierta, candidato);
							if(la_nas.empty()){ // si no esta en la lista abierta...
								InsertarOrdenado(listaAbierta, candidato); //Lo meto
							}
							else { // y si esta...
								//Compruebo a ver cual tiene un menor camino de momento
								if(candidato.G < la_nas.G){ //si el candidato tiene un menor camino...
									Borrar(listaAbierta, la_nas);
									InsertarOrdenado(listaAbierta, candidato); //borro el que hay en la lista abierta y inserto el candidato
								}
							}
						}
						else {
							//cout<<"Pathfinding: NO ENTRA"<<endl;
						}
						//cout<<endl;
					}
				}

				//Obtenemos el camino
				if(!cancelado) {	//si no ha sido cancelado sacamos el camino por A star
									//y si se ha cancelado se queda el camino voraz
					if(!listaAbierta.empty()){
						nodoAStar *n_act = &listaAbierta.front();
						_camino.clear();
						while(n_act->padre != NULL){
							_camino.insert(_camino.begin(), n_act->nodo);
							n_act = n_act->padre;
						}
					}
				}

			}
			//Añadimos las posiciones inicial y final al camino
			Nodo* I = new Nodo(init, true);
			Nodo* F = new Nodo(fin, true);
			_camino.insert(_camino.begin(), I);
			_camino.push_back(F);
		}

	}

}

vector<Nodo*> Pathfinding::getCamino(){
	return _camino;
}

}
