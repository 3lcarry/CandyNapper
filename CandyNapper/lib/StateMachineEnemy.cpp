/*
 * StateMachineEnemy.cpp
 *
 *  Created on: 01/03/2012
 *      Author: esteve
 */

#include "StateMachineEnemy.h"
#include "CompIA.h"
#include "CandyNapper.h"

namespace candy{


StateMachineEnemy::StateMachineEnemy(Enemy* e){
	_enemy = e;
}

StateMachineEnemy::StateMachineEnemy(int id, vector<State*> states, State* cs, State* is) : StateMachine(id, states, cs, is) {

}

StateMachineEnemy::~StateMachineEnemy() {
	/*for (unsigned i = 0; i < States.size(); i++) {
		delete States[i];
		States[i] = NULL;
	}*/
	CurrentState = NULL;
	InitialState = NULL;
}

Vector3 StateMachineEnemy::ObtRandPos(){
	Vector3 r;

	do{
		double x = rand()%300;  ///Cambiar segun el tamaño del mapa
		double z = rand()%400;
		if (Timer::getTimeElapsed()%5 == 0) {
			r.setX(x*-1);
			r.setY(0.0);
			r.setZ(z*-1);

		} else if (Timer::getTimeElapsed() % 3 == 0) {
			r.setX(x*-1);
			r.setY(0.0);
			r.setZ(z );

		} else if (Timer::getTimeElapsed() % 2 == 0) {
			r.setX(x);
			r.setY(0.0);
			r.setZ(z*-1);
		} else {
			r.setX(x);
			r.setY(0.0);
			r.setZ(z);

		}
	}while(!InterfazPathfinding::getInstance()->EsTransitable(r));

	return r;
}

bool StateMachineEnemy::SeVe() {
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


Enemy* StateMachineEnemy::getEnemy(){
	return _enemy;
}

}


