#pragma once
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;

class GestorRecursos;

class ParserGestorRecursos
{
public:
	ParserGestorRecursos(GestorRecursos* GR);
	~ParserGestorRecursos(void);
	bool loadFile(string ruta);
	bool configure(void);

private:
	TiXmlDocument* documento;
	TiXmlHandle* raiz;
	TiXmlElement* elemento;
	GestorRecursos* gestor;

public:
	void closeFile(void);
};

