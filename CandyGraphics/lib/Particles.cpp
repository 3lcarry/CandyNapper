/*
 * Particles.cpp
 *
 *  Created on: 23/05/2012
 *      Author: carrillo
 */

#include "Particles.h"

namespace candy {

Particles::Particles(int numParticulas)
:GNode(GNode::E_Particula)
{
	this->numParticulas = numParticulas;
	color = Color::Red;
	particulas = new strucParticles[numParticulas];
	iniciarParticulas();
	velY = 0.005f;
	velX = 0;
	velZ = 0;
}

Particles::~Particles() {
	if(particulas != NULL)
	{
		delete [] particulas;
	}
	particulas = NULL;
	numParticulas = 0;
}

void Particles::Render(bool seleccion)
{
	if(!seleccion)
	{
		glDisable(GL_LIGHTING);
		renderizarParticulas();
		glEnable(GL_LIGHTING);
	}

	RenderHijos(seleccion);
}


/*
void Particles::setNumParticulas(int nParticulas)
{
}
*/

void Particles::iniciarParticulas()
{
	for (int i=0;i<numParticulas;i++)				// Initials All The Textures
	{
		if(rand()%50>25)
		{
			color = Color::Orange;
		}else
		{
			color = Color::Cyan;
		}


		particulas[i].active=true;								// Make All The Particles Active
		particulas[i].life=1.0f;								// Give All The Particles Full Life
		particulas[i].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
		particulas[i].r= color.R();	// Select Red Rainbow Color
		particulas[i].g= color.G();	// Select Red Rainbow Color
		particulas[i].b= color.B();	// Select Red Rainbow Color
		particulas[i].xi=float((rand()%50)-26.0f)/10.f;		// Random Speed On X Axis
		particulas[i].yi=float((rand()%50)-25.0f)/10.f;		// Random Speed On Y Axis
		particulas[i].zi=float((rand()%50)-25.0f)/10.f;		// Random Speed On Z Axis
		particulas[i].xg=velX;									// Set Horizontal Pull To Zero
		particulas[i].yg=velY;								// Set Vertical Pull Downward
		particulas[i].zg=velZ;
		if(numParticulas > 600){
			particulas[i].x=((rand()%200)-100.0)/100.0f;
			particulas[i].y=((rand()%200)-100.0)/100.0f;
			particulas[i].z=((rand()%200)-100.0)/100.0f;
		}else{
			particulas[i].x=((rand()%200)-100.0)/400.0f;
			particulas[i].y=((rand()%200)-100.0)/400.0f;
			particulas[i].z=((rand()%200)-100.0)/400.0f;
		}
	}

}

void Particles::renderizarParticulas()
{
	if(rand()%50>25)
	{
		color = Color::Orange;
	}else
	{
		color = Color::Cyan;
	}

	for (int i=0;i<numParticulas;i++)					// Loop Through All The Particles
	{

		float x=particulas[i].x;						// Grab Our Particle X Position
		float y=particulas[i].y;						// Grab Our Particle Y Position
		float z=particulas[i].z;					// Particle Z Pos + Zoom

		// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
		glColor4f(particulas[i].r,particulas[i].g,particulas[i].b,particulas[i].life);

		glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
			glTexCoord2d(1,1); glVertex3f(x+0.01f,y+0.01f,z); // Top Right
			glTexCoord2d(0,1); glVertex3f(x-0.01f,y+0.01f,z); // Top Left
			glTexCoord2d(1,0); glVertex3f(x+0.01f,y-0.01f,z); // Bottom Right
			glTexCoord2d(0,0); glVertex3f(x-0.01f,y-0.01f,z); // Bottom Left
		glEnd();					// Done Building Triangle Strip


		particulas[i].x+=particulas[i].xi/(2.0*1000);// Move On The X Axis By X Speed
		particulas[i].y+=particulas[i].yi/(2.0*1000);// Move On The Y Axis By Y Speed
		particulas[i].z+=particulas[i].zi/(2.0*1000);// Move On The Z Axis By Z Speed

		particulas[i].x+=velX;(velY-0.5)/10.0f;  //particulas[i].xg;			// Take Pull On X Axis Into Account
		particulas[i].y+=velY;//particul1as[i].yg;			// Take Pull On Y Axis Into Account
		particulas[i].z+=-(velY-0.5)/10.0f;			// Take Pull On Z Axis Into Account
		particulas[i].life-=particulas[i].fade;		// Reduce Particles Life By 'Fade'

		if (particulas[i].life<0.0f)					// If Particle Is Burned Out
		{
			particulas[i].active=true;								// Make All The Particles Active
			particulas[i].life=1.0f;								// Give All The Particles Full Life
			particulas[i].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
			particulas[i].r= color.R();	// Select Red Rainbow Color
			particulas[i].g= color.G();	// Select Red Rainbow Color
			particulas[i].b= color.B();	// Select Red Rainbow Color
			particulas[i].xi=float((rand()%50)-26.0f)/10.f;		// Random Speed On X Axis
			particulas[i].yi=float((rand()%50)-25.0f)/10.f;		// Random Speed On Y Axis
			particulas[i].zi=float((rand()%50)-25.0f)/10.f;		// Random Speed On Z Axis
			particulas[i].xg=velX;									// Set Horizontal Pull To Zero
			particulas[i].yg=velY;								// Set Vertical Pull Downward
			particulas[i].zg=velZ;
			if(numParticulas > 600){
				particulas[i].x=((rand()%200)-100.0)/100.0f;
				particulas[i].y=((rand()%200)-100.0)/100.0f;
				particulas[i].z=((rand()%200)-100.0)/100.0f;
			}else{
				particulas[i].x=((rand()%200)-100.0)/400.0f;
				particulas[i].y=((rand()%200)-100.0)/400.0f;
				particulas[i].z=((rand()%200)-100.0)/400.0f;
			}
		}
    }
}

int Particles::getNumParticulas()
{
	return numParticulas;
}

} /* namespace candy */
