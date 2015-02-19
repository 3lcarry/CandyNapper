/*
 * AnimatedTransformation.cpp
 *
 *  Created on: 12/05/2012
 *      Author: carrillo
 */

#include "AnimatedTransformation.h"
#include "Timer.h"

namespace candy {

AnimatedTransformation::AnimatedTransformation() {
	_activateRotation = false;
	_activateRotationMAXMIN = false;
	_activateAmpliation = false;
	_tiempoAnterior = Timer::getTimeElapsed();
}

AnimatedTransformation::~AnimatedTransformation() {
	// TODO Auto-generated destructor stub
}

void AnimatedTransformation::setRotacionTotal(int milisegundos, int eje) {
	_activateRotation = true;
	_rotationEje = eje;
	_tiempoRotation = milisegundos;
}

void AnimatedTransformation::Render(bool seleccion) {
	if(!seleccion){
		ActualizarTranformacion();
	}

	Transformation::Render(seleccion);
}

void
AnimatedTransformation::setAmpliacion(int milisegundos, float minAmpliacion,float maxAmpliacion)
{
	_activateAmpliation = true;
	_tiempoAmpliacion = milisegundos;
	_minAmpliacion = minAmpliacion;
	_maxAmpliacion = maxAmpliacion;
	_dirAmpliacion = 1;
	_ampliacionActual = minAmpliacion;
}

void AnimatedTransformation::ActualizarTranformacion() {
	long int tIncrementado = Timer::getTimeElapsed() - _tiempoAnterior;
	if (_activateRotation) {
		_incAngulo = ((float)tIncrementado * 2 * M_PI) / ((float) (_tiempoRotation));
		Rotate(_rotationEje, _incAngulo);
	}


	if(_activateAmpliation)
	{
		_incAmpliacion = ((float)tIncrementado * (_maxAmpliacion-_minAmpliacion))/((float)_tiempoAmpliacion);
		_ampliacionActual += _incAmpliacion*_dirAmpliacion;

		if(_ampliacionActual >= _maxAmpliacion || _ampliacionActual <= _minAmpliacion)
		{
			_dirAmpliacion *= -1;
		}

		setScalation(_ampliacionActual,_ampliacionActual,_ampliacionActual);
	}

	_tiempoAnterior = Timer::getTimeElapsed();
}

} /* namespace candy */
