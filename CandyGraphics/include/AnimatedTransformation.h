/*
 * AnimatedTransformation.h
 *
 *  Created on: 12/05/2012
 *      Author: carrillo
 */

#ifndef ANIMATEDTRANSFORMATION_H_
#define ANIMATEDTRANSFORMATION_H_

#include "Transformation.h"

namespace candy {

class AnimatedTransformation: public candy::Transformation {
public:
	AnimatedTransformation();
	virtual ~AnimatedTransformation();

	void setRotacionTotal(int milisegundos, int eje);

	void setAmpliacion(int milisegundos, float minAmpliacion, float maxAmpliacion);

	virtual void Render(bool seleccion);

	void ActualizarTranformacion();

private:
	///////////////////////////
	//Ejes  para rotacion    //
	//X: 0, Y: 1, Z:2//////////
	int _rotationEje;
	int _rotationAngle;
	bool _activateRotationMAXMIN;
	bool _activateRotation;
	float _incAngulo;
	float _anguloActual;
	long int _tiempoAnterior;
	bool _activadoMaxAngulo;
	bool _activadoMinAngulo;
	float _maxAngulo;
	float _minAngulo;
	int _tiempoRotation;

	/////////////////////////////
	//Variables para ampliacion//
	/////////////////////////////
	bool _activateAmpliation;
	float _incAmpliacion;
	float _maxAmpliacion;
	float _minAmpliacion;
	int _dirAmpliacion;
	int _tiempoAmpliacion;
	float _ampliacionActual;



	////////////////////////
};

} /* namespace candy */
#endif /* ANIMATEDTRANSFORMATION_H_ */
