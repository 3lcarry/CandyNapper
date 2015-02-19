/*
 * PauseState.h
 *
 *  Created on: Nov 25, 2011
 *      Author: carrillo
 */

#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "State.h"

namespace candy {
	class InterfazGraphics;
	class EntityManager;

	/**
	 * Estado Pause,
	 * este estado deja pausados los motores excepto el motor InOut para ver si se pulsan teclas y salir del estado
	 * pause
	 */
	class StatePause: public State {
	public:
		/**
		 * Constructor
		 */
		StatePause();
		/**
		 * Destructor
		 */
		virtual ~StatePause();
		/**
		 * Transicion que saldra del estado pause
		 */
		void Transition();
		/**
		 * Solo actualiza InOut
		 */
		void Execute();

		void comprobarBotones();
	private:
		/**
		 * Decodifica la consola segun lo que haya introducido
		 */
		void decodeConsole();

		InterfazGraphics* _ig;


		bool _salir;
		bool _continuar;
		bool _menuPrincipal;
	};

} /* namespace candy */
#endif /* PAUSESTATE_H_ */
