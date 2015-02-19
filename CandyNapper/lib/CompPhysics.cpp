/*
 * ObjectPhysics.cpp
 *
 *  Created on: Nov 15, 2011
 *      Author: carrillo
 */

#include "CompPhysics.h"
#include "GameEntity.h"
#include "GEDynamic.h"
#include "GEStatic.h"
#include "Obstaculo.h"

namespace candy {

CompPhysics::~CompPhysics() {
	InterfazPhysics::getInstance()->getMundo()->DestroyBody(cuerpo);
	cuerpo = NULL;
	delete forma;
	delete cuerpo_def;
}

b2Shape *CompPhysics::getShape() {
	return forma;
}

void CompPhysics::setCuerpo(b2Body *b) {
	cuerpo = b;
}

void CompPhysics::Update(GameEntity *entidad) {
	_entidad = entidad;
	if(_entidad->isDynamic()){
		GEDynamic* e = (GEDynamic*)_entidad;
		ajustarAngulo();
		ajustarVelocidad();
		Vector3 posicion;
		posicion.setX(cuerpo->GetPosition().x);
		posicion.setY(0.0);
		posicion.setZ(-cuerpo->GetPosition().y);
		//cout << "Posicion en compPhysics" << endl;
		//cout << posicion << endl;
		e->setPosicion(posicion);
	}
/*	if(_entidad->getTipo() == GameEntity::Enemigo){
		GEDynamic* e = (GEDynamic*)_entidad;
		e->setVelocidad(4);
	}*/
}

CompPhysics::CompPhysics(GameEntity *entidad) {
	Vector3 posicion = entidad->getPosicion();
	_entidad = entidad;

	if(entidad->getTipo() == GameEntity::Estatica){
		//Cambiara la forma segun el tamaño y forma del obstaculo
		b2PolygonShape* f;

		if(((GEStatic*)entidad)->getTipoStatic() == GEStatic::Obstaculo)
		{
			Obstaculo* obs = (Obstaculo*)entidad;
			if(obs->getTipoObstaculo() == Obstaculo::Chupachups || obs->getTipoObstaculo() == Obstaculo::Algodon)
			{
				f = new b2PolygonShape();
				f->SetAsBox(1, 1);
			}
			else if(obs->getTipoObstaculo() == Obstaculo::Tarta)
			{
				f = new b2PolygonShape();
				b2Vec2 *vert = new b2Vec2[3];
				vert[0] = b2Vec2(-1.7,1.0);
				vert[1] = b2Vec2(0.3,-4.3);
				vert[2] = b2Vec2(2.3,1.0);
				f->Set(vert,3);
			}
		}



		//Igual para todos los estaticos
		forma = f;
		cuerpo_def = new b2BodyDef();
		cuerpo_def->type = b2_staticBody;
		cuerpo_def->position.Set(posicion.getX(), -posicion.getZ()); //La Y es la Z
	} else if (entidad->isDynamic()) {
		//
		b2CircleShape* f = new b2CircleShape();


		f->m_radius = 1.0f; //TODO: mirar radio de las diferentes entidades dinamicas

		forma = f;
		//Igual para todos los dinamicos
		cuerpo_def = new b2BodyDef();
		cuerpo_def->type =  b2_dynamicBody;
		cuerpo_def->position.Set(posicion.getX(), -posicion.getZ());
	}


	cuerpo = InterfazPhysics::getInstance()->getMundo()->CreateBody(cuerpo_def);
	cuerpo->SetFixedRotation(true);
	cuerpo->CreateFixture(forma, 1.0f);
	cuerpo->SetUserData(entidad);

}

void CompPhysics::setCuerpoDef(b2BodyDef *bd) {
	cuerpo_def = bd;
}

void CompPhysics::setShape(b2Shape *s) {
	forma = s;
}

b2BodyDef *CompPhysics::getCuerpoDef() {
	return cuerpo_def;
}

b2Body *CompPhysics::getCuerpo() {
	return cuerpo;
}

void CompPhysics::ajustarVelocidad() {
	float velx, vely, angulo;

	if(_entidad->isDynamic()){
		GEDynamic* e = (GEDynamic*)_entidad;

		angulo = e->getVisionX() + e->getAnguloMovimiento() + M_PI/2.0;
		velx = cos(angulo) * e->getVelocidad();
		vely = sin(angulo) * e->getVelocidad();

		cuerpo->SetLinearVelocity(b2Vec2(velx, vely));
	}
}

void CompPhysics::ajustarAngulo() {
	if(_entidad->isDynamic()){
		GEDynamic* e = (GEDynamic*)_entidad;
		cuerpo->SetTransform(cuerpo->GetPosition(), e->getVisionX()+M_PI/2.0);
	}
}

} /* namespace Candy */
