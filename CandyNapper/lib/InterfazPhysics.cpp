/*
 * InterfazPhysics.cpp
 *
 *  Created on: Nov 15, 2011
 *      Author: carrillo
 */

#include "InterfazPhysics.h"
#include "InterfazGraphics.h"
#include <sstream>
using namespace std;

namespace candy {

InterfazPhysics* InterfazPhysics::_instancia = NULL;
b2World *InterfazPhysics::getMundo() {
	return _mundo;
}

bool InterfazPhysics::obstaculo(Vector3 inicio, Vector3 fin) {
	bool resultado = false;
	RayCastStaticCallback callback;
	b2Vec2 p1(inicio.getX(),-inicio.getZ());
	b2Vec2 p2(fin.getX(),-fin.getZ());

	/**cout << "Raycast.................................." << endl;
	cout << "Punto 1 " << p1.x << " , " << p1.y << endl;
	cout << "Punto 2 " << p2.x << " , " << p2.y << endl;
	**/

	if(p1.x != p2.x || p1.y != p2.y){
		_mundo->RayCast(&callback,p1,p2);

		if(callback.m_fixture != NULL && callback.m_fraction != -1){
			resultado = true;
		}
	}

	return resultado;
}

GameEntity* InterfazPhysics::RayTracing(Vector3 inicio, float distancia, float angulo) {
	//angulo = angulo+M_PI/2.0;
	RayCastCallback callback;
	b2Vec2 p1(inicio.getX(),-inicio.getZ());
	b2Vec2 p2 = p1 + distancia * b2Vec2( -sin(angulo), cos(angulo) );
	GameEntity* entidad = NULL;
	if(p1.x != p2.x || p1.y != p2.y){
		_mundo->RayCast(&callback,p1,p2);

		if(callback.m_fixture != NULL){
			entidad = ((GameEntity*)callback.m_fixture->GetBody()->GetUserData());
		}
	}
	return entidad;
}

InterfazPhysics::InterfazPhysics() {
	_mundo = new b2World(b2Vec2(0.0f, 0.0f));
	Init(400, 400);
}

InterfazPhysics::~InterfazPhysics() {
	delete _mundo;
}

void InterfazPhysics::Init(int ancho, int alto) {
	//Insertamos las "paredes"

	b2PolygonShape* fpared;
	b2BodyDef* bd;
	b2Body* cp;
	//Derecha
	fpared = new b2PolygonShape();
	bd = new b2BodyDef();
	fpared->SetAsBox(0.5, alto);
	bd->position.Set(ancho / 2.0, 0.0);
	bd->type = b2_staticBody;
	cp = _mundo->CreateBody(bd);
	cp->CreateFixture(fpared, 1.0f);
	//Izquierda
	fpared = new b2PolygonShape();
	bd = new b2BodyDef();
	fpared->SetAsBox(0.5, alto);
	bd->position.Set(-ancho / 2.0, 0.0);
	bd->type = b2_staticBody;
	cp = _mundo->CreateBody(bd);
	cp->CreateFixture(fpared, 1.0f);
	//Arriba
	fpared = new b2PolygonShape();
	bd = new b2BodyDef();
	fpared->SetAsBox(ancho, 0.5);
	bd->position.Set(0.5, alto / 2.0);
	bd->type = b2_staticBody;
	cp = _mundo->CreateBody(bd);
	cp->CreateFixture(fpared, 1.0f);
	//Abajo
	fpared = new b2PolygonShape();
	bd = new b2BodyDef();
	fpared->SetAsBox(ancho, 0.5);
	bd->position.Set(0.5, -alto / 2.0);
	bd->type = b2_staticBody;
	cp = _mundo->CreateBody(bd);
	cp->CreateFixture(fpared, 1.0f);

}

InterfazPhysics *InterfazPhysics::getInstance() {
	if (_instancia == NULL) {
		_instancia = new InterfazPhysics();
	}
	return _instancia;
}

void InterfazPhysics::Update(float timestep) {


	_mundo->Step(timestep, 8, 3);



}

} /* namespace Candy */
