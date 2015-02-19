/*
 * StateMachineEnemy.h
 *
 *  Created on: 01/03/2012
 *      Author: esteve
 */

#ifndef STATEMACHINEENEMY_H_
#define STATEMACHINEENEMY_H_
using namespace std;
#include "StateMachine.h"
#include "IPathfinding.h"
#include "InterfazPhysics.h"
#include "Enemy.h"
#include <math.h>

//DEBUG
#include "InterfazGraphics.h"
#include "InterfazPathfinding.h"
#include "World3D.h"
#include <vector>
//FIN DEBUG

namespace candy {
class CompIA;
class StateMachineEnemy : public StateMachine {
private:
	Enemy* _enemy;

public:
	enum States {Patrol = 0, Follow = 1, Stand = 2, Escape = 3, Attack = 4, Regenerate = 5};

	StateMachineEnemy(Enemy* e);
	StateMachineEnemy(int id, vector<State*> states, State* cs, State* is);
	~StateMachineEnemy();
	bool SeVe();
	Vector3 ObtRandPos();
	Enemy* getEnemy();
};
}

#endif /* STATEMACHINEENEMY_H_ */
