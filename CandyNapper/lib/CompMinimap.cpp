/*
 * CompMinimap.cpp
 *
 *  Created on: 16/02/2012
 *      Author: kaseyo
 */

#include "CompMinimap.h"

#include "HUD.h"
#include "GEStatic.h"

#include "Objetos.h"

namespace candy {

CompMinimap::CompMinimap(GameEntity* entidad) {

	c_transformacion = InterfazGraphics::getInstance()->getHUD()->getMinimap()->addTransformation();
	Transformation* transf_escalado = c_transformacion->addTransformation();

	c_transformacion->setTranslation(scene2minimap(entidad->getPosicion()));

	GEDynamic* ent_din = NULL;

	switch(entidad->getTipo()){
		case GameEntity::Player:
			transf_escalado->Scale(1, 0.5);
			ent_din = (GEDynamic*)entidad;
			//Le sumamos el ajuste para tomar como referencia cuando el triangulo sale "hacia arriba"
			c_transformacion->setRotation(2, ent_din->getVisionX() + CandyMath::grad2rad(-90));
			c_polygon = transf_escalado->addShape(3, Color(0.0, 0.0, 1.0, 1.0));
		break;

		case GameEntity::Enemigo:
			transf_escalado->Scale(1, 0.5);
			ent_din = (GEDynamic*)entidad;
			//Le sumamos el ajuste para tomar como referencia cuando el triangulo sale "hacia arriba"
			c_transformacion->setRotation(2, ent_din->getVisionX() + CandyMath::grad2rad(-90));
			c_polygon = transf_escalado->addShape(3, Color(1.0, 0.0, 0.0, 1.0));
		break;

		case GameEntity::Estatica:
			if(((GEStatic*)entidad)->getTipoStatic()== GEStatic::Obstaculo){
				transf_escalado->Scale(0.5, 0.5);
				c_polygon = transf_escalado->addShape(4, Color(0.0, 1.0, 0.0, 1.0));
			}else{
				transf_escalado->Scale(0.5, 0.5);
				if(((Objetos*)entidad)->getTipoObjeto() == Objetos::Portal){
					c_polygon = transf_escalado->addShape(4, Color::Orange);
				}else{
					c_polygon = transf_escalado->addShape(4, Color::Yellow);
				}
			}
		break;

		default:
			c_polygon = c_transformacion->addShape(6, Color(0.8, 0.8, 0.8, 1.0));
		break;
	}
}

CompMinimap::~CompMinimap() {
	c_transformacion->setDestroy(true);
}

void
CompMinimap::Update(GameEntity* entidad){
	if(entidad->getTipo() != GameEntity::Estatica){
		//Si es algo que se mueva
		GEDynamic* ent_din = (GEDynamic*)entidad;
		if(ent_din->isModificado()){
			Vector2 nueva_pos = scene2minimap(ent_din->getPosicion());
			c_transformacion->setTranslation(nueva_pos);
			//Le sumamos el ajuste para tomar como referencia cuando el triangulo sale "hacia arriba"
			c_transformacion->setRotation(2, ent_din->getVisionX() + CandyMath::grad2rad(-90) + ent_din->getAnguloMovimiento());
		}
	}
}

Vector2
CompMinimap::scene2minimap(Vector3 pos_3d){
	Vector2 pos_minimapa;

	float ancho_minimapa = 140.0;
	float alto_minimapa = 105.0;

	float profundidad_escenario = 200;
	float ancho_escenario = 200;

	float coeficiente_ancho = ancho_minimapa / ancho_escenario;
	float coeficiente_alto = alto_minimapa / profundidad_escenario;

	pos_minimapa.setX(pos_3d.getX() * coeficiente_ancho);

	//En el HUD las Y son positivas parriba
	pos_minimapa.setY(-pos_3d.getZ() * coeficiente_alto);

	return pos_minimapa;
}

} /* namespace candy */
