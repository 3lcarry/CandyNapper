/*
 * StateFollow.h
 *
 *  Created on: 05/03/2012
 *      Author: esteve
 */

#ifndef STATEFOLLOW_H_
#define STATEFOLLOW_H_
#include "State.h"
#include "StateMachineEnemy.h"
#include "CompIA.h"
#include "CandyNapper.h"
#include "Timer.h"
#include <math.h>
#include "InterfazGraphics.h"
#include "InterfazPathfinding.h"
#include "HUD.h"


namespace candy {

class StateFollow : public State{
private:
	vector<Vector3> _camino;
	Vector3 _sigPos;
	Vector3 _ultPos;
	float _angulo;
	int _dist_perder;
	int _ultRecalculo;
	Enemy* _enemy;
	InterfazPathfinding* _pathfinding;
	int _ultVision;
	bool SeVe();


public:
	StateFollow();
	StateFollow(int id, StateMachineEnemy *sm);
	~StateFollow();
	void Transition();
	void Execute();
};

}

#endif /* STATEFOLLOW_H_ */
