/*
 * HealthComponent.cpp
 *
 *  Created on: 01/03/2012
 *      Author: kaseyo
 */

#include "CompHealth.h"

#include "GEDynamic.h"
#include "HUD.h"
#include "InterfazGraphics.h"

#include <sstream>
using namespace std;

namespace candy {

CompHealth::CompHealth(GameEntity* entidad) {
	if(entidad->getTipo() == GameEntity::Player){
		_tTexto = InterfazGraphics::getInstance()->getHUD()->getBox1()->addTransformation();
		_tTexto->Translate(-60, 0, 0);
		_textoVidaRestante = _tTexto->addText();
		_textoVidaRestante->setColor(Color(1.0, 0.0, 0.0));
		_textoVidaRestante->setTamanyo(15);
	}
}

CompHealth::~CompHealth() {
	_tTexto->setDestroy(true);
}

void
CompHealth::Update(GameEntity* entidad){
	if(entidad->getTipo() == GameEntity::Player){
		GEDynamic* ent_din = (GEDynamic*)entidad;
		ostringstream formsal;

		formsal << ent_din->getVidaRestante() << " / " << ent_din->getVidaTotal();
		_textoVidaRestante->setTexto(formsal.str());
	}
}

} /* namespace candy */
