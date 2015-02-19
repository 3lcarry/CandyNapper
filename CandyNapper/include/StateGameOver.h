/*
 * StateGameOver.h
 *
 *  Created on: 24/05/2012
 *      Author: esteve
 */

#ifndef STATEGAMEOVER_H_
#define STATEGAMEOVER_H_

#include "State.h"
#include "Teclado.h"
#include <iostream>
#include "InterfazMusic.h"
#include "InterfazGraphics.h"
#include "Application.h"
using namespace std;

namespace candy
{

	class StateGameOver : public State  {
	public:
		StateGameOver();
		virtual ~StateGameOver();

		/**
		 * Las posibles transicion que hay desde play
		 */
		void Transition();
		/**
		 * Actualiza los motores del juego
		 */
		void Execute();

	private:
		bool _Reintentar;
		bool _irMenuPrincipal;
		bool _salir;
		InterfazGraphics* _iGrafica;
	};

}

#endif /* STATEGAMEOVER_H_ */
