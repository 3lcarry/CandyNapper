#include "Application.h"
#include "CandyNapper.h"
#include "CandyMath.h"
#include "CandyGraphics.h"
#include <iostream>
using namespace std;
using namespace candy;

float num_osos = 0;

void OchoPuntos(float x, float y, EntityManager* em){
	em->addEnemy(candy::Vector3(x, 0, y), Enemy::Oso);
	em->addEnemy(candy::Vector3(-x, 0, y), Enemy::Oso);
	em->addEnemy(candy::Vector3(-x, 0, -y), Enemy::Oso);
	em->addEnemy(candy::Vector3(x, 0, -y), Enemy::Oso);
	em->addEnemy(candy::Vector3(y, 0, x), Enemy::Oso);
	em->addEnemy(candy::Vector3(-y, 0, x), Enemy::Oso);
	em->addEnemy(candy::Vector3(-y, 0, -x), Enemy::Oso);
	em->addEnemy(candy::Vector3(y, 0, -x), Enemy::Oso);

	num_osos += 8;
}

void dibujarCirculo(int radio, EntityManager* em){
	int x,y;
	float d;

	x = 0;
	y = radio;
	d = 5/4-radio;
	float dE = 3; //Valor init
	float dSE = 5 - 2*radio;

	glColor3f(1, 0, 0);

	OchoPuntos(x, y, em);


	while(y > x){
		if(d < 0){
			//E
			dE += 2;
			dSE += 2;
			d += dE;
			//d += 2*x + 3;
			x++;
		}else{
			//SE
			dE += 2;
			dSE += 4;
			d += dSE;
			//d += 2*(x-y) + 5;
			x++;
			y--;
		}
		OchoPuntos(x, y, em);
	}
}


int main(){
	Application* cn = new Application();
	EntityManager* em = cn->getCandyNapper()->getEm();
	InterfazGraphics* ig = cn->getGrafico();
	InterfazPhysics* fisica = cn->getFisica();

	if(GL_ARB_fragment_shader && GL_ARB_vertex_shader){
		cout << "[pruebas-graficos.cpp] Shaders: OK" << endl;
	}else{
		cout << "[pruebas-graficos.cpp] Shaders: MAL" << endl;
	}

	//cn->createRandomMap();
	cn->Run();


	delete cn;
}
