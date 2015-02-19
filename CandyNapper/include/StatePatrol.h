#ifndef STATEATTACK_H_
#define STATEATTACK_H_
using namespace std;
#include <time.h>
#include "State.h"
#include "StateMachineEnemy.h"
#include "EntityManager.h"
#include "CompIA.h"
#include "Timer.h"
#include "Player.h"
#include "Vector2.h"
#include "poly2tri/poly2tri.h"
#include "InterfazGraphics.h"
#include "HUD.h"
#include "CandyMath.h"
#include "InterfazPathfinding.h"

namespace candy{
using namespace CandyMath;
class StatePatrol: public State {
private:
	static const double _angGiro;
	StateMachineEnemy* _SM;
	double _angMovimiento;
	Vector3* _randPos;
	double _angGiroPorCiclo;
	double _angGiroAct;
	Enemy* _enemy;
	vector<Vector3> _camino;
	Vector3 _sigPos;
	int _cont;
	int _change;


public:
	StatePatrol();
	StatePatrol(int id, StateMachineEnemy* sm);
	~StatePatrol();
	void Transition();
	void Execute();


};
}

#endif /* STATEATTACK_H_ */
