/*
 * GraphicComponent.cpp
 *
 *  Created on: 15/02/2012
 *      Author: kaseyo
 */

#include "CompGraphic.h"
#include "GEDynamic.h"
#include "InterfazGraphics.h"
#include "World3D.h"
#include "Enemy.h"
#include "Obstaculo.h"
#include "GEStatic.h"
#include "Objetos.h"
#include <cstdlib>

namespace candy {

CompGraphic::CompGraphic(GameEntity* entidad) {
	AnimatedTransformation* atrans =  InterfazGraphics::getInstance()->getWorld3D()->getScene3D()->addAnimatedTransformation();
	c_transformacion =  atrans;

	int texvalue = rand() % 4 + 17;

	vector<int> modelos;
	vector<int> modelosAtaque;
	_ultimoAtaque = 0;

	if(entidad->getTipo() == GameEntity::Enemigo){

		Enemy* enemigo = (Enemy*)entidad;

		if(enemigo->getTipoEnemigo() == Enemy::Oso)
		{
			for(int i = InterfazGraphics::M_OsoMovimiento1; i<=InterfazGraphics::M_OsoMovimiento5;i++){
				modelos.push_back(i);
			}
			for(int i = InterfazGraphics::M_OsoAtaque1; i<=InterfazGraphics::M_OsoAtaque8;i++){
				modelosAtaque.push_back(i);
			}
			_modelDefault = InterfazGraphics::M_Oso;
			_texturaModel = texvalue;
		}else if(enemigo->getTipoEnemigo() == Enemy::Gengibre){
			for(int i = InterfazGraphics::M_GengibreMovimiento1; i<=InterfazGraphics::M_GengibreMovimiento5;i++){
				modelos.push_back(i);
			}
			for(int i = InterfazGraphics::M_GengibreAtaque1; i<=InterfazGraphics::M_GengibreAtaque8;i++){
				modelosAtaque.push_back(i);
			}
			_modelDefault = InterfazGraphics::M_Gengibre;
			_texturaModel = InterfazGraphics::T_Gengibre;
		}else if(enemigo->getTipoEnemigo() == Enemy::Melon){
			for(int i = InterfazGraphics::M_Melon; i<=InterfazGraphics::M_Melon;i++){
				modelos.push_back(i);
			}
			_modelDefault = InterfazGraphics::M_Melon;
			_texturaModel = InterfazGraphics::T_Melon;
		}

		_animacion.addModels(modelos);
		_animacionAtaque.addModels(modelosAtaque);
		modelos.clear();
		modelosAtaque.clear();


	}else if(entidad->getTipo() == GameEntity::Estatica){

		if(((GEStatic*)entidad)->getTipoStatic() == GEStatic::Obstaculo){
			Obstaculo* obstaculo = (Obstaculo*)entidad;

			switch (obstaculo->getTipoObstaculo()) {
				case Obstaculo::Algodon:
					c_modelo = c_transformacion->addModel(InterfazGraphics::M_Algodon, InterfazGraphics::T_Algodon);
					break;
				case Obstaculo::Chupachups:
					c_modelo = c_transformacion->addModel(InterfazGraphics::M_Chupachups, InterfazGraphics::T_Chupachups);
					break;
				case Obstaculo::Tarta:
					c_modelo = c_transformacion->addModel(InterfazGraphics::M_Tarta, InterfazGraphics::T_Tarta);
					break;
				default:
					break;
			}
		}else if(((GEStatic*)entidad)->getTipoStatic() == GEStatic::Objeto){
			Objetos* objec = (Objetos*)entidad;

			if(objec->getTipoObjeto() == Objetos::Jeringilla)
			{
				atrans->setAmpliacion(2000,0.5,1.5);
				atrans->setRotacionTotal(1500,1);
				c_modelo = c_transformacion->addModel(InterfazGraphics::M_Jeringuilla, InterfazGraphics::T_Jeringuilla);
			}
			else if(objec->getTipoObjeto() == Objetos::Botiquin_Pequeno)
			{
				c_modelo = c_transformacion->addModel(InterfazGraphics::M_BotiquinPe, InterfazGraphics::T_Botiquin);
			}
			else if(objec->getTipoObjeto() == Objetos::Botiquin_Mediano)
			{
				c_modelo = c_transformacion->addModel(InterfazGraphics::M_BotiquinMe, InterfazGraphics::T_Botiquin);
			}
			else if(objec->getTipoObjeto() == Objetos::Botiquin_Grande)
			{
				c_modelo = c_transformacion->addModel(InterfazGraphics::M_BotiquinGr, InterfazGraphics::T_Botiquin);
			}
			else if(objec->getTipoObjeto() == Objetos::Miel){
				c_modelo = c_transformacion->addModel(InterfazGraphics::M_Miel, InterfazGraphics::T_Miel);
			}
			else if(objec->getTipoObjeto() == Objetos::Portal){
				c_modelo = c_transformacion->addModel(InterfazGraphics::M_Portal, InterfazGraphics::T_Portal);

				Transformation* aux = c_transformacion->addTransformation();
				aux->Rotate(0,-M_PI/2.0);
				Transformation* aux1 = aux->addTransformation();
				Transformation* aux2 = aux->addTransformation();
				Transformation* aux3 = aux->addTransformation();
				Transformation* aux4 = aux->addTransformation();


				aux1->addParticles(2000);
			}

		}

	}

	c_modelo = c_transformacion->addModel(_modelDefault, _texturaModel);
	c_modelo->setID(entidad->getID());

	_animacion.setModel(c_modelo);
	_animacionAtaque.setModel(c_modelo);

	//Setteamos la posicion o lo que haya que hacer
	if(entidad->getTipo() == GameEntity::Enemigo){
		GEDynamic* ent_din = (GEDynamic*)entidad;
		actualizar(ent_din);
	}else if(entidad->getTipo() == GameEntity::Estatica){
		c_transformacion->setTranslation(entidad->getPosicion());
	}
}

CompGraphic::~CompGraphic() {
	//No destruimos nada, por que es el arbol el que se carga cosas
	//Pero marcamos a lo que esta "por encima" para que lo destruya, es decir, a la transformacion
	c_transformacion->setDestroy(true);
}

void
CompGraphic::Update(GameEntity* entidad){
	if(entidad->getTipo() != GameEntity::Estatica){
		//Es una entidad dinamica, debemos actualizar su posicion
		GEDynamic* entidad_din = (GEDynamic*)entidad;

		if(entidad_din->isModificado()){
			actualizar(entidad_din);
		}
	}
}

void
CompGraphic::actualizar(GEDynamic* entidad_din){
	//Controla Animacion
	if(entidad_din->getVelocidad() > 0){
		_animacion.Continue();
	}
	else if(entidad_din->getAttack()->isAttacking()){
		_atacando = true;
	}
	else{
		_animacion.Start();
		c_modelo->setIdModel(_modelDefault);
	}


	if(_atacando){
		_animacionAtaque.Continue(500);
		if(Timer::getTimeElapsed() - _ultimoAtaque > 500){
			_ultimoAtaque = Timer::getTimeElapsed();
			_atacando = false;
			_animacionAtaque.Start();
		}

	}
	/*
	float vidaActual = entidad_din->getVidaRestante();
	float vidaTotal = entidad_din->getVidaTotal();
	//Controla Textura
	int pos = vidaTotal/_texturas.size();
	pos = (vidaActual/pos);
	if(pos != _texturas.size())
		pos++;
	_textureUse = _texturas[_texturas.size()-pos];
*/

	c_transformacion->setRotation(1, entidad_din->getVisionX()+M_PI);
	c_transformacion->setTranslation(entidad_din->getPosicion());
}

} /* namespace candy */
