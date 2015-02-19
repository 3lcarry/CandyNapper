/*
 * Obstaculo.cpp
 *
 *  Created on: 10/05/2012
 *      Author: gustavo
 */

#include "Obstaculo.h"
#include "CompGraphic.h"
#include "CompPhysics.h"
#include "CompMinimap.h"

namespace candy{

Obstaculo::Obstaculo(TipoObstaculo tipo, Vector3 posicion)
	:GEStatic(GEStatic::Obstaculo, posicion){

		_tipoObstaculo = tipo;

		_convexHull = PolygonFactory::Cuadrado(Vector2(posicion.getX(), -posicion.getZ()), posicion.getX(), posicion.getZ());
		IComponent* gc = new CompGraphic(this);
		c_componentes.push_back(gc);
		IComponent* minimapc = new CompMinimap(this);
		c_componentes.push_back(minimapc);
		IComponent* fc = new CompPhysics(this);
		c_componentes.push_back(fc);
}

Obstaculo::~Obstaculo(){

}

Obstaculo::TipoObstaculo Obstaculo::getTipoObstaculo(){
	return _tipoObstaculo;
}

}

