/*
 * StateRegenerate.h
 *
 *  Created on: 18/03/2012
 *      Author: esteve
 */

#ifndef STATEREGENERATE_H_
#define STATEREGENERATE_H_
#include "State.h"
#include "StateMachineEnemy.h"
#include "CompLogic.h"
#include "EntityManager.h"
#include "Timer.h"
#include "InterfazGraphics.h"
#include "HUD.h"
#include "CandyMath.h"
#include "InterfazPathfinding.h"

namespace candy {
using namespace CandyMath;
class StateRegenerate : public State {
private:
	StateMachineEnemy* _SM;
	Enemy* _enemy;
	double _angInicial;
	double _angGiroPorCiclo;
	int _ultReg;
public:
	StateRegenerate();
	StateRegenerate(int id, StateMachineEnemy* sm);
	~StateRegenerate();
	void Transition();
	void Execute();
};

}

#endif /* STATEREGENERATE_H_ */
