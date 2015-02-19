/*
 * GameEntityStatic.cpp
 *
 *  Created on: Nov 8, 2011
 *      Author: carrillo
 */

#include "GEStatic.h"
#include "CandyMath.h"
#include "CompGraphic.h"
#include "CompPhysics.h"
#include "CompMinimap.h"
using namespace candy;

const float GEStatic::tamanyo = 1;

GEStatic::GEStatic(TipoStatic tipo, Vector3 posicion)
	:GameEntity(GameEntity::Estatica, 0, posicion) //En principio, no es importante el id de las estaticas
{
	_tipoStatic = tipo;

	_convexHull = PolygonFactory::Cuadrado(Vector2(posicion.getX(), -posicion.getZ()), tamanyo, tamanyo);
}

GEStatic::GEStatic(const GEStatic & cop):GameEntity(cop){
	copiarDesde(cop);
}

GEStatic & GEStatic::operator =(const GEStatic & cop){
	if(this !=  &cop){
		this->~GEStatic();
		copiarDesde(cop);
	}

	return *this;
}

GEStatic::~GEStatic() {

}

GEStatic::TipoStatic
candy::GEStatic::getTipoStatic()
{
	return _tipoStatic;
}

void GEStatic::copiarDesde(const GEStatic & cop){
	GameEntity::copiarDesde(cop);
}




