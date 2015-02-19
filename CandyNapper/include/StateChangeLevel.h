/*
 * StateChangeLevel.h
 *
 *  Created on: 17/05/2012
 *      Author: carrillo
 */

#ifndef STATECHANGELEVEL_H_
#define STATECHANGELEVEL_H_

#include <iostream>
#include "State.h"
using namespace std;

namespace candy {

class Application;

class StateChangeLevel : public State {
public:
	StateChangeLevel();
	virtual ~StateChangeLevel();
	/**
	 * @brief Transicion a otros estados
	 * Implementacion del metodo de State
	 */
	void Transition();

	/**
	 * @brief Codigo del estado
	 * Implementacion del metodo de State
	 */
	void Execute();


private:
	Application* owner;
	string nextLevel;
	bool firstime;
	bool continuar;

};

} /* namespace candy */
#endif /* STATECHANGELEVEL_H_ */
