/*
 * statemachine.h
 *
 *  Created on: 07/11/2011
 *      Author: esteve
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include<iostream>
using namespace std;
#include <vector>

namespace candy{
	class State;

	/**
	* @class StateMachine
	* @brief Clase generica para la creación de máquinas de estados
	* Sirbe para crear máquinas de estados
	*/
	class StateMachine {
	protected:
		/**
		 * ID de la máquina de estados
		 */
		int ID;
		/**
		 * Conjunto de estados
		 */
		vector<State*> States;
		/**
		 * Estado actual
		 */
		State *CurrentState;
		/**
		 * Estado inicial
		 */
		State *InitialState;

	public:

		/**
		 * Constructor por defecto
		 */
		StateMachine();

		/**
		 * Constructor
		 * @param ID de la máquina de estados
		 * @param conjunto de estados
		 * @param Estado actual
		 * @param Estado inicial
		 * @param Propietario de la máquina de estados
		 */
		StateMachine(int id, vector<State*> states, State* cs, State* is);

		/**
		 * Destructor
		 */
		~StateMachine();

		/**
		 * Obtines la ID a la máquina de estados
		 * return ID de la máquina de estados
		 */
		int getID();

		/**
		 * Devuelve el estado actual de la maquína de estados
		 * @return puntero a estado actual
		 */
		State* getCurrentState();

		/**
		 * Devuelve el estado inicial de la máquina de estados
		 * @return puntero a estado inicial
		 */
		State* getInitialState();

		/**
		 * Devuelve el conjunto de estados de la máquina de estados
		 * @return vetor de punteros a estados
		 */
		vector<State*> getStates();

		/**
		 * Añade la ID a la máquina de estados
		 * @param ID de la maquína de estados
		 */
		void setID(int id);

		/**
		 * Añade el estado actual a la máquina de estados
		 * @param Estado actual de la máquina de estados
		 */
		void setCurrentState(State* s);

		/**
		 * Añade el estado inicial de la máquina de estados
		 * @param Estado inicial de la máquina de estados
		 */
		void setInitialState(State* s);
		/**
		 * Añade un conjunto de estados a la máquina de estados
		 * @param vector de puntero a estados
		 */
		void setStates(vector<State*> s);

		/**
		 * Añade un estado al conjunto de estados de la máquina
		 * @param puntero a estado
		 * @return boleano para indicar que se ha añadido correctamente
		 */
		bool AddState(State* s);
		/**
		 * Cambia de estado
		 * @paran ID del estado
		 * @return boleano para indicar que se ha cambiado correctamente de estado
		 */
		bool ChangeState(int id);

		/**
		 * Actualiza la máquina de estados en cada instante
		 */
		void Update();
	};
}

#endif  /*STATEMACHINE_H_*/
