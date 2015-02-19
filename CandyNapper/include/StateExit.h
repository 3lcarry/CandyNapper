/*
 * ExitState.h
 *
 *  Created on: Nov 25, 2011
 *      Author: carrillo
 */

#ifndef EXITSTATE_H_
#define EXITSTATE_H_

#include "State.h"

#include <iostream>
using namespace std;

namespace candy {
/**
 * Estado que finaliza el juego, se encarga de liberar toda la memoria y poner el flag de salir de la maquina de estados
 * a true
 */
class StateExit: public State {
public:
	/**
	 * Constructor por defecto del estado salir
	 */
	StateExit();
	/**
	 * Destructor del estado
	 */
	virtual ~StateExit();
	/**
	 * Transicion, la cual esta vacia ya que, no se puede salir de este estado
	 */
	void Transition();
	/**
	 * Debe liberar la memoria y poner el flag de salir a true
	 */
	void Execute();
};

} /* namespace candy */
#endif /* EXITSTATE_H_ */
