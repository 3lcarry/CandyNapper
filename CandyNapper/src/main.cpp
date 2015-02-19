/*
 * main.cpp
 *
 *  Created on: Nov 24, 2011
 *      Author: carrillo
 */

#include <iostream>
using namespace std;

#include "CandyNapper.h"
#include "ParserXML.h"
using namespace candy;

int main(){
	CandyNapper juego;

	ParserXML parser;
	if(	parser.cargarFichero("resources/configuracion.xml")){
		parser.inicializarCandyNapper(&juego);
		juego.Run();
	}else{
		cout << "Archivo de configuracion.xml no encontrado" << endl;
	}

	return 0;
}

