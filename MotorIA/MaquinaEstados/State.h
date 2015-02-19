/*
 * state.h
 *
 *  Created on: 07/11/2011
 *      Author: esteve
 */

#ifndef STATE_H_
#define STATE_H_

#include<iostream>
using namespace std;
#include<vector>

namespace candy{
	class StateMachine;

	/**
	 * Class State
	 * @brief Estado genérico para la máquina de estados
	 * Sirve para la creación de estados genéricos para que sean utilizados en una máquina de estados
	 */
	class State {
		protected:
			/**
			 * ID del estado
			 */
			int ID;
			/**
			 * Puntero a la máquina de estados a la que pertenece
			 */
			StateMachine* SM;

		public:
			/**
			 * Constructor por defecto
			 */
			State();

			/**
			 * Constructor
			 * @param ID de la máquina de estados
			 */
			State(int id);

			/**
			 * Constructor
			 * @param ID de la máquina de estados
			 * @param puntero a la máquina de estados al que pertenece
			 */
			State(int id, StateMachine* sm);

			/**
			 * Destructor
			 */
			virtual ~State();

			/**
			 * Añade la ID al estado
			 * @param ID del estado
			 */
			void setID(int id);
			/**
			 * Devuelve el ID del estado
			 * @return ID del estado
			 */
			int getID();

			/**
			 * Indica el propiterario del estado
			 * @param puntero a la máquina de estados a la que pertenece el estado
			 */
			void setStateMachine(StateMachine *sm);

			/**
			 * Devuelve a que máquina de estados pertene este estado
			 * @return ID de la máquina de estados
			 */
			int getStateMachine();
			/**
			 * Se obtiene un estado a partir de su ID
			 * @param ID del estado a buscar
			 * @param puntero al estado que se buscaba
			 */
			State* getStateByID(int id);

			/**
			 * Sirbe para cambiar de estado
			 * @param ID del estado al que se quiere cambiar
			 * @return boleano que indica si el cambio a sido correcto
			 */
			bool ChangeTo(int id);

			/**
			 * Función para establecer las transiciones de estados
			 */
			virtual void Transition() = 0;

			/**
			 * Función para ejecutar el estado actual
			 */
			virtual void Execute() = 0;
	};
}
#endif /*STATE_H_*/
