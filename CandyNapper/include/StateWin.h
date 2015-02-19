/*
 * StateWin.h
 *
 *  Created on: 25/05/2012
 *      Author: esteve
 */

#ifndef STATEWIN_H_
#define STATEWIN_H_

#include "State.h"
#include "Teclado.h"
#include <iostream>
#include "InterfazMusic.h"
#include "InterfazGraphics.h"
#include "Application.h"
using namespace std;

namespace candy {

class StateWin: public candy::State {
private:
	bool _irMenuPrincipal;
	InterfazGraphics* _iGrafica;

public:
	StateWin();
	~StateWin();
	/**
	 * Las posibles transicion que hay desde play
	 */
	void Transition();
	/**
	 * Actualiza los motores del juego
	 */
	void Execute();
};

}

#endif /* STATEWIN_H_ */
