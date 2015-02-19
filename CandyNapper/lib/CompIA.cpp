/*
 * CompLogic.cpp
 *
 *  Created on: 01/03/2012
 *      Author: esteve
 */

#include "CompIA.h"
#include "StateMachineEnemy.h"
#include "Attack.h"
#include "Enemy.h"
#include "StatePatrol.h"
#include "StateFollow.h"
#include "StateStand.h"
#include "StateEscape.h"
#include "StateRegenerate.h"
#include "StateStrike.h"

namespace candy{

CompIA::CompIA(Enemy* enemy) {

	_SM = new StateMachineEnemy(enemy);
	//Añadir los ataques segun el enemigo
	//if(((Enemy*)enemy)->getTipoEnemigo() == Enemy::Oso){
		StateFollow* sf = new StateFollow(/*enemy, */StateMachineEnemy::Follow, ((StateMachineEnemy*)_SM));
		StatePatrol* sp = new StatePatrol(StateMachineEnemy::Patrol, ((StateMachineEnemy*)_SM));
		StateStand* st = new StateStand(StateMachineEnemy::Stand, ((StateMachineEnemy*)_SM));
		StateStrike* ss = new StateStrike(StateMachineEnemy::Attack, ((StateMachineEnemy*)_SM));
		StateEscape* se = new StateEscape(StateMachineEnemy::Escape, ((StateMachineEnemy*)_SM));
		StateRegenerate* sr = new StateRegenerate(StateMachineEnemy::Regenerate, ((StateMachineEnemy*)_SM));

		_SM->AddState(sf);
		_SM->AddState(sp);
		_SM->AddState(st);
		_SM->AddState(ss);
		_SM->AddState(se);
		_SM->AddState(sr);

		_SM->setInitialState(sp);
	/*}
	else if(((Enemy*)enemy)->getTipoEnemigo() == Enemy::Gengibre){

	}
	else if(((Enemy*)enemy)->getTipoEnemigo() == Enemy::Melon){

	}*/

	//Generar Grafo de navegacion
	/*list<GEStatic*> obs = EntityManager::getInstance()->getStatics();
	list<GEStatic*>::iterator i;
	for(i = obs.begin(); i != obs.end(); i++){
		Vector2 posicion = ((StateMachineEnemy*)_SM)->AdapCoordJ2P((*i)->getPosicion());
		Polygon  poligono = PolygonFactory::Cuadrado(posicion, 1.0, 1.0);
		IPathfinding::Instance()->AddObstaculo(poligono);
	}*/

	//Añadir los estados segun el enemigo(futuro)

}

CompIA::~CompIA() {
	// TODO Auto-generated destructor stub
}

void CompIA::Update(GameEntity* entity){
	((StateMachineEnemy*)_SM)->Update();
}

}
