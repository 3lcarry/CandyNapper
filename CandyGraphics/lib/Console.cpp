/*
 * Console.cpp
 *
 *  Created on: 08/02/2012
 *      Author: kaseyo
 */

#include "Console.h"

namespace candy {

Console::Console(){
	//Limpiamos lo que hay en el Buffer de cin y reseteamos su estado
	//clearInput();

	//Inicializamos comando y lineaCompleta
	c_comando = "";
	c_completo = false;
	c_activa = false;
	c_GNode = NULL;
	c_nodoTexto = NULL;
	c_nodoCaja = NULL;
}

Console::~Console() {

}

Console::Console(const Console & cop){
	copiarDesde(cop);
}

Console &
Console::operator =(const Console & cop){
	if(this != &cop){
		copiarDesde(cop);
	}

	return *this;
}

void
Console::copiarDesde(const Console & cop){

}

void
Console::ShowConsole(){
	if(c_GNode != NULL){
		c_GNode->setActive(true);
	}
	//Limpiamos la consola
	//clearConsole();

	//Mostramos nuestra mega-cabecera
	//cout << "================================================================" << endl;
	//cout << "===========================  CONSOLA  ==========================" << endl;
	//cout << "================================================================" << endl;

	//Mostramos el prompt
	prompt();

	//Limpiamos lo que hay en el Buffer de cin y reseteamos su estado
	//clearInput();

	//Inicializamos comando y lineaCompleta
	c_comando = "";
	c_completo = false;
	c_activa = true;
}

bool Console::IsActive(){
	return c_activa;
}

void
Console::CommandCompleted(){
	c_completo = true;
	//cout << "=== COMANDO INTRODUCIDO ===" << endl;
	prompt();
}

void Console::clearInput(){
	//cin.ignore(std::numeric_limits<std::streamsize>::max());
	//cin.clear();
}

void Console::clearConsole(){

#ifdef WINDOWS

	std::system ( "CLS" );

#else

	// Assume POSIX

	std::system ( "clear" );

#endif
}

void
Console::HideConsole(){
	if(c_GNode != NULL){
		c_GNode->setActive(false);
	}
	//cout << "===========================   ADIOS  ===========================" << endl;
	c_activa = false;
}

void
Console::prompt(){
	if(c_GNode != NULL){
		c_nodoTexto->setTexto("> ");
	}
	//cout << "=== INTRODUZCA NUEVO COMANDO ===" << endl;
}

void
Console::AddChar(char caracter){
	if(c_completo){
		c_completo = false;
		c_comando = "";
	}
        
	c_comando += caracter;

	if(c_GNode != NULL){
		c_nodoTexto->setTexto("> " + c_comando);
	}

	//cout << c_comando << endl;
}

void
Console::RmChar(){
	if (c_comando.size () > 0){
		c_comando.resize (c_comando.size () - 1);
	}

	if(c_GNode != NULL){
		c_nodoTexto->setTexto("> " + c_comando);
	}

	//cout << c_comando << endl;
}

bool
Console::IsComplete(){
	return c_completo;
}

string
Console::GetCommand(){
	string resultado = c_comando;

	if(c_completo){
		c_completo = false;
		c_comando = "";
	}

	return resultado;
}

vector<string>
Console::GetCommandSplitted(){
	//Esto habra que meterlo en una funcion "split" de una futura libreria candy-utilities o algo asi..., al menos
	//si lo usamos en algun sitio mas
	vector<string> troceado;
	string comando = GetCommand();
	string trozo = "";

	for(unsigned i = 0; i <= comando.size(); i++){
		if(i == comando.size() || comando[i] == ' '){
			troceado.push_back(trozo);
			trozo = "";
		}else{
			trozo += comando[i];
		}
	}

	return troceado;
}

void
Console::setGNode(GNode* nodo){
	c_GNode = nodo;
	if(c_GNode != NULL){
		c_GNode->setActive(false);

		Transformation* trans_caja = c_GNode->addTransformation();
		trans_caja->Translate(400, 300, 0);
		trans_caja->Scale(40, 30, 1);
		c_nodoCaja = trans_caja->addShape(4, Color(0.6, 0.6, 0.6, 0.4));

		Transformation* trans_texto = c_GNode->addTransformation();
		trans_texto->Translate(150, 450, 0);
		c_nodoTexto = trans_texto->addText();
		c_nodoTexto->setColor(Color(1.0, 0.0, 0.0, 1.0));
		c_nodoTexto->setTamanyo(20);
		c_nodoTexto->setFont(GestorRecursos::E_Anarchy);
		c_nodoTexto->setTexto("> ");
	}
}

} /* namespace candy */
