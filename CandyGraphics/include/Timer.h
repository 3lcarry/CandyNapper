/*
 * Timer.h
 *
 *  Created on: 25/02/2012
 *      Author: kaseyo
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "SFML/System.hpp"

namespace candy {
/**
 * \addtogroup CandyEngine
 * @{
 */

	/**
	 * @class Timer
	 * Reloj del juego (necesario para temporarizar cosas
	 */
	class Timer {
	public:
		/**
		 * Constructor por defecto
		 */
		Timer();

		/**
		 * Destructor
		 */
		~Timer();

		/**
		 * Devuelve el numero de milisegundos desde la ultima vez que llamamos a esta funcion
		 * (tiemp parcial)
		 * @return Milisegundos parciales
		 */
		static long int getTimeElapsed();

		/**
		 * Inicializa el reloj a 0
		 * @return Devuelve los milisegundos totales transcurridos
		 */
		static long int Init();

	private:
		/**
		 * Reloj del sistema de la SFML
		 */
		static sf::Clock _reloj;
	};

} /* namespace candy */
#endif /* TIMER_H_ */
