#include <iostream>
#include <sstream>
using namespace std;

#include "CandyGraphics.h"
#include <cmath>
#include "FTGL/ftgl.h"
using namespace candy;

#define METAL 10
#define MADERA 20
#define GRANERO 30
#define FONT_ANARCHY 10
#define FONT_INTUITIVE 20

#define MONIGOTE 40

void
initOpenGL(){
	// Set color and depth clear value
    glClearColor(0.f, 0.f, 0.f, 0.f);
	glClearDepth(1.f);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

//Solo vamos a usar la consola para modificar transformaciones, de momento
void
actualizarConsola(Console* consola, Transformation* t){
	vector<string> comando;


	if(consola->IsActive()){ //Comprobamos que la consola este activa
		if(consola->IsComplete()){ //Comprobamos que el comando este completo
			comando = consola->GetCommandSplitted(); //Cogemos el comando ya troceado

			if(comando.size() > 0){
				// SINTAXIS:
				// rotar|r	eje	angulo --> Rotar
				// escalar|s  escX escY escZ --> Escalar
				// transladar|t tranX tranY tranZ --> Transladar
				// luz|l p|a|d|e X/R Y/G Z/B  --> Manejar las luces (elegimos param y sus valores)
				// fps --> Muestra los fps actuales

				if(comando[0] == "rotar" || comando[0] == "r"){
					if(comando.size() == 3){
						int eje = atoi(comando[1].c_str());
						float angulo_rot = atof(comando[2].c_str());

						//Aplicamos la transformacion
						t->Rotate(eje, angulo_rot);
					}
				}else if(comando[0] == "escalar" || comando[0] == "s"){
					if(comando.size() == 4){
						Vector3 escalado;

						escalado.setX(atof(comando[1].c_str()));
						escalado.setY(atof(comando[2].c_str()));
						escalado.setZ(atof(comando[3].c_str()));

						//Aplicamos la transformacion
						t->Scale(escalado);
					}
				}else if(comando[0] == "trasladar" || comando[0] == "t"){
					if(comando.size() == 4){
						Vector3 translacion;

						translacion.setX(atof(comando[1].c_str()));
						translacion.setY(atof(comando[2].c_str()));
						translacion.setZ(atof(comando[3].c_str()));

						//Aplicamos la transformacion
						t->Translate(translacion);
					}
				}
			}
		}
	}
}

int main(int argc, char **argv) {
	//Params por defecto
	float ancho = 800;
	float alto = 600;
	string titulo = "CandyNapper";

	Ventana* v = new Ventana(ancho, alto, titulo); //Parametros por defecto
	Raton raton(v);
	Teclado tec;
	CandyGraphics cg;
	Scene* escena = cg.getScenePtr();

	//A–adimos y nos guardamos los punteros a las dos camaras
	Camera* cam3D = escena->addCamera(1, 2000.0, ancho/alto , M_PI/2.5);
	Camera* cam2D = escena->addCamera2D(0, ancho, 0, alto);

	Vector3 pos;
	Vector3 ambiente(0.5, 0.5, 0.5);
	Vector3 difusa(0.5, 0.5, 0.5);
	Vector3 especular(0.5, 0.5, 0.5);
	cam3D->addLight(pos, ambiente, difusa, especular, 0);

	//Cargamos los recursos del gestor de recursos
	GestorRecursos* gs = GestorRecursos::getInstancia();

	gs->addFont(FONT_ANARCHY, "AnarchySans.otf");
	gs->addFont(FONT_INTUITIVE, "intuitive.ttf");
	gs->add3ds(GRANERO, "caja.3ds");
	gs->addTextura(MADERA, "madera.jpg");

	//Aqui deberiamos de poner "enmedio" una transformacion (que sea la que "mueve" la camara)
	Transformation* tModel = cam3D->addTransformation();
	Transformation* tPolygon = cam3D->addTransformation();

	Model* m = tModel->addModel(GRANERO, MADERA);
	Shape* pol = tPolygon->addShape(30, Color(0.6, 0.6, 0.6, 1.0));

	tModel->Translate(0, 0, -200);
	tPolygon->Translate(0, 0, -250);
	tPolygon->Scale(0.25, 0.25, 0.25);

	Console* c = v->getConsolePtr();
	Transformation* t_consola = cam2D->addTransformation();

	//Settings de la consola
	c->setGNode(t_consola);

	Transformation* tTexto = cam2D->addTransformation();
	Text* texto = tTexto->addText();
	texto->setFont(FONT_ANARCHY);
	texto->setTamanyo(15);
	texto->setColor(Color(1.0, 1.0, 1.0, 1.0));

	tTexto->Translate(50, 550, 0);

	Transformation* tTexto2 = cam2D->addTransformation();
	Text* texto2 = tTexto2->addText();
	texto2->setFont(FONT_INTUITIVE);
	texto2->setTamanyo(15);
	texto2->setColor(Color(1.0, 1.0, 1.0, 1.0));

	tTexto2->Translate(50, 500, 0);

	while(!v->isClosing()){
		v->Update();

		actualizarConsola(c, tModel);

		tModel->Rotate(1, 0.01);
		tPolygon->Rotate(1, 0.001);

		ostringstream form_fps;
		form_fps << "FPS: " << v->getFramesPerSecond();
		texto->setTexto(form_fps.str());

		ostringstream form_raton;
		Vector2 pos_raton = raton.getPosition();
		form_raton << "PosX: " << pos_raton.getX() << " PosY: " << pos_raton.getY();
		texto2->setTexto(form_raton.str());

		if(tec.isPulsada(Teclado::W)){
			tModel->Translate(0, 0, -1);
		}

		if(tec.isPulsada(Teclado::S)){
			tModel->Translate(0, 0, 1);
		}

		if(tec.isPulsada(Teclado::A)){
			tModel->Translate(-1, 0, 0);
		}

		if(tec.isPulsada(Teclado::D)){
			tModel->Translate(1, 0, 0);
		}

		cg.Render();

		v->Display();
	}
}
