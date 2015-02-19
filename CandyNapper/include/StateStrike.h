/*
 * StateStrike.h
 *
 *  Created on: 18/03/2012
 *      Author: esteve
 */

#ifndef STATESTRIKE_H_
#define STATESTRIKE_H_
#include "State.h"
#include "GEDynamic.h"
#include "StateMachineEnemy.h"
#include "CompIA.h"
#include "EntityManager.h"
#include "InterfazGraphics.h"
#include "InterfazPathfinding.h"
#include "HUD.h"


namespace candy {

class StateStrike : public State {
private:
	Enemy* _enemy;
public:
	StateStrike();
	StateStrike(int id, StateMachineEnemy* sm);
	~StateStrike();
	void Transition();
	void Execute();
};

}

#endif /* STATESTRIKE_H_ */
