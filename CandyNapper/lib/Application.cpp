/*
 * Application.cpp
 *
 *  Created on: 03/05/2012
 *      Author: carrillo
 */

#include "Application.h"

#include "Timer.h"
using namespace candy;

Application::Application()
{
	m_fisica = InterfazPhysics::getInstance();

	m_grafico = InterfazGraphics::getInstance();

	pf = InterfazPathfinding::getInstance();

//	_candynapper = CandyNapper::getInstancia();

	_configFile = "";
//	_parser = new ParserCandy(CandyNapper::getInstancia());

	//StateMachineGame::StateMachineGame();
}

void
Application::createRandomMap()
{
	EntityManager* em = CandyNapper::getInstancia()->getEm();
	srand(time(0));
	em->addPlayer(candy::Vector3(0, 0, 0));
	//int numObstaculos = 0;
	for(int i =0; i<10;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		em->addObstacle(candy::Vector3(x,0,y),Obstaculo::Tarta);
		//numObstaculos++;
	}

	for(int i =0; i<10;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		em->addObstacle(candy::Vector3(x,0,y),Obstaculo::Chupachups);
		//numObstaculos++;
	}

	for(int i =0; i<10;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		em->addObstacle(candy::Vector3(x,0,y),Obstaculo::Algodon);
		//numObstaculos++;
	}
	for(int i =0; i<10;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		em->addObjeto(candy::Vector3(x,0,y),Objetos::Miel);
		//numObstaculos++;
	}


	for(int i =0; i<15;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		em->addEnemy(candy::Vector3(x,0,y),Enemy::Oso);
		//numObstaculos++;
	}

	for(int i =0; i<5;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		em->addEnemy(candy::Vector3(x,0,y),Enemy::Gengibre);
		//numObstaculos++;
	}


	for(int i =0; i<5;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		em->addObjeto(candy::Vector3(x,0,y),Objetos::Jeringilla);
		//numObstaculos++;
	}

	for(int i =0; i<15;i++){
		int y = rand()%400-200;
		int x = rand()%400-200;
		em->addObjeto(candy::Vector3(x,0,y),Objetos::Botiquin_Pequeno);
		//numObstaculos++;
	}
	//cout << "[Aplication.cpp] Numero de obstaculos: " << numObstaculos << endl;
}

Application::~Application() {

	if(m_fisica != NULL){
		delete m_fisica;
	}

	if(m_grafico != NULL){
		delete m_grafico;
	}

	m_grafico = NULL;

}

void candy::Application::Run()
{

	while(!getSalir()){
		Update();
	}
}

string Application::getConfigFile() const{
	return _configFile;
}

void Application::setConfigFile(string configFile){
	_configFile = configFile;
}

InterfazPhysics *Application::getFisica() const
{
    return m_fisica;
}


InterfazGraphics *Application::getGrafico() const
{
    return m_grafico;
}

InterfazPathfinding* Application::getPathfinder() const{
	return pf;
}

bool candy::Application::LoadFromXML(string ruta)
{
	bool resultado;

	ParserCandy* _parser = new ParserCandy(CandyNapper::getInstancia());

	resultado = _parser->loadFile(ruta);

	if(resultado){
		_parser->configure();
		_parser->closeFile();
	}

	return resultado;
}

CandyNapper* Application::getCandyNapper() const{
	return  CandyNapper::getInstancia();
}

void Application::setCandyNapper(CandyNapper* cd){
	//_candynapper = cd;
}

void Application::saveCandyNapper()
{
	ofstream fsal;
	string ruta = (string)CANDYROOT + "/resources/saved.xml";
	cout << "[Application.cpp] Ruta: " << ruta << endl;
	fsal.open(ruta.c_str(),ios::out);
	if(fsal.is_open())
	{
		fsal << CandyNapper::getInstancia()->Serializar() << endl;
		fsal.close();
	}
}

