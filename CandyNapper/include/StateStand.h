/*
 * StateStand.h
 *
 *  Created on: 15/03/2012
 *      Author: esteve
 */

#ifndef STATESTAND_H_
#define STATESTAND_H_
#include "State.h"
#include "GEDynamic.h"
#include "StateMachineEnemy.h"
#include "CompLogic.h"
#include "EntityManager.h"
#include "Timer.h"
#include "Player.h"
#include "Vector2.h"
#include "StatePatrol.h"
#include "StateFollow.h"
#include "InterfazGraphics.h"
#include "HUD.h"
#include <sstream>

namespace candy {

class StateStand : public State{
private:
	StateMachineEnemy* _SM;
	Enemy* _enemy;
	double _angInicial;
	double _angGiroPorCiclo;
	double _angAcumulado;
	bool _goback;
	bool _follow;
public:
	StateStand();
	StateStand(int id, StateMachineEnemy* sm);
	~StateStand();
	void Execute();
	void Transition();
};
}

#endif /* STATESTAND_H_ */
