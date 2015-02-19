/*
 * StateFollow.cpp
 *
 *  Created on: 05/03/2012
 *      Author: esteve
 */

#include "StateFollow.h"

namespace candy {

StateFollow::StateFollow() : State(){
	_ultRecalculo = 0;
	_angulo = 0.0;
	_dist_perder = 0;
	_enemy = NULL;
	_pathfinding = InterfazPathfinding::getInstance();
	_ultVision = 0;
}

StateFollow::StateFollow(int id, StateMachineEnemy* sm) : State(id, sm){
	_ultRecalculo = 0;
	_angulo = 0.0;
	_enemy = sm->getEnemy();
	_dist_perder = sm->getEnemy()->getAttack()->getDistVisM();
	_pathfinding = InterfazPathfinding::getInstance();
	_ultVision = 0;
}

StateFollow::~StateFollow() {
	SM = NULL;
}

/*void StateFollow::Transition() {
	GEDynamic* player = EntityManager::getInstance()->getPlayer();
	InterfazPhysics* ip = InterfazPhysics::getInstance();

	if (player != NULL) {
		Vector3 pos_player = player->getPosicion();

		Vector3 pos_Enemy = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getPosicion();
		Attack* ataque = ((StateMachineEnemy*)SM)->getOwner()->getEnemy()->getAttack();

		//cout << pos_Enemy << endl;
			//	cout << pos_player << endl;

		double dist_player = pos_Enemy.Distancia(pos_player);

		if(dist_player < ataque->getRango()){
			//cout<<"CAMBIO A ATACAR"<<endl;
			SM->ChangeState(StateMachineEnemy::Attack);
		}



		else if(dist_player > dist_perder || ip->obstaculo(pos_Enemy, pos_player)){
			//cout<<"CAMBIO A PATRULLAR"<<endl;
			SM->ChangeState(StateMachineEnemy::Patrol);
		}

		Enemy::TipoEnemigo tipo = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getTipoEnemigo();
		if(tipo != Enemy::Melon){

			int vidaRes = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getVidaRestante();
			int vidaTotal = ((StateMachineEnemy*) SM)->getOwner()->getEnemy()->getVidaTotal();
			//cout<<"vidaRes "<<vidaRes<<endl;
			if(vidaRes < vidaTotal*30/100){
				//cout<<"CAMBIA A HUIR"<<endl;
				SM->ChangeState(StateMachineEnemy::Escape);
			}
		}
	}
}*/

bool StateFollow::SeVe() {
	bool seve = false;
	GEDynamic* player = CandyNapper::getInstancia()->getEm()->getPlayer();

	if(player != NULL) {
		Vector3 posEnemy = _enemy->getPosicion();
		Vector3 posPlayer = player->getPosicion();


		if(posEnemy.Distancia(posPlayer) < _enemy->getAttack()->getDistVisP()) {

			double angEnemyPlayer = InterfazPathfinding::getInstance()->ObtAngulo(posEnemy, posPlayer);
			double angEnemy =  _enemy->getVisionX();

			double angAux;

			if(angEnemy == 0)
				angEnemy = 2*M_PI;

			if(angEnemyPlayer > angEnemy)
				angAux = angEnemyPlayer - angEnemy;
			else
				angAux = angEnemy - angEnemyPlayer;

			//Normalizar angulo
			while(angAux > 2*M_PI)
				angAux -= 2*M_PI;
			while(angAux < 0)
				angAux += 2*M_PI;


			if(angAux < _enemy->getAttack()->getCampVision()/2){
				if(!InterfazPhysics::getInstance()->obstaculo(posEnemy, posPlayer))
					seve = true;
			}

		}
		else {
			seve = false;
		}
	}

	return seve;
}

void StateFollow::Transition() {
	Player *player = CandyNapper::getInstancia()->getEm()->getPlayer();
	if(player != NULL){
		Vector3 posPlayer = player->getPosicion();
		Vector3 posEnemy = _enemy->getPosicion();

		if(SeVe() || _ultVision == 0)
			_ultVision = Timer::getTimeElapsed();

		int tiempo = Timer::getTimeElapsed();

		/*cout<<endl;
		cout<<"StateFollow : tiempo "<<tiempo<<endl;
		cout<<"STateFollow : _ultVision "<<_ultVision<<endl;*/

		if(posEnemy.Distancia(posPlayer) < _enemy->getAttack()->getRango()){
			SM->ChangeState(StateMachineEnemy::Attack);
			_ultVision = 0;
		}
		else if(/*posEnemy.Distancia(posPlayer) > _enemy->getAttack()->getDistVisM() && */tiempo - _ultVision > 5000){
			SM->ChangeState(StateMachineEnemy::Patrol);
			_ultVision = 0;
		}

	}
}


void StateFollow::Execute(){
	Text* texto = InterfazGraphics::getInstance()->getHUD()->getText2();
	//texto->setTexto("ESTADO FOLLOW");

	GEDynamic* player = CandyNapper::getInstancia()->getEm()->getPlayer();

	if(player != NULL){

		Vector3 posPlayer = player->getPosicion();
		Vector3 posEnemy = _enemy->getPosicion();
		int tiempo = Timer::getTimeElapsed();

		if(posPlayer.Distancia(posEnemy) > _enemy->getRadio()*2){

			if((_ultPos != posPlayer && tiempo - _ultRecalculo > 500) || _camino.empty()){
				//cout<<"StateFollow: Va a recalcular el camino"<<endl;
				_camino = _pathfinding->ObtCamino(posEnemy, posPlayer);
				_ultRecalculo = tiempo;
			}
			/*else if(_ultPos == posPlayer && posEnemy.Distancia(_sigPos) < 0.2){
				_camino = _pathfinding->ObtCamino(posEnemy, posPlayer);
			}*/

			/*cout<<endl;
			cout<<"StateFollow: _camino.size "<<_camino.size()<<endl;*/

			/*try{
				_sigPos = _pathfinding->Suavizado(_camino, _enemy);
			}
			catch (int e) {
				_camino = _pathfinding->ObtCamino(posEnemy, posPlayer);
				if(_camino.empty())
					_sigPos = posPlayer;
				else
					_sigPos = _pathfinding->Suavizado(_camino, _enemy);
			}*/

			//cout<<"StateFollow: _camino.size() "<<_camino.size()<<endl;
			try {
				_sigPos = _pathfinding->Suavizado(_camino, _enemy);
			}
			catch (int ex){
				_sigPos = posPlayer;
			}
			/*for(int i = 0; i < _camino.size(); i++){
				cout<<_camino[i]<<endl;
			}*/
			/*cout<<endl;
			cout<<"StateFollow: posEnemy "<<posEnemy<<endl;
			cout<<"StateFollow: sigPos "<<_sigPos<<endl;
			cout<<"StateFollow: dist"<<posEnemy.Distancia(_sigPos)<<endl;
			cout<<endl;
			cout<<endl;*/

			//cout<<"StateFollow:  posEnemy "<<posEnemy<<endl;
			//cout<<"StateFollow: _sigPos "<<_sigPos<<endl;
			_angulo = _pathfinding->ObtAngulo(posEnemy, _sigPos);
			//cout<<endl;
			//cout<<"StateFollow: angulo "<<_angulo<<endl;
			//cout<<"StateFollow: VelocidadEnemigo "<<Enemy::VelocidadEnemigo<<endl;

			_enemy->setVisionX(_angulo);
			_enemy->setVelocidad(Enemy::VelocidadEnemigo);
		}
		else
			_enemy->setVelocidad(0.0);
		_ultPos = posPlayer;
	}
}

}
