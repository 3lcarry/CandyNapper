/*
 * GSManager.h
 *
 *  Created on: 22/11/2011
 *      Author: kaseyo
 */

#ifndef CANDYNAPPER_H_
#define CANDYNAPPER_H_

#include <iostream>
using namespace std;

#include "StateMachine.h"
#include "EntityManager.h"
#include "InterfazPhysics.h"
//#include "InterfazIA.h"
#include "InterfazGraphics.h"
//#include "IPathfinding.h"
#include "ParserCandy.h"
#include "InterfazPathfinding.h"


namespace candy {

/**
 * \addtogroup GameState
 * Modulo encargado de la maquina de estados del juego, así como de su "estado" en general.
 * @{
 */
	/**
	 * @class GSManager
	 * @brief Game State Manager
	 * Clase que gestiona el estado actual del juego, así como la maquina de estados.
	 */
	class StateMachineGame;

	class CandyNapper{
	public:
		static CandyNapper* getInstancia();

		/**
		 * Destructor
		 */
		~CandyNapper();

	    EntityManager *getEm() const;

	    void Init();

	    string Serializar() const;

	    bool ChangeLevel();

	    void setChangeLevel(bool cl);

	    string getNextLevel();

	    void setNextLevel(string lv);

	    bool isGameComplete();

	    void setGameComplete(bool gc);

	    string getActualLevel();

	    void setActualLevel(string level);

	    bool isPartidaRapida;


	private:
	    /**
		 * Constructor, creara la máquina de estados
		 * y inicializara todos los motores
		 */
		CandyNapper();
	    /**
		 * Variable para el EntityManager
		 */
	    EntityManager* em;

	    static CandyNapper* instancia;

	    bool changeLevel;

	    bool gameComplete;

	    string _actLevel;

	    string nextLevel;
	};
} /* namespace candy */
#endif /* GSMANAGER_H_ */
