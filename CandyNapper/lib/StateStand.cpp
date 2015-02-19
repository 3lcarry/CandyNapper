/*
 * StateStand.cpp
 *
 *  Created on: 15/03/2012
 *      Author: esteve
 */

#include "StateStand.h"

namespace candy {

StateStand::StateStand() : State(){
	_SM = NULL;
	_enemy = NULL;
	_angInicial = INFINITY;
	_angGiroPorCiclo = grad2rad(0.5);
	_angAcumulado = 0.0;
	_goback = false;
	_follow = false;
}

StateStand::StateStand(int id, StateMachineEnemy *sm) : State(id, sm){
	_SM = ((StateMachineEnemy*)SM);
	_enemy = sm->getEnemy();
	_angInicial = INFINITY;
	_angGiroPorCiclo = grad2rad(0.5);
	_angAcumulado = 0.0;
	_goback = false;
	_follow = false;
}

StateStand::~StateStand(){
	_enemy = NULL;
}



void StateStand::Execute(){

	Text* texto = InterfazGraphics::getInstance()->getHUD()->getText2();
	//texto->setTexto("ESTADO STAND");

	if(_angInicial == INFINITY){
		_angInicial = _enemy->getVisionX();
		_angAcumulado = _enemy->getVisionX();

	}

	_angAcumulado += _angGiroPorCiclo;
	_enemy->setVisionX(_angAcumulado);
	_enemy->setVelocidad(0.0);


}

void StateStand::Transition() {

	if(_SM->SeVe()){
		_angAcumulado = 0.0;
		SM->ChangeState(StateMachineEnemy::Follow);
	}
	if(_angInicial+2*M_PI < _angAcumulado){
		_angAcumulado = 0.0;
		SM->ChangeState(StateMachineEnemy::Patrol);
	}
}

//void StateStand::Transition(){

	/*if(goback){
		//cout<<"CAMBIO A PATRULLAR"<<endl;
		goback = false;
		cont = 0;
		SM->ChangeState(StateMachineEnemy::Patrol);

	}
	if(follow){
		//cout<<"CAMBIO A PRESEGUIR"<<endl;
		follow = false;
		SM->ChangeState(StateMachineEnemy::Follow);

	}*/

//}
}
