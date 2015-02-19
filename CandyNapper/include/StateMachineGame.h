/*
 * SMGSManager.h
 *
 *  Created on: Nov 23, 2011
 *      Author: carrillo
 */

#ifndef SMGSMANAGER_H_
#define SMGSMANAGER_H_

#include "StateMachine.h"


namespace candy {
	class CandyNapper;

	/**
	 * Maquina del juego, encargada de gestionar los estados del juego en si
	 * pause, play ...
	 */
	class StateMachineGame : public StateMachine {
	public:
		/**
		 * Constructor
		 */
		StateMachineGame();

		/**
		 * Destructor
		 */
		~StateMachineGame();

		/**
		 * Flag para indicar que la máquina de estados se encuentra en el estado salir
		 * y el juego debe de finalizar
		 * @param s
		 */
		void setSalir(bool s);
		/**
		 * Para saber si la máquina se encuentra en el estado salir
		 * @return Si esta en el estado salir
		 */
		bool getSalir();

		/**
		 * Enumeracion de estados
		 */
		enum Estados{
			Menu=0,       //!< Init
			Play=1,       //!< Play
			Pause=2,      //!< Pause
			Exit=3,       //!< Exit
			ChangeLevel,
			GameOver,
			Win
		};
	private:
		bool salir;
	};

} /* namespace candy */
#endif /* SMGSMANAGER_H_ */
