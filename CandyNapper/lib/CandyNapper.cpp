/*
 * GSManager.cpp
 *
 *  Created on: 22/11/2011
 *      Author: kaseyo
 */

#include "StateMachineGame.h"
#include "CandyNapper.h"
#include "Timer.h"
#include <sstream>
using namespace candy;

CandyNapper* CandyNapper::instancia = NULL;

CandyNapper*
CandyNapper::getInstancia()
{
	if(instancia == NULL)
	{
		instancia = new CandyNapper();
	}
	return instancia;
}

bool candy::CandyNapper::ChangeLevel()
{
	return changeLevel;
}

void candy::CandyNapper::setChangeLevel(bool cl)
{
	changeLevel = cl;
}

string candy::CandyNapper::getNextLevel()
{
	return nextLevel;
}

void candy::CandyNapper::setNextLevel(string lv)
{
	nextLevel = lv;
}

bool candy::CandyNapper::isGameComplete()
{
	return gameComplete;
}

void candy::CandyNapper::setGameComplete(bool gc)
{
	gameComplete = gc;
}

string CandyNapper::getActualLevel(){
	return _actLevel;
}

void CandyNapper::setActualLevel(string level){
	_actLevel = level;
}

CandyNapper::CandyNapper() {
	em = new EntityManager();
	nextLevel = "";
	changeLevel = false;
	gameComplete = false;
}

CandyNapper::~CandyNapper() {
	if(em != NULL){
		delete em;
	}
}

EntityManager *CandyNapper::getEm() const
{
    return em;
}

void
CandyNapper::Init()
{
	nextLevel = "";
	changeLevel = false;
	gameComplete = false;
	em->Init();
}

string
CandyNapper::Serializar() const
{

	stringstream resultado;
	resultado << "<CandyNapper> \n";

	if(em->getPlayer()!= NULL)
	{
		resultado << "<Player x=\"" << em->getPlayer()->getPosicion().getX() << "\" y=\"" << em->getPlayer()->getPosicion().getZ() << "\"></Player> \n";
		resultado << "\t<Enemies> \n";
	}

	{
		list<GEDynamic*> listaEnemis = em->getDynamics();
		list<GEDynamic*>::iterator itDin;
		for(itDin = listaEnemis.begin(); itDin != listaEnemis.end(); itDin++)
		{
			if((*itDin)->getTipo() == GEDynamic::Enemigo)
			{
				Enemy* ene = (Enemy*)(*itDin);
				resultado << "\t\t<Enemy x=\"" << ene->getPosicion().getX() << "\" y=\"" << ene->getPosicion().getZ() << "\" type=\"" << ene->getTipoEnemigo() << "\" ></Enemy>\n";
			}
		}
	}

	resultado << "\t</Enemies> \n";
	resultado << "\t<Obstacles> \n";

	{
		list<GEStatic*> listaStatic = em->getStatics();
		list<GEStatic*>::iterator itStatic;

		for(itStatic = listaStatic.begin(); itStatic != listaStatic.end(); itStatic++)
		{
			if((*itStatic)->getTipoStatic() == GEStatic::Obstaculo)
			{
				Obstaculo* obs = (Obstaculo*)(*itStatic);
				resultado << "\t\t<Obstacle x=\"" << obs->getPosicion().getX() << "\" y=\"" << obs->getPosicion().getZ() << "\" type=\"" << obs->getTipoObstaculo() << "\" ></Obstacle>\n";
			}
		}
	}

	resultado << "\t</Obstacles> \n";
	resultado << "\t<Objects>\n";

	{
		list<GEStatic*> listaStatic = em->getStatics();
		list<GEStatic*>::iterator itStatic;

		for(itStatic = listaStatic.begin(); itStatic != listaStatic.end(); itStatic++)
		{
			if((*itStatic)->getTipoStatic() == GEStatic::Objeto)
			{
				Objetos* obs = (Objetos*)(*itStatic);
				if(obs->getTipoObjeto() == Objetos::Portal)
				{
					resultado << "\t\t<Object x=\"" << obs->getPosicion().getX() << "\" y=\"" << obs->getPosicion().getZ() << "\" type=\"" << obs->getTipoObjeto() << "\" nextLevel=\""<< obs->getNextLevel() << "\"  killAll=\""<< obs->getMatarTodos()  << "\"  ></Object>\n";
				}
				else
				{
					resultado << "\t\t<Object x=\"" << obs->getPosicion().getX() << "\" y=\"" << obs->getPosicion().getZ() << "\" type=\"" << obs->getTipoObjeto() << "\" ></Object>\n";
				}
			}
		}
	}

	resultado << "\t</Objects>\n";
	resultado << "</CandyNapper>\n";
	return resultado.str();
}


