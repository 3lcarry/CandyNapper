/*
 * StateEscape.h
 *
 *  Created on: 18/03/2012
 *      Author: esteve
 */

#ifndef STATEESCAPE_H_
#define STATEESCAPE_H_
#include "State.h"
#include "StateMachineEnemy.h"
#include "CompLogic.h"
#include "CandyNapper.h"
#include "InterfazGraphics.h"
#include "HUD.h"
#include "InterfazPathfinding.h"
#include <sstream>


namespace candy {

class StateEscape : public State{
private:
	static const double _angDondeNoHuir;
	StateMachineEnemy* _SM;
	Enemy* _enemy;
	Vector3* _randPos;
	vector<Vector3> _camino;
	bool HaciaPlayer(Vector3 pos);
public:
	StateEscape();
	StateEscape(int id, StateMachineEnemy* sm);
	~StateEscape();
	void Transition();
	void Execute();
};

}

#endif /* STATEESCAPE_H_ */
