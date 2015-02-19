/*
 * ParserCandy.h
 *
 *  Created on: 16/03/2012
 *      Author: carrillo
 */

#ifndef PARSERCANDY_H_
#define PARSERCANDY_H_
#include <iostream>
using namespace std;

#include "tinyxml.h"
#include "tinystr.h"


namespace candy {

class CandyNapper;
/**
 * Clase para configurar candyNapper desde XML
 */
class ParserCandy {
public:
	/**
	 * Constructor del parser hay que indicarle la clase candyNapper
	 * @param c, juego que modificia
	 */
	ParserCandy(CandyNapper* c);
	/**
	 * Destructor
	 */
	virtual ~ParserCandy();
	/**
	 * Carga el fichero indicado
	 * @param ruta
	 * @return true si lo ha cargado bien
	 */
	bool loadFile(string ruta);
	/**
	 * Configura el juego pasado por el constructor
	 * @return si todo ha ido correctamente
	 */
	bool configure(void);
	/**
	 * Cierra el documento
	 */
	void closeFile(void);

private:
	TiXmlDocument* _documento;
	TiXmlHandle* _raiz;
	TiXmlElement* _elemento;
	CandyNapper* _candy;

};

} /* namespace candy */
#endif /* PARSERCANDY_H_ */
