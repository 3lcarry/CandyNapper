#include <iostream>
#include <cstdlib>
using namespace std;

#define _DEBUG_

#include "CandyGraphics.h"
using namespace candy;

#define GRANERO 1
#define METAL 2
#define MADERA 3

Vector2
scene2minimap(Vector3 pos_3d){
	Vector2 pos_minimapa;

	float ancho_minimapa = 140.0;
	float alto_minimapa = 105.0;

	float profundidad_escenario = 500;
	float ancho_escenario = 100;

	float coeficiente_ancho = ancho_minimapa / ancho_escenario;
	float coeficiente_alto = alto_minimapa / profundidad_escenario;

	pos_minimapa.setX(pos_3d.getX() * coeficiente_ancho);

	//En el HUD las Y son positivas parriba
	pos_minimapa.setY(-pos_3d.getZ() * coeficiente_alto);

	return pos_minimapa;
}

void
initOpenGL(){
	// Set color and depth clear value
    // Borra FrameBuffer y Z-Buffer
    glClearIndex((GLfloat) 0);
	glClearDepth(1000.0);

	glEnable(GL_DEPTH_TEST);

	glPointSize(100);

	glDepthMask(GL_TRUE);
}

int main(int argc, char **argv) {
	string titulo = "Prueba Render";
	Ventana v(800, 600, titulo);

	GestorRecursos* g = GestorRecursos::getInstancia();
	g->add3ds(GRANERO,"caja.3ds");
	g->addTextura(MADERA,"madera.jpg");
	g->addTextura(METAL,"metal.jpg");

	//initOpenGL();

	Scene* escena = new Scene();

	Vector3 pos;
	Vector3 ambiente(0.5, 0.5, 0.5);
	Vector3 difusa(0.5, 0.5, 0.5);
	Vector3 especular(0.5, 0.5, 0.5);

	//Construimos la escena 3D
	/*
	Camera* camera = escena->addCamera(0.01, 1000.0, 800.0/600.0, 45.0);
	Transformation* transformacion = camera->addTransformation();
	Transformation* transformacionModelo = transformacion->addTransformation();
	Transformation* transformacionPoligono = transformacion->addTransformation();
	Light* luz0 = camera->addLight(pos, ambiente, difusa, especular, 0);
	Model* m = transformacionModelo->addModel(GRANERO, METAL);
    Color color1(1.0,0.0,0.0);
    Polygon* pol = transformacionPoligono->addPolygon(50,color1);
	*/
    //Construimos la escena 2D
    Camera* camera2D = escena->addCamera2D(0, 800, 0, 600);

	Transformation* c_minimapa = camera2D->addTransformation();
	Transformation* t_caja = c_minimapa->addTransformation();
	Shape* p_caja = t_caja->addShape(4, Color(0.3, 0.3, 0.3, 1.0));
	c_minimapa->Translate(650, 450);
	t_caja->Scale(20, 15, 1);

	Transformation* c_transformacion = c_minimapa->addTransformation();
	c_transformacion->Translate(scene2minimap(Vector3(0, 0, -200)));

	Transformation* c_rotacionCono = c_transformacion->addTransformation();
	Shape* c_cono = c_rotacionCono->addShape(3, Color(1.0, 1.0, 0.0, 0.5));

	Shape* c_polygon = c_transformacion->addShape(30, Color(0.0, 0.0, 1.0, 1.0));

	Transformation* c_t2 = c_rotacionCono->addTransformation();
	c_t2->Translate(-10, 10);
	Shape* c_p2 = c_t2->addShape(2, Color(1.0, 1.0, 1.0, 0.8));

	Transformation* c_t3 = c_t2->addTransformation();
	c_t3->Translate(20, 10);
	Shape* c_p3 = c_t3->addShape(4, Color(1.0, 0.0, 1.0, 0.8));

    //escena->Render(false);

	while(!v.isClosing()){
		v.Update();

                escena->Render(false);

		v.Display();
	}

    delete escena;

}
