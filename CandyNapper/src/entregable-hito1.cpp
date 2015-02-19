#include <iostream>
#include <cstdlib>
using namespace std;

#include "CandyNapper.h"
#include "EntityManager.h"
#include "ParserXML.h"
using namespace candy;


const string CANDYNAPPER = "CandyNapper v0.1 - Entregable hito 1";
const string OPCIONES = "\t1) Cargar XML\n\t2)Situar entidades\n\t3)Jugar\n\t4)Salir";
const string ASK = "Opcion: ";
const string ASKXML = "Fichero XML: ";
const string ERRXML = "No existe el fichero";
const string ASKSEGUIR = "¿Quieres introducir otra entidad? (S/N): ";
const string ASKPLAYER_X = "Elige la coordenada X del player: ";
const string ASKPLAYER_Y = "Elige la coordenada Y del player: ";
const string ASKTIPO = "Elige el tipo de entidad\n\t1 - Enemigo\n\t2 - Obstaculo";
const string ASK_X = "Elige la coordenada X de la entidad: ";
const string ASK_Y = "Elige la coordenada Y de la entidad: ";
const string ASK_MAP_X = "Anchura del Mapa (Se recomienda no mas de 30) : ";
const string ASK_MAP_Y = "Altura del Mapa (Se recomienda no mas de 30)  : ";
const string ERR_MAP = "Error, debe ser mayor que 0";

/*
 * Lee un numero, como si fuera un string (devolviendo float)
 */
float
readNumber(){
	float answer;
	string cadena;

	getline(cin, cadena);

	answer = atof(cadena.c_str());

	return answer;
}

/*
 * Muestra el menu principal
 */
int
showMenu(){
	int option;

	do{
		cout << CANDYNAPPER << endl;
		cout << OPCIONES << endl;

		cout << ASK;

		option = readNumber();
	}while(option < 1 || option > 4);

	return option;
}

/*
 * Carga un XML preguntando al usuario el nombre del fichero
 */
CandyNapper*
cargarXML(){
	CandyNapper* juego = new CandyNapper;
	//EntityManager* em;
	ParserXML parser;
	string fic;

	cout << ASKXML;
	getline(cin, fic);

	if(parser.cargarFichero(fic)){
		parser.inicializarCandyNapper(juego);
	}else{
		cout << ERRXML << endl;
	}

	return juego;
}

/*
 * Pregunta al usuario si quiere continuar introduciendo entidades
 */
bool
askContinuar(){
	bool salir = true;
	char respuesta;

	do{
		cout << ASKSEGUIR;
		cin.get(respuesta);
		cin.ignore();
		if(respuesta == 'S'){
			salir = false;
		}else if(respuesta == 'N'){
			salir = true;
		}
	}while(respuesta != 'S' && respuesta != 'N');

	return salir;
}

/*
 * Pide el tipo de entidad
 */
GameEntity::TipoEntidad
askTipo(){
	GameEntity::TipoEntidad tipo;
	int opcion;

	do{
		cout << ASKTIPO << endl;
		cout << ASK;

		opcion = readNumber();

		if(opcion == 1){
			tipo = GameEntity::Enemigo;
		}else if(opcion == 2){
			tipo = GameEntity::Estatica;
		}
	}while(opcion != 1 && opcion != 2);


	return tipo;
}

/*
 * Permite al usuario elegir una serie de entidades.
 * Es obligatorio introducir el player.
 */
CandyNapper*
elegirEntidades(){
	CandyNapper* juego = new CandyNapper;

	int ancho=0;
	do{
		cout << ASK_MAP_X;
		ancho = readNumber();
		if(ancho <0)
		{
			cout << ERR_MAP << endl;
		}
	}while(ancho <0);

	int alto=0;
	do{
		cout << ASK_MAP_X;
		alto = readNumber();
		if(ancho <0)
		{
			cout << ERR_MAP << endl;
		}
	}while(ancho <0);
	juego->setMapa(ancho,alto,"");

	EntityManager* em = NULL;
	bool salir = false;
	int id_enem = 0, id_obst = 0;
	GameEntity::TipoEntidad tipo;
	int x;
	int y;

	GameEntity* entidad;

	cout << ASKPLAYER_X;
	x = readNumber();

	cout << ASKPLAYER_Y;
	y = readNumber();

	em = new EntityManager(x, y);

	salir = askContinuar();

	while(!salir){
		tipo = askTipo();

		cout << ASK_X;
		x = readNumber();

		cout << ASK_Y;
		y = readNumber();

		switch(tipo){
			case GameEntity::Enemigo:
				entidad = new GEDynamic(tipo, id_enem, x, y);
				id_enem++;
			break;

			case GameEntity::Estatica:
				entidad = new GEStatic(tipo, id_obst, x, y);
				id_obst++;
			break;

			default:
				//Aqui no deberia de entrar por que controlamos el tipo en askTipo()
			break;
		}

		em->addEntity(entidad);

		salir = askContinuar();
	}

	juego->setEm(em);
	//Hace falta settear el mapa?

	return juego;
}

int main(){
	CandyNapper* juego = NULL;

	//EntityManager* em = NULL;
	int opcion;

	do{
		opcion = showMenu();

		switch(opcion){
			case 1:
				if(juego != NULL){
					delete juego;
					juego = NULL;
				}
				juego = cargarXML();
			break;

			case 2:
				if(juego != NULL){
					delete juego;
					juego = NULL;
				}

				juego = elegirEntidades();
			break;

			case 3:
				if(juego!=NULL){
					juego->Run();
					delete juego;
					juego = NULL;
				}else{
					cout << "No has inicializado el juego. Para ello, selecciona la opcion 1 o 2"  << endl;
				}
			break;
		}
	}while(opcion != 4);

	if(juego != NULL){
		delete juego;
		juego = NULL;
	}

	return 0;
}

