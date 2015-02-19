/*
 * AnimatedModel.cpp
 *
 *  Created on: 17/03/2012
 *      Author: kaseyo
 */

#include "ModelAnimation.h"
#include "Timer.h"

namespace candy {

ModelAnimation::ModelAnimation(Model *m) {
	_modelo = m;
	_lastTime =0;
	_actualMovement =0;
}

ModelAnimation::ModelAnimation(Model *m, vector<int> ids) {
	_modelo = m;
	_modelos = ids;
	_lastTime =0;
	_actualMovement = _modelos.size();
}

ModelAnimation::~ModelAnimation() {
	// TODO Auto-generated destructor stub
}

void ModelAnimation::Start() {
	_actualMovement = _modelos.size();
}

void ModelAnimation::Continue(int duracion) {
	if(_modelos.size()>0 && _modelo != NULL)
	{
		if(Timer::getTimeElapsed()-_lastTime > duracion/_modelos.size()){
			_actualMovement++;
			_lastTime = Timer::getTimeElapsed();
		}

		if(_actualMovement >=_modelos.size()){
			_actualMovement=0;
		}

		_modelo->setIdModel(_modelos[_actualMovement]);
	}
}

void ModelAnimation::setModel(Model *m) {
	_modelo = m;
}


void ModelAnimation::addModels(vector<int> idsModels) {
	_modelos = idsModels;
	_actualMovement = idsModels.size();
	for(int i=0;i < _modelos.size(); i++){
	}
}

} /* namespace candy */
