#include "ParserGestorRecursos.h"
#include "GestorRecursos.h"


ParserGestorRecursos::ParserGestorRecursos(GestorRecursos* GR)
{
	gestor = GR;
	documento = NULL;
}


ParserGestorRecursos::~ParserGestorRecursos(void)
{
	if(documento != NULL){
		delete documento;
		documento = NULL;
		raiz = NULL;
		elemento = NULL;
	}
}


bool ParserGestorRecursos::loadFile(string ruta)
{
	bool resul = true;
	
	documento = new TiXmlDocument(ruta.c_str());
	if(documento->LoadFile()){
		TiXmlHandle manejadorAux(documento);
		elemento = manejadorAux.FirstChild("GestorRecursos").Element();
		if(elemento != NULL){
			raiz = new TiXmlHandle(elemento);
		}else{
			resul = false;
		}
	}else{
		resul = false;
	}

	return resul;
}


bool ParserGestorRecursos::configure(void)
{
	bool correcto = true;
	int id;

	//Configuramos los Modelos
	for(elemento = raiz->FirstChild("Modelos").FirstChild().Element(); elemento != NULL;elemento = elemento->NextSiblingElement()){
		if(elemento->Attribute("ruta") != NULL){
			if(elemento->Attribute("id") != NULL){
				elemento->QueryIntAttribute("id",&id);
				gestor->add3ds(id,elemento->Attribute("ruta"));
			}else{
				correcto = false;
			}
		}else{
			correcto = false;
		}
	}

	//Configuramos las texturas
	for(elemento = raiz->FirstChild("Texturas").FirstChild().Element(); elemento != NULL;elemento = elemento->NextSiblingElement()){
		if(elemento->Attribute("ruta") != NULL){
			if(elemento->Attribute("id") != NULL){
				elemento->QueryIntAttribute("id",&id);
				gestor->addTextura(id,elemento->Attribute("ruta"));
			}else{
				correcto = false;
			}
		}else{
			correcto = false;
		}
	}

	return correcto;
}


void ParserGestorRecursos::closeFile(void)
{
	if(documento != NULL){
		delete documento;
		documento = NULL;
		raiz = NULL;
		elemento = NULL;
	}
}
