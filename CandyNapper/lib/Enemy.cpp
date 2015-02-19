/*
 * Enemy.cpp
 *
 *  Created on: 01/03/2012
 *      Author: kaseyo
 */

#include "Enemy.h"

#include "CompGraphic.h"
#include "CompMinimap.h"
#include "CompPhysics.h"
#include "CompLogic.h"
#include "CompIA.h"
#include "CompMusic.h"

namespace candy {

int Enemy::_numEnemigos = 0;
const float Enemy::VelocidadEnemigo = 10.0;

Enemy::Enemy(Vector3 posicion, TipoEnemigo enem)
	:GEDynamic(GameEntity::Enemigo, _numEnemigos, posicion)
{
	_numEnemigos++;
	_tipoEnem = enem;

	switch(enem){
	case Oso:
		_radio = 1.0;
		_vidaTotal = 100.0;
		break;
	case Gengibre:
			_radio = 1.0;
			_vidaTotal = 200.0;
			break;
	case Melon:
			_radio = 1.0;
			_vidaTotal = 50.0;
			break;
	default:
		_radio = 0.0;
		_vidaTotal = 0;
		break;
	}
	_ataque = new Attack(this);
	_convexHull = PolygonFactory::Circulo(Vector2(posicion.getX(), -posicion.getZ()), _radio);
	_vidaRestante = _vidaTotal;
	_muerto = false;

	//Anyadimos el componente grafico
	IComponent* gc = new CompGraphic(this);
	c_componentes.push_front(gc);

	//Anyadimos el componente de minimapa
	IComponent* minimapc = new CompMinimap(this);
	c_componentes.push_back(minimapc);

	//Anyado el componente de fisica
	IComponent* fc = new CompPhysics(this);
	c_componentes.push_back(fc);

	//Añado el componente de lógica
	IComponent* lc = new CompIA(this);
	c_componentes.push_back(lc);

	IComponent* mc = new CompMusic(this);
	c_componentes.push_back(mc);
}

Enemy::~Enemy() {

}

Enemy::TipoEnemigo Enemy::getTipoEnemigo(){
	return _tipoEnem;
}

} /* namespace candy */
