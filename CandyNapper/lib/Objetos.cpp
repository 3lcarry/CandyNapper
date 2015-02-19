/*
 * Objetos.cpp
 *
 *  Created on: 11/05/2012
 *      Author: carrillo
 */

#include "Objetos.h"
#include "CompLogic.h"
#include "CompGraphic.h"
#include "CompMinimap.h"

namespace candy {

Objetos::Objetos(Objetos::TiposObjetos tipo, Vector3 pos)
:GEStatic(GEStatic::Objeto,pos)
{
	_tipo = tipo;

	IComponent* lc = new CompLogic();
	c_componentes.push_back(lc);

	IComponent* gc = new CompGraphic(this);
	c_componentes.push_back(gc);

	IComponent* minimapc = new CompMinimap(this);
	c_componentes.push_back(minimapc);

	nextLevel = "";
	matarTodos=false;
}


Objetos::~Objetos() {
}

Objetos::TiposObjetos
Objetos::getTipoObjeto() {
	return _tipo;
}

void
Objetos::setNextLevel(string nl) {
	nextLevel = nl;
}

string
Objetos::getNextLevel() {
	return nextLevel;
}

void Objetos::setMatarTodos(bool mT) {
	matarTodos = mT;
}

bool Objetos::getMatarTodos() {
	return matarTodos;
}

} /* namespace candy */
