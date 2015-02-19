/*
 * PlayState.h
 *
 *  Created on: Nov 23, 2011
 *      Author: carrillo
 */

#ifndef PLAYSTATE_H_
#define PLAYSTATE_H_
#include "State.h"
#include "Teclado.h"
#include <iostream>
#include "InterfazMusic.h"
using namespace std;

namespace candy  {
	class InterfazPhysics;
	class InterfazGraphics;
	class EntityManager;

	/**
	 * Estado Play
	 * Estado principal, donde se "ejecuta" realmente el juego
	 */
	class StatePlay : public State {
	public:
		/**
		 * Constructor
		 */
		StatePlay();
		/**
		 * Destructor
		 */
		virtual ~StatePlay();
		/**
		 * Las posibles transicion que hay desde play
		 */
		void Transition();
		/**
		 * Actualiza los motores del juego
		 */
		void Execute();

	private:
		float _tickTime;

		InterfazPhysics* _if;

		InterfazGraphics* _ig;


		bool _pausa;

		Teclado _teclado;

		int _idSoundBird;

		int _lastTimeSound;
	};

} /* namespace candy */
#endif /* PLAYSTATE_H_ */
