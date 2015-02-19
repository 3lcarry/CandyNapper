/*
 * gameentity.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: carrillo
 */

#include "GameEntity.h"
using namespace candy;

GameEntity::GameEntity(TipoEntidad tipo, int id, Vector3 posicion){
	c_tipo = tipo;
	c_id = id;
	c_posicion = posicion;
	_destruir = false;
}

GameEntity::~GameEntity(){
	list<IComponent*>::iterator it;

	for(it = c_componentes.begin(); it != c_componentes.end(); it++){
		delete (*it);
		(*it) = NULL;
	}

	c_componentes.clear();
}

GameEntity::GameEntity(const GameEntity & cop){
	copiarDesde(cop);
}

GameEntity &
GameEntity::operator =(const GameEntity & cop){
	if(this != &cop){
		copiarDesde(cop);
	}

	return *this;
}

void candy::GameEntity::setDestroy()
{
	_destruir = true;
}

bool candy::GameEntity::getDestroy()
{
	return _destruir;
}

void GameEntity::copiarDesde(const GameEntity & cop){
	c_tipo = cop.c_tipo;
	c_posicion = cop.c_posicion;
	c_id = cop.c_id;
}


GameEntity::TipoEntidad GameEntity::getTipo(){
	return c_tipo;
}

Vector3
GameEntity::getPosicion(){
	return c_posicion;
}

int
GameEntity::getID(){
	return c_id;
}

void
GameEntity::Update(){
	list<IComponent*>::iterator it;

	for(it = c_componentes.begin(); it != c_componentes.end(); it++){
		(*it)->Update(this);
	}
}

void
GameEntity::AddComponent(IComponent* componente){
	c_componentes.push_back(componente);
}

bool
GameEntity::isDynamic(){
	return (c_tipo == Player || c_tipo == Enemigo);
}

bool
GameEntity::isStatic(){
	return (c_tipo == Estatica);
}





