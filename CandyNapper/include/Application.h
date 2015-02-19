/*
 * Application.h
 *
 *  Created on: 03/05/2012
 *      Author: carrillo
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "StateMachineGame.h"
#include "CandyNapper.h"
//#include "StateMachine.h"
#include "EntityManager.h"
#include "InterfazPhysics.h"
#include "InterfazGraphics.h"
#include "ParserCandy.h"
#include "InterfazPathfinding.h"
#include "InterfazMusic.h"
#include <fstream>
using namespace std;

namespace candy {

class Application : StateMachineGame {
public:
	Application();
	virtual ~Application();

	/**
	 * Comenzara con el bucle del juego
	 */
	void Run();

	/**
	 * Configura el juego desde el xml
	 * @param ruta ruta del xml
	 * @return si todo a sido correcto
	 */
	bool LoadFromXML(string ruta);

    InterfazPhysics *getFisica() const;
    InterfazGraphics *getGrafico() const;
    InterfazPathfinding *getPathfinder() const;
    CandyNapper *getCandyNapper() const;
    MusicEngine mEngine;

    string getConfigFile() const;

    void setConfigFile(string configFile);

    void setCandyNapper(CandyNapper* cd);

    void createRandomMap();

    void saveCandyNapper();

private:

	InterfazPathfinding *pf;

    /**
	 * Variable para motor fisica
	 */
    InterfazPhysics *m_fisica;

    /**
     * Puntero a la interfaz grafica
     */
    InterfazGraphics *m_grafico;

    /**
     * Puntero al parser
     */
    //ParserCandy *_parser;

    /**
     * Ruta al fichero de configuracion
     */
    string _configFile;

    /**
     * Clase que guarda el estado del juego
     */
   // CandyNapper* _candynapper;
};

} /* namespace candy */
#endif /* APPLICATION_H_ */
