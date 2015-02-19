/*
 * CompLogic.h
 *
 *  Created on: 12/05/2012
 *      Author: carrillo
 */

#ifndef COMPLOGIC_H_
#define COMPLOGIC_H_

#include "IComponent.h"


namespace candy {

class CompLogic : public IComponent {
public:
	CompLogic();
	virtual ~CompLogic();
	void Update(GameEntity* entidad);
};

} /* namespace candy */
#endif /* COMPLOGIC_H_ */
