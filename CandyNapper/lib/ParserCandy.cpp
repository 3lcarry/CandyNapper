/*
 * ParserCandy.cpp
 *
 *  Created on: 16/03/2012
 *      Author: carrillo
 */

#include "ParserCandy.h"
#include "CandyNapper.h"

namespace candy {

ParserCandy::ParserCandy(CandyNapper* c) {
	_candy = c;
	_documento = NULL;
	_elemento = NULL;
	_raiz = NULL;
}

ParserCandy::~ParserCandy() {
	if(_documento != NULL){
		delete _documento;
		_documento = NULL;
		_raiz = NULL;
		_elemento = NULL;
	}
}

bool ParserCandy::loadFile(string ruta) {
	bool resul = true;

	_documento = new TiXmlDocument(ruta.c_str());
	if(_documento->LoadFile()){
		TiXmlHandle manejadorAux(_documento);
		_elemento = manejadorAux.FirstChild("CandyNapper").Element();
		if(_elemento != NULL){
			_raiz = new TiXmlHandle(_elemento);
		}else{
			resul = false;
		}
	}else{
		resul = false;
	}

	return resul;
}

bool ParserCandy::configure(void) {
	bool correcto = true;

	if(_raiz->FirstChild("Map").Element() != NULL)
		_elemento = _raiz->FirstChild("Map").Element();

	if(_elemento != NULL){
		int x,y;
		_elemento->QueryIntAttribute("x",&x);
		_elemento->QueryIntAttribute("y",&y);
		//TODO: Almacenar en Candy el tamaño del mapa
	}

	//creamos el player
	if(_raiz->FirstChild("Player").Element() != NULL)
		_elemento = _raiz->FirstChild("Player").Element();




	if(_elemento != NULL)
	{
		float x,y;
		_elemento->QueryFloatAttribute("x",&x);
		_elemento->QueryFloatAttribute("y",&y);
		_candy->getEm()->addPlayer(Vector3(x,0,y));
	}


	//Creamos los enemigos
	for(_elemento = _raiz->FirstChild("Enemies").FirstChild().Element(); _elemento != NULL; _elemento = _elemento->NextSiblingElement()){
		float tipo,x,y;
		_elemento->QueryFloatAttribute("type",&tipo);
		_elemento->QueryFloatAttribute("x",&x);
		_elemento->QueryFloatAttribute("y",&y);

		if(tipo < Enemy::NumTipoEnemigos){
			_candy->getEm()->addEnemy(Vector3(x,0,y),Enemy::TipoEnemigo(tipo));
		}
	}

	//Creamos los obstaculos
	for(_elemento = _raiz->FirstChild("Obstacles").FirstChild().Element(); _elemento != NULL; _elemento = _elemento->NextSiblingElement()){
		float tipo,x,y;
		_elemento->QueryFloatAttribute("type",&tipo);
		_elemento->QueryFloatAttribute("x",&x);
		_elemento->QueryFloatAttribute("y",&y);

		if(tipo < Obstaculo::NumTipoObstaculos){
			_candy->getEm()->addObstacle(Vector3(x,0,y),Obstaculo::TipoObstaculo(tipo));
		}
	}

	//Creamos los Objetos
	for(_elemento = _raiz->FirstChild("Objects").FirstChild().Element(); _elemento != NULL; _elemento = _elemento->NextSiblingElement()){
		float tipo,x,y;
		_elemento->QueryFloatAttribute("type",&tipo);
		_elemento->QueryFloatAttribute("x",&x);
		_elemento->QueryFloatAttribute("y",&y);

		if(tipo < Objetos::NumTipoObjetos){
			Objetos* obj;
			obj =  _candy->getEm()->addObjeto(Vector3(x,0,y),Objetos::TiposObjetos(tipo));
			if(tipo == Objetos::Portal)
			{
				if(_elemento->Attribute("nextLevel") != NULL)
				{
					obj->setNextLevel(_elemento->Attribute("nextLevel"));
					bool matarTodos;
					_elemento->QueryBoolAttribute("killAll",&matarTodos);
					obj->setMatarTodos(matarTodos);
				}
			}
		}
	}
	return correcto;
}

void ParserCandy::closeFile(void) {
	if(_documento != NULL){
		delete _documento;
		_documento = NULL;
		_raiz = NULL;
		_elemento = NULL;
	}
}

} /* namespace candy */
