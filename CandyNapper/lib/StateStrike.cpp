/*
 * StateStrike.cpp
 *
 *  Created on: 18/03/2012
 *      Author: esteve
 */

#include "StateStrike.h"

namespace candy {

StateStrike::StateStrike() : State(){

}

StateStrike::StateStrike(int id, StateMachineEnemy* sm) : State(id, sm){
	_enemy = sm->getEnemy();
}

StateStrike::~StateStrike(){

}

void StateStrike::Transition(){
	GEDynamic* player = CandyNapper::getInstancia()->getEm()->getPlayer();

	if(player != NULL){
		Vector3 posPlayer = player->getPosicion();
		Vector3 posEnemy = _enemy->getPosicion();

		Attack* ataque = _enemy->getAttack();
		int vidaRest = _enemy->getVidaRestante();
		int vidaTotal = _enemy->getVidaTotal();

		if(posEnemy.Distancia(posPlayer) > ataque->getRango()){
			//cout<<"CAMBIO A PERSEGUIR"<<endl;
			SM->ChangeState(StateMachineEnemy::Follow);
		}
		else if(vidaRest < vidaTotal*30/100 && _enemy->getTipoEnemigo() != Enemy::Melon){
			//cout<<"CAMBIO A HUIR"<<endl;
			SM->ChangeState(StateMachineEnemy::Escape);
		}

	}
}

void StateStrike::Execute(){
	Text* texto = InterfazGraphics::getInstance()->getHUD()->getText2();
	//texto->setTexto("ESTADO STRIKE");

	GEDynamic* player = CandyNapper::getInstancia()->getEm()->getPlayer();
	_enemy->getAttack()->isAttacking(false);

	if(player != NULL){
		//cout<<"vida Player "<<player->getVidaRestante()<<endl;
		Vector3 posEnemy = _enemy->getPosicion();
		_enemy->setVisionX(InterfazPathfinding::getInstance()->ObtAngulo(posEnemy, player->getPosicion()));
		_enemy->setVelocidad(0);
		int idPlayer = player->getID();
		//Attack ataque = ((StateMachineEnemy*)SM)->getOwner()->getEnemy()->getAttack();


		_enemy->getAttack()->Atacar(idPlayer, GameEntity::Player);


		if(_enemy->getTipoEnemigo() == Enemy::Melon){
			_enemy->setVidaRestante(0);
		}

	}

}

}
