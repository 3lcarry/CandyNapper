/*
 * StateEscape.cpp
 *
 *  Created on: 18/03/2012
 *      Author: esteve
 */

#include "StateEscape.h"

namespace candy {

const double StateEscape::_angDondeNoHuir = 30*M_PI/180; //30grados

bool StateEscape::HaciaPlayer(Vector3 pos){
	GEDynamic* player = CandyNapper::getInstancia()->getEm()->getPlayer();


	bool va = false;

	Text* texto = InterfazGraphics::getInstance()->getHUD()->getText2();

	if(player != NULL) {
		Vector3 posEnemy = _enemy->getPosicion();
		Vector3 posPlayer = player->getPosicion();
		double angPlayer = InterfazPathfinding::getInstance()->ObtAngulo(posEnemy, posPlayer);
		double angPos = InterfazPathfinding::getInstance()->ObtAngulo(posEnemy, pos);
		double angAux;

		if(angPlayer == 0.0)
			angPlayer = 2*M_PI;

		if(angPos == 0.0)
			angPos == 2*M_PI;

		if(angPos > angPlayer)
			angAux = angPos - angPlayer;
		else
			angAux = angPlayer - angPos;

		while(angAux > 2*M_PI)
			angAux -= 2*M_PI;
		while(angAux < 0)
			angAux += 2*M_PI;



		if(angAux < _angDondeNoHuir)
			va = true;

		/*stringstream ss (stringstream::in | stringstream::out);

		if(va)
			ss<<"angAux = "<<rad2grad(angAux)<<" _angDondeNoHuir "<<rad2grad(_angDondeNoHuir)<<" VA = TRUE";
		else
			ss<<"angAux = "<<rad2grad(angAux)<<" _angDondeNoHuir "<<rad2grad(_angDondeNoHuir)<<" VA = FALSE";

		texto->setTexto(ss.str());*/

	}

	return va;
}

StateEscape::StateEscape() : State(){
	_SM = NULL;
	_enemy = NULL;
	_randPos = NULL;
}

StateEscape::StateEscape(int id, StateMachineEnemy* sm) : State(id, sm){
	_SM = ((StateMachineEnemy*)SM);
	_enemy = sm->getEnemy();
	_randPos = NULL;
}

StateEscape::~StateEscape(){
	delete _randPos;
	_randPos = NULL;
	_enemy = NULL;
}

void StateEscape::Transition(){
	Vector3 myPos = _enemy->getPosicion();

	if(myPos.Distancia(*_randPos) < 1){
		//cout<<"CAMBIA A REGENERAR"<<endl;
		delete _randPos;
		_randPos = NULL;
		SM->ChangeState(StateMachineEnemy::Regenerate);
	}

}

void StateEscape::Execute(){

	Text* texto = InterfazGraphics::getInstance()->getHUD()->getText2();
	//texto->setTexto("ESTADO ESCAPE");

	if(_randPos == NULL){
		GEDynamic* player = CandyNapper::getInstancia()->getEm()->getPlayer();

		if(player != NULL){
			//int cont = 0;
			do {
				Vector3 pos = _SM->ObtRandPos();
				delete _randPos;
				_randPos = new Vector3(pos.getX(), pos.getY(), pos.getZ());
				stringstream ss (stringstream::in | stringstream::out);
				//cout<<endl<<"StateEscape: cont "<<cont<<endl;
				//cont++;
			}while(HaciaPlayer(*_randPos) || player->getPosicion().Distancia(*_randPos) < 150);
			//cont = 0;
		}
		_camino = InterfazPathfinding::getInstance()->ObtCamino(_enemy->getPosicion(), *_randPos);
	}

	if(_randPos != NULL){
		//cout<<"RandPos "<<*RandPos<<endl;

		Vector3 posEnemy = _enemy->getPosicion();
		Vector3 sigPos;
		try {
			 sigPos = InterfazPathfinding::getInstance()->Suavizado(_camino, _enemy);
		}
		catch (int ex) {
			sigPos = *_randPos;
		}
		double angulo = InterfazPathfinding::getInstance()->ObtAngulo(posEnemy, *_randPos);

		_enemy->setVisionX(angulo);
		_enemy->setVelocidad(Enemy::VelocidadNormal);
	}

}

}
