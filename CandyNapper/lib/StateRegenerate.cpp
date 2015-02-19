/*
 * StateRegenerate.cpp
 *
 *  Created on: 18/03/2012
 *      Author: esteve
 */

#include "StateRegenerate.h"

namespace candy {

StateRegenerate::StateRegenerate() : State(){
	_SM = NULL;
	_angGiroPorCiclo = grad2rad(0.5);
	_angInicial = INFINITY;
	_enemy = NULL;
	_ultReg = 0;
}

StateRegenerate::StateRegenerate(int id, StateMachineEnemy* sm) : State(id, sm){
	_SM = ((StateMachineEnemy*)SM);
	_angGiroPorCiclo = grad2rad(0.5);
	_angInicial = INFINITY;
	_enemy = sm->getEnemy();
	_ultReg = 0;
}

StateRegenerate::~StateRegenerate(){
	_enemy = NULL;
	_SM = NULL;
}

//void StateRegenerate::Transition(){

	/*int vidaRes = ((StateMachineEnemy*)SM)->getOwner()->getEnemy()->getVidaRestante();
	int vidaTotal = ((StateMachineEnemy*)SM)->getOwner()->getEnemy()->getVidaTotal();

	if(vidaRes == vidaTotal){
		SM->ChangeState(StateMachineEnemy::Patrol);
	}

	if(visto){
		if(vidaRes < vidaTotal*75/100){
			cont = 0;
			visto = false;
			SM->ChangeState(StateMachineEnemy::Attack);
		}
		else {
			cont = 0;
			visto = false;
			SM->ChangeState(StateMachineEnemy::Escape);
		}
	}*/

//}

/*void StateRegenerate::Execute(){

	((StateMachineEnemy*)SM)->getOwner()->getEnemy()->setVelocidad(0);

	int tiempo = Timer::getTimeElapsed();
	if(ultReg == 0 || tiempo-ultReg > 1500){
		((StateMachineEnemy*)SM)->getOwner()->getEnemy()->incVida();
		ultReg = tiempo;
	}

	Vector3 pos_Enemy = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getPosicion();
	GEDynamic* player = EntityManager::getInstance()->getPlayer();

	if(player != NULL){
		Vector3 pos_player = player->getPosicion();

		double angPlayer = ((StateMachineEnemy*) SM)->ObtAngulo(pos_Enemy, pos_player);
		double angEnemy = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getVisionX();

		if(cont%60 == 0 && cont > 0){
			((StateMachineEnemy*) SM)->getOwner()->getEnemy()->setVisionX(angEnemy+ (M_PI/2));
			angEnemy = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getVisionX();

		}
		cont++;

		double ang1 = angEnemy + ((StateMachineEnemy*)SM)->Grad2Rad(_angVis/2);
		double ang2 = angEnemy  - ((StateMachineEnemy*)SM)->Grad2Rad(_angVis/2);*/

		/*if(ang1 > M_PI*2.0)
			ang1 -= M_PI*2.0;

		if(ang2 > M_PI*2.0)
			ang2 -= M_PI*2.0;

		if(angPlayer < 0)
			angPlayer += M_PI*2.0;*/


		/*if(ang2 < 0){
			ang2 += 2*M_PI;
		}

		if(ang1 < ang2){
			ang1 += 2*M_PI;

			if(angPlayer < M_PI/2.0){
				angPlayer+= 2*M_PI;
			}
		}

		while(ang1 > 2.0*M_PI)
			ang1 -= 2.0*M_PI;

		while(ang2 > 2.0*M_PI)
			ang2 -= 2.0*M_PI;

		if(angPlayer < 0)
			angPlayer += M_PI*2.0;*/

		/*cout<<endl;
		cout<<"ang1 "<<ang1<<endl;
		cout<<"ang2 "<<ang2<<endl;
		cout<<"angPlayer "<<angPlayer<<endl;*/

		/*if(angPlayer < ang1 && angPlayer > ang2 && pos_Enemy.Distancia(pos_player) < _distVis){
			if(pos_Enemy != pos_player){
				if(!InterfazPhysics::getInstance()->obstaculo(pos_Enemy, pos_player))
					visto = true;
			}
		}
	}
}*/

/*void StateRegenerate::Execute(){
	Text* texto = InterfazGraphics::getInstance()->getHUD()->getText2();
	texto->setTexto("ESTADO ESCAPE");

	((StateMachineEnemy*)SM)->getOwner()->getEnemy()->setVelocidad(0);

	int tiempo = Timer::getTimeElapsed();
	if(ultReg == 0 || tiempo-ultReg > 1500){
		((StateMachineEnemy*)SM)->getOwner()->getEnemy()->incVida();
		ultReg = tiempo;
	}

	Vector3 pos_Enemy = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getPosicion();
	GEDynamic* player = EntityManager::getInstance()->getPlayer();

	if(player != NULL){
		Vector3 pos_player = player->getPosicion();

		double angPlayer = ((StateMachineEnemy*) SM)->ObtAngulo(pos_Enemy, pos_player);
		double angEnemy = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getVisionX();

		if(cont%60 == 0 && cont > 0){
			((StateMachineEnemy*) SM)->getOwner()->getEnemy()->setVisionX(angEnemy+ (M_PI/2));
			angEnemy = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getVisionX();

		}
		cont++;

		if(pos_Enemy.Distancia(pos_player) < _distVis) {
			double AngEnemyPlayer = ((StateMachineEnemy*)SM)->ObtAngulo(pos_Enemy, pos_player);

			while(angEnemy > 2*M_PI)
				angEnemy -= 2*M_PI;

			double angAux = AngEnemyPlayer - angEnemy;

			while(angAux > 2*M_PI)
				angAux -= 2*M_PI;

			if(angAux < 0)
				angAux += 2*M_PI;

			if(angAux < ((StateMachineEnemy*)SM)->Grad2Rad(_angVis)){
				if(InterfazPhysics::getInstance()->obstaculo(pos_Enemy, pos_player));
				visto = true;
			}
		}
		else{
			visto = false;
		}

	}

}*/

void StateRegenerate::Execute(){
	Text* texto = InterfazGraphics::getInstance()->getHUD()->getText2();
	//texto->setTexto("ESTADO REGENERATE");

	_enemy->setVelocidad(0.0);

	int tiempo = Timer::getTimeElapsed();
	if(_ultReg == 0 || tiempo-_ultReg > 1000){
		_enemy->incVida();
		_ultReg = tiempo;
	}

	if(_angInicial == INFINITY){
		_angInicial = _enemy->getVisionX();
	}

	_enemy->setVisionX(_enemy->getVisionX() + _angGiroPorCiclo);
	_enemy->setVelocidad(0.0);
}

void StateRegenerate::Transition() {
	int vidaRes = _enemy->getVidaRestante();
	int vidaTotal = _enemy->getVidaTotal();

	if(vidaRes == vidaTotal){
		SM->ChangeState(StateMachineEnemy::Patrol);
	}

	//cout<<"StateRegenerate: vida "<<vidaRes<<endl;

	if(_SM->SeVe()){
		if(vidaRes > vidaTotal*75/100){
			_angInicial = INFINITY;
			SM->ChangeState(StateMachineEnemy::Attack);
		}
		else {
			_angInicial = INFINITY;
			SM->ChangeState(StateMachineEnemy::Escape);
		}
	}
}

}
