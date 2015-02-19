/*
 * CompLogic.h
 *
 *  Created on: 01/03/2012
 *      Author: esteve
 */

#ifndef COMPIA_H_
#define COMPIA_H_

#include "GEDynamic.h"
#include "StateMachineEnemy.h"
#include "Enemy.h"


namespace candy{
class CompIA : public IComponent{
private:
	StateMachine* _SM;
public:
	CompIA(Enemy* enemy);
	~CompIA();
	void Update(GameEntity* entity);
};
}

#endif /* COMPLOGIC_H_ */
