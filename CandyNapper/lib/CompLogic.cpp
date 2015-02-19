/*
 * CompLogic.cpp
 *
 *  Created on: 12/05/2012
 *      Author: carrillo
 */

#include "CompLogic.h"
#include "CandyMath.h"
#include "Player.h"
#include "GEStatic.h"
#include "Objetos.h"
#include "CandyNapper.h"

namespace candy {

CompLogic::CompLogic() {
	// TODO Auto-generated constructor stub

}

CompLogic::~CompLogic() {
	// TODO Auto-generated destructor stub
}

void CompLogic::Update(GameEntity *entidad) {
	if(entidad->getTipo() == GameEntity::Estatica)
	{
		if(((GEStatic*)entidad)->getTipoStatic() == GEStatic::Objeto)
		{
			float distancia;
			Player* pl = CandyNapper::getInstancia()->getEm()->getPlayer();
			Vector3 posPlayer;

			if(pl == NULL){
				//Inicializamos a 1000000 todos para que nunca coincida y se ejecuten sin player
				posPlayer.setX(1000000.0);
				posPlayer.setY(1000000.0);
				posPlayer.setZ(1000000.0);
			}
			else{
				posPlayer= pl->getPosicion();

				Vector3 posObject = entidad->getPosicion();
				distancia = posPlayer.Distancia(posObject);
				if(distancia < 0)
					distancia = distancia*-1;

				Objetos* object = (Objetos*)entidad;
				if(object->getTipoObjeto() == Objetos::Jeringilla)
				{
					if(distancia <= 2.0f)
					{
						if(!pl->getModoATope())
						{
							pl->setModoATope(true);
							entidad->setDestroy();
						}
					}
				}else if(object->getTipoObjeto() == Objetos::Botiquin_Pequeno)
				{
					if(distancia <= 2.0f && pl->getVidaTotal()!=pl->getVidaRestante())
					{
						pl->setVidaRestante(25+pl->getVidaRestante());
						if(pl->getVidaRestante()>pl->getVidaTotal())
							pl->setVidaRestante(pl->getVidaTotal());
						entidad->setDestroy();
					}
				}else if(object->getTipoObjeto() == Objetos::Botiquin_Mediano)
				{
					if(distancia <= 2.0f && pl->getVidaTotal()!=pl->getVidaRestante())
					{
						pl->setVidaRestante(50+pl->getVidaRestante());
						if(pl->getVidaRestante()>pl->getVidaTotal())
							pl->setVidaRestante(pl->getVidaTotal());
						entidad->setDestroy();
					}
				}else if(object->getTipoObjeto() == Objetos::Botiquin_Grande)
				{
					if(distancia <= 2.0f && pl->getVidaTotal()!=pl->getVidaRestante())
					{
						pl->setVidaRestante(100+pl->getVidaRestante());
						if(pl->getVidaRestante()>pl->getVidaTotal())
							pl->setVidaRestante(pl->getVidaTotal());
						entidad->setDestroy();
					}
				}
				else if(object->getTipoObjeto() == Objetos::Miel)
				{
					if(distancia <= 3.0f)
					{
						pl->setModificadorVelocidad(0.3);
					}
				}
				else if(object->getTipoObjeto() == Objetos::Portal)
				{
					if(distancia <= 2.0f)
					{
						if(!object->getMatarTodos() || (object->getMatarTodos() && CandyNapper::getInstancia()->getEm()->getEnemys().empty())){
							if(object->getNextLevel() != ""){
								CandyNapper::getInstancia()->setChangeLevel(true);
								CandyNapper::getInstancia()->setNextLevel(object->getNextLevel());
							}else{
								CandyNapper::getInstancia()->setGameComplete(true);
							}
						}else{
							InterfazGraphics::getInstance()->visibilidadTextoCentral(true);
							InterfazGraphics::getInstance()->setTextoCentral1("Para poder entrar al portal tienes ");
							InterfazGraphics::getInstance()->setTextoCentral2("que eliminar a todos los enemigos  ");
						}

					}
				}
			}
		}
	}


	}

} /* namespace candy */
