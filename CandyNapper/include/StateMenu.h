/*
 * InitState.h
 *
 *  Created on: 22/11/2011
 *      Author: kaseyo
 */

#ifndef INITSTATE_H_
#define INITSTATE_H_

#include "State.h"
#include "Raton.h"
#include "InterfazMusic.h"

namespace candy {
	class InterfazGraphics;

/**
 * \addtogroup GameState
 * @{
 */
	class Application;

	/**
	 * @class MenuState
	 * @brief Estado inicial que muestra el menu
	 * Estado de entrada, que se encarga de mostrar el menu del juego
	 */
	class StateMenu : public State {
	public:
		/**
		 * Constructor por defecto
		 */
		StateMenu();

		/**
		 * Destructor por defecto
		 */
		virtual ~StateMenu();

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
		InterfazGraphics* _iGrafica;
		Application* _owner;
		bool _pasarJuego;
		bool _salir;
		bool _partidaRapida;
		bool _cargar;
	};

} /* namespace candy */
#endif /* INITSTATE_H_ */
