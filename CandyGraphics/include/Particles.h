/*
 * Particles.h
 *
 *  Created on: 23/05/2012
 *      Author: carrillo
 */

#ifndef PARTICLES_H_
#define PARTICLES_H_

#include "GNode.h"
#include "OpenGL.h"

namespace candy {

typedef struct						// Create A Structure For Particle
{
	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// X Gravity
	float	yg;						// Y Gravity
	float	zg;						// Z Gravity
}
strucParticles;

class Particles : public candy::GNode {
public:
	Particles(int numParticulas = 500);
	virtual ~Particles();

	/**
	 * Renderiza, si el id del modelo no existe o es incorrecto
	 * no dibuja nada
	 */
	void Render(bool seleccion);

	void renderizarParticulas();

	//void setNumParticulas(int nParticulas);
	void iniciarParticulas();

	int getNumParticulas();
private:
	int numParticulas;
	strucParticles *particulas;
	float velX;
	float velY;
	float velZ;
	Color color;

};

} /* namespace candy */
#endif /* PARTICLES_H_ */
