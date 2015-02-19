/*
 * ExitState.cpp
 *
 *  Created on: Nov 25, 2011
 *      Author: carrillo
 */

#include "StateExit.h"
#include "StateMachineGame.h"

namespace candy {

StateExit::StateExit()
	:State(StateMachineGame::Exit)
{
	//ID = StateMachineGame::Exit;
	//SM = NULL;
}

StateExit::~StateExit() {
}

void StateExit::Transition() {
	//Si no se deseara salir, se volveria al play
}

void StateExit::Execute() {
	//Aqui deberiamos mostrar el menu de "Desea salir?"
	((StateMachineGame*)SM)->setSalir(true);
}

} /* namespace candy */
