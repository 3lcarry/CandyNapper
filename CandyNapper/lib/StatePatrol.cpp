/*
 * StateAttack.cpp
 *
 *  Created on: 01/03/2012
 *      Author: esteve
 */
#include "StatePatrol.h"


namespace candy{

const double StatePatrol::_angGiro = 15*M_PI/180; //15grados

/*double StatePatrol::ObtDist(Vector3 v, Nodo* n){
	return (sqrt(pow((v.getX() - n->getX()), 2) + pow((v.getZ() - n->getZ()), 2)));
}

double StatePatrol::ObtDist(Vector3 v1, Vector3 v2){
	return (sqrt(pow((v1.getX() - v2.getX()), 2) + pow((v1.getZ() - v2.getZ()), 2)));
}*/

StatePatrol::StatePatrol(){
	_SM = NULL;
	_angMovimiento = 0.0;
	_randPos = NULL;
	_enemy = NULL;
	_cont = 0;
	_change = 0;
	_angGiroPorCiclo = grad2rad(30)/120;
	_angGiroAct = 0;
	srand(time(NULL)*Timer::getTimeElapsed()*M_PI*-37);
}

StatePatrol::StatePatrol(int id, StateMachineEnemy* sm) : State(id, sm) {
	_SM = ((StateMachineEnemy*)SM);
	_angMovimiento = 0.0;
	_randPos = NULL;
	_enemy = sm->getEnemy();
	_cont = 0;
	_change = 0;
	_angGiroPorCiclo = grad2rad(30)/120;;
	_angGiroAct = 0;
	srand(time(NULL)*Timer::getTimeElapsed()*M_PI*-37);
}

StatePatrol::~StatePatrol(){
	delete _randPos;
	_randPos = NULL;
	_enemy = NULL;
	_SM = NULL;
}

//void StatePatrol::Transition(){
	/*if(stand){
		//cout<<"CAMBIO A STAND"<<endl;
		cont = 0;
		SM->ChangeState(StateMachineEnemy::Stand);
	}
	if(SeVe()){
		//cout<<"CAMBIO A PRESEGUIR"<<endl;
		cont = 0;
		stand = false;
		Obj = NULL;
		SM->ChangeState(StateMachineEnemy::Follow);
	}*/
//}



void StatePatrol::Transition(){

	/*cout<<endl;
	cout<<"StatePatrol: _randPos "<<*_randPos<<endl;
	cout<<"StatePatrol: enemyPos"<<_enemy->getPosicion()<<endl;*/
	if(_SM->SeVe()){
		_randPos = NULL;
		SM->ChangeState(StateMachineEnemy::Follow);
	}
	else if(_randPos != NULL && _enemy->getPosicion().Distancia(*_randPos) < 1.0){
		_randPos = NULL;
		SM->ChangeState(StateMachineEnemy::Stand);
	}

}

void StatePatrol::Execute(){
	Text* texto = InterfazGraphics::getInstance()->getHUD()->getText2();
	//texto->setTexto("ESTADO PATROL");

	Vector3 posEnemy = _enemy->getPosicion();
	//double angEnemy = _enemy->getVisionX();

	if(_randPos == NULL){
		Vector3 aux = _SM->ObtRandPos();
		_randPos = new Vector3(aux.getX(), aux.getY(), aux.getZ());
		_camino = InterfazPathfinding::getInstance()->ObtCamino(posEnemy, *_randPos);
	}

	/*try {
		_sigPos = InterfazPathfinding::getInstance()->Suavizado(_camino, _enemy);
	}
	catch (int e) {
		Vector3 aux = _SM->ObtRandPos();
		_randPos = new Vector3(aux.getX(), aux.getY(), aux.getZ());
		_camino = InterfazPathfinding::getInstance()->ObtCamino(posEnemy, *_randPos);
		if(!_camino.empty())
			_sigPos = InterfazPathfinding::getInstance()->Suavizado(_camino, _enemy);
	}*/
	try {
		_sigPos = InterfazPathfinding::getInstance()->Suavizado(_camino, _enemy);
	}
	catch (int ex) {
		_sigPos = *_randPos;
	}
	//cout<<"StatePatrol: _sigPos "<<_sigPos<<endl;

	_angMovimiento = InterfazPathfinding::getInstance()->ObtAngulo(posEnemy, _sigPos);

	if(_cont == 60){
		_change++;
	}
	else if(_cont == 180){
		_change++;
	}
	else if(_cont == 240){
		_change=0;
		_cont = 0;
	}

	if(_change == 0 || _change == 2) {
		_angGiroAct += _angGiroPorCiclo;
		_enemy->setVisionX(_angMovimiento + _angGiroAct);
		_enemy->setAnguloMovimiento(- _angGiroAct);
	}
	else if(_change == 1) {
		_angGiroAct -= _angGiroPorCiclo;
		_enemy->setVisionX(_angMovimiento + _angGiroAct);
		_enemy->setAnguloMovimiento(- _angGiroAct);
	}


	_enemy->setVelocidad(Enemy::VelocidadEnemigo);
	_cont++;
}


}
