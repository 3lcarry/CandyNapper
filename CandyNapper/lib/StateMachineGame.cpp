/*
 * SMGSManager.cpp
 *
 *  Created on: Nov 23, 2011
 *      Author: carrillo
 */

#include "StateMachineGame.h"
#include "StateMenu.h"
#include "StatePlay.h"
#include "StatePause.h"
#include "StateExit.h"
#include "StateChangeLevel.h"
#include "StateGameOver.h"
#include "StateWin.h"

#include "Timer.h"

namespace candy {

StateMachineGame::StateMachineGame()
	:StateMachine()
{
	StateMenu* ms = new StateMenu();
	StatePlay* ps = new StatePlay();
	StatePause* pas = new StatePause();
	StateExit* es = new StateExit();
	StateChangeLevel* cl = new StateChangeLevel();
	StateGameOver* go = new StateGameOver();
	StateWin* ws = new StateWin();

	AddState(ms);
	AddState(ps);
	AddState(pas);
	AddState(es);
	AddState(cl);
	AddState(go);
	AddState(ws);

	this->setInitialState(ms);
	this->setCurrentState(ms);

	salir = false;
}

StateMachineGame::~StateMachineGame() {

}

void StateMachineGame::setSalir(bool s) {
	salir = s;
}

bool StateMachineGame::getSalir() {
	return salir;
}

} /* namespace candy */
