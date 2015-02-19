/*
 * EntityManager.cpp
 *
 *  Created on: Nov 9, 2011
 *      Author: carrillo
 */

#include "EntityManager.h"
using namespace candy;




EntityManager::EntityManager(){
	_player = NULL;
	_gameover = true;
}

EntityManager::~EntityManager() {
	list<GEDynamic*>::iterator it_dyn;
	list<GEStatic*>::iterator it_sta;

	//Eliminamos las dinamicas
	for(it_dyn = _dinamicas.begin(); it_dyn != _dinamicas.end(); it_dyn++){
		delete *it_dyn;
		*it_dyn = NULL;
	}

	_dinamicas.clear();

	//Eliminamos las estaticas
	for(it_sta = _staticas.begin(); it_sta != _staticas.end(); it_sta++){
		delete (*it_sta);
		(*it_sta) = NULL;
	}

	_staticas.clear();

	//Eliminamos el player
	if(_player != NULL){
		delete _player;
		_player = NULL;
	}

	_gameover = true;
}

EntityManager::EntityManager(const EntityManager& em){
	copiarDesde(em);
}

EntityManager&
EntityManager::operator=(const EntityManager& em){
	if(this != &em){
		//this->~EntityManager();
		copiarDesde(em);
	}

	return *this;
}

void
EntityManager::copiarDesde(const EntityManager& em){
	_staticas = em._staticas;
	_dinamicas = em._dinamicas;
	_player = em._player;
}

/*
GameEntity*
EntityManager::addEntity(GameEntity::Tipo tipo, int id, Vector3 posicion){
	GameEntity* res = NULL;

	if(tipo == GameEntity::Enemigo){
		GEDynamic* ent_din = new Enemy(posicion, );

		addOrderedDynamic(ent_din);

		res = ent_din;
	}else if(tipo == GameEntity::Obstaculo){
		GEStatic* ent_sta = new GEStatic(tipo, id, posicion);

		addOrderedStatic(ent_sta);

		res = ent_sta;
	}else if(tipo == GameEntity::Player){
		if(_player != NULL){
			delete _player;
		}

		_player = new Player(posicion);
		_gameover = false;
		res = _player;
	}

	return res;
}
*/

GameEntity*
EntityManager::addEntity(GameEntity* entidad){
	if(isDynamic(entidad->getTipo())){
		GEDynamic* ent_din = (GEDynamic*)entidad;

		addOrderedDynamic(ent_din);
	}else if(isStatic(entidad->getTipo())){
		GEStatic* ent_sta = (GEStatic*)entidad;

		addOrderedStatic(ent_sta);
	}else if(entidad->getTipo() == GameEntity::Player){
		if(_player != NULL){
			delete _player;
		}

		_player = (Player*)entidad;
		_gameover = false;
	}

	return entidad;
}

Enemy*
EntityManager::addEnemy(Vector3 posicion, Enemy::TipoEnemigo tipo_enem){
	GEDynamic* enem = new Enemy(posicion, tipo_enem);

	addOrderedDynamic(enem);

	return (Enemy*)enem;
}

Obstaculo*
EntityManager::addObstacle(Vector3 posicion, Obstaculo::TipoObstaculo tipo_sta){
	Obstaculo* estatic = new Obstaculo(tipo_sta, posicion);
	double tam = estatic->tamanyo/2;

	addOrderedStatic(estatic);

	return estatic;
}

Objetos *candy::EntityManager::addObjeto(Vector3 posicion, Objetos::TiposObjetos tipo_objeto)
{
	Objetos* obj = new Objetos(tipo_objeto,posicion);
	addOrderedStatic(obj);
	return obj;
}

void
EntityManager::addOrderedStatic(GEStatic* ent_sta){
	list<GEStatic*>::iterator it = _staticas.begin();

	while(it != _staticas.end() && ent_sta->getID() > (*it)->getID()){
		it++;
	}

	_staticas.insert(it, ent_sta);

	//cout << "[EntityManager.cpp] A–ado un nuevo obstaculo (" << _staticas.size() << ")" << endl;
}

void
EntityManager::addOrderedDynamic(GEDynamic* ent_din){
	list<GEDynamic*>::iterator it = _dinamicas.begin();

	while(it != _dinamicas.end() && ent_din->getID() > (*it)->getID()){
		it++;
	}

	_dinamicas.insert(it, ent_din);
}

GameEntity*
EntityManager::getEntity(GameEntity::TipoEntidad tipo, int id){
	GameEntity* entidad = NULL;

	if(isDynamic(tipo)){
		entidad = getStatic(id);

	}else if(isStatic(tipo)){
		entidad = getEnemy(id);

	}else if(tipo == GameEntity::Player){
		entidad = _player;
	}

	return entidad;
}

GEStatic*
EntityManager::getStatic(int id){
	GEStatic* ent_sta = NULL;
	bool encontrado = false;
	list<GEStatic*>::iterator it = _staticas.begin();

	while(it != _staticas.end() && !encontrado){
		if((*it)->getID() == id){
			ent_sta = *it;
			encontrado = true;
		}else{
			it++;
		}
	}

	return ent_sta;
}

GEDynamic*
EntityManager::getEnemy(int id){
	GEDynamic* ent_din = NULL;
	bool encontrado = false;
	list<GEDynamic*>::iterator it = _dinamicas.begin();

	while(it != _dinamicas.end() && !encontrado){
		if((*it)->getID() == id){
			ent_din = *it;
			encontrado = true;
		}else{
			it++;
		}
	}

	return ent_din;
}

Player*
EntityManager::getPlayer(){
	return _player;
}

void
EntityManager::deleteEntity(GameEntity::TipoEntidad tipo, int id){
	bool encontrado = false;

	if(isDynamic(tipo)){
		list<GEDynamic*>::iterator it_din = _dinamicas.begin();

		while(it_din != _dinamicas.end() && !encontrado){
			if((*it_din)->getID() == id){
				encontrado = true;
				delete *it_din;
				_dinamicas.erase(it_din);
			}else{
				it_din++;
			}
		}
	}else if(isStatic(tipo)){
		list<GEStatic*>::iterator it_sta = _staticas.begin();

		while(it_sta != _staticas.end() && !encontrado){
			if((*it_sta)->getID() == id){
				encontrado = true;
				delete *it_sta;
				_staticas.erase(it_sta);
			}else{
				it_sta++;
			}
		}
	}else if(tipo == GameEntity::Player){
		deletePlayer();
		_gameover = true;
	}
}

void
EntityManager::deleteType(GameEntity::TipoEntidad tipo){
	if(isDynamic(tipo)){
		list<GEDynamic*>::iterator it_din;
		for(it_din = _dinamicas.begin(); it_din != _dinamicas.end(); it_din++){
			delete *it_din;
		}

		_dinamicas.clear();
	}else if(isStatic(tipo)){
		list<GEStatic*>::iterator it_sta;
		for(it_sta = _staticas.begin(); it_sta != _staticas.end(); it_sta++){
			delete *it_sta;
		}

		_staticas.clear();
	}else if(tipo == GameEntity::Player){
		deletePlayer();
		_gameover = true;
	}
}

list<GEDynamic*>
EntityManager::getDynamics(){
	return _dinamicas;
}

list<GEStatic*>
EntityManager::getStatics(){
	return _staticas;
}

Player *
EntityManager::addPlayer(Vector3 posicion){
	deletePlayer();

	_player = new Player(posicion);
	_gameover = false;
	return _player;
}

void
EntityManager::deletePlayer(){
	if(_player!=NULL){
		delete _player;
		_player = NULL;
	}
}

list<GEDynamic*>
EntityManager::getEnemys(){
	return _dinamicas;
}



bool
EntityManager::isStatic(GameEntity::TipoEntidad tipo){
	bool estatica = false;

	if(tipo == GameEntity::Estatica){
		estatica = true;
	}

	return estatica;
}

bool
EntityManager::isDynamic(GameEntity::TipoEntidad tipo){
	bool dinamica = false;

	if(tipo == GameEntity::Enemigo){
		dinamica = true;
	}

	return dinamica;
}

void
EntityManager::Update(){
	if(_player != NULL){
		_player->Update();
		//Cuando acabo, miro si han matado al player
		if(_player->isMuerto()){
			_gameover = true;
			delete _player;
			_player = NULL;
		}
	}

	list<GEDynamic*>::iterator it_din;
	for(it_din = _dinamicas.begin(); it_din != _dinamicas.end(); it_din++){
		if((*it_din)->isMuerto() || (*it_din)->getDestroy()){
			delete (*it_din);
			it_din = _dinamicas.erase(it_din);
		}else{
			(*it_din)->Update();
		}
	}

	list<GEStatic*>::iterator it_sta;
	for(it_sta = _staticas.begin(); it_sta != _staticas.end(); it_sta++){
		if((*it_sta)->getDestroy())
		{
			delete (*it_sta);
			it_sta = _staticas.erase(it_sta);
		}
		else{
			(*it_sta)->Update();
		}
	}
}

bool
EntityManager::isGameOver(){
	return _gameover;
}

void
EntityManager::Init()
{
	_gameover = false;

	if(_player != NULL)
	{
		delete _player;
	}

	_player = NULL;


	list<GEDynamic*>::iterator dinamicIt;
	for(dinamicIt = _dinamicas.begin(); dinamicIt != _dinamicas.end(); dinamicIt++)
	{
		delete (*dinamicIt);
	}
	_dinamicas.clear();


	list<GEStatic*>::iterator staticIt;
	for(staticIt = _staticas.begin(); staticIt != _staticas.end(); staticIt++)
	{
		delete (*staticIt);
	}
	_staticas.clear();
}

