#include <iostream>
#include <stdlib.h>
#include "CandyGraphics.h"


using namespace std;
using namespace candy;

Transformation* t;
Model* m;
int id = 0;
GestorRecursos* gestor;
bool shader = false;


/*
void
initOpenGL(){
	// Set color and depth clear value
    glClearColor(0.f, 0.f, 0.f, 0.f);
	glClearDepth(1.f);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
}
*/

void
actualizarConsola(Console* consola, Model* m){
	vector<string> comando;


	if(consola->IsActive()){ //Comprobamos que la consola este activa
		if(consola->IsComplete()){ //Comprobamos que el comando este completo
			comando = consola->GetCommandSplitted(); //Cogemos el comando ya troceado

			if(comando.size() > 0){
				if(comando.size()==2 && comando[0] == "model")
				{
					id++;
					gestor->add3ds(id,comando[1]);
					m->setIdModel(id);
				}

				if(comando.size()==2 && comando[0] == "texture")
				{
					id++;
					m->setColor(1,1,1,1);
					gestor->addTextura(id,comando[1]);
					m->setTexture(id);
				}
				if(comando.size()==4 && comando[0] == "t")
				{
					t->setTranslation(atof(comando[1].c_str()),atof(comando[2].c_str()),atof(comando[3].c_str()));
				}
				if(comando.size()==4 && comando[0] == "s")
				{
					t->setScalation(atof(comando[1].c_str()),atof(comando[2].c_str()),atof(comando[3].c_str()));
				}
				if(comando.size()==1 && comando[0] == "activarShader"){
					shader = true;
				}
				if(comando.size()==1 && comando[0] == "desactivarShader"){
					shader = false;
				}
			}
		}
	}
}



int main()
{
	//Params por defecto
	float ancho = 800;
	float alto = 600;
	string titulo = "Cargador de Modelos";

	Ventana* v = new Ventana(ancho, alto, titulo); //Parametros por defecto

	CandyGraphics cg;
	cg.InitOpenGL();
	cg.setClearColor(Color::Cyan);

	Scene* escena = cg.getScenePtr();
	Teclado teclado;

	gestor = GestorRecursos::getInstancia();

	//A�adimos y nos guardamos los punteros a las dos camaras
	Camera* cam3D = escena->addCamera(1, 2000.0, ancho/alto , 45);
	Camera* cam2D = escena->addCamera2D(0, ancho, 0, alto);
	cam2D->setLight(false);
	cam2D->setDepth(false);

	cam3D->addLight(Vector3(0, 0, 0), Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(1, 1, 1), 0);
	//cam3D->addLight(Vector3(0, 1, 0), Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(1, 1, 1), 1);
	//cam3D->addLight(Vector3(1, 0, 0), Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(1, 1, 1), 2);

	t = cam3D->addTransformation();
	t->setTranslation(Vector3(0,0,-10));
	m = t->addModel(GestorRecursos::E_Mono,-1);
	m->setColor(0.5,0.5,0.5,1);
	Console* consola = v->getConsolePtr();

	Transformation* tcon = cam2D->addTransformation();

	Transformation* tTitulo = cam2D->addTransformation();
	Transformation* tInstrucciones = cam2D->addTransformation();
	Transformation* tComandos1 = cam2D->addTransformation();
	Transformation* tComandos2 = cam2D->addTransformation();
	Transformation* tComandos3 = cam2D->addTransformation();
	Transformation* tComandos4 = cam2D->addTransformation();
	Text* Titulo = tTitulo->addText();
	Text* Intrucciones = tInstrucciones->addText();
	Text* Comando1 = tComandos1->addText();
	Text* Comando2 = tComandos2->addText();
	Text* Comando3 = tComandos3->addText();
	Text* Comando4 = tComandos4->addText();

	tTitulo->setTranslation((Vector2(275,550)));
	tInstrucciones->setTranslation(Vector2(50,500));
	tComandos1->setTranslation(Vector2(50,475));
	tComandos2->setTranslation(Vector2(50,450));
	tComandos3->setTranslation(Vector2(50,425));
	tComandos4->setTranslation(Vector2(50,400));

	Titulo->setTexto("Cargador De Modelos");
	Intrucciones->setTexto("Para mostrar la consola pulsar ALT");
	Comando1->setTexto("model ruta (carga el modelo)");
	Comando2->setTexto("texture ruta (carga la textura)");
	Comando3->setTexto("t x y z (posiciona el modelo)");
	Comando4->setTexto("s x y z (escala el modelo)");

	Titulo->setTamanyo(25);
	Intrucciones->setTamanyo(15);
	Comando1->setTamanyo(15);
	Comando2->setTamanyo(15);
	Comando3->setTamanyo(15);
	Comando4->setTamanyo(15);

	Titulo->setColor(Color::Black);
	Intrucciones->setColor(Color::Black);
	Comando1->setColor(Color::Black);
	Comando2->setColor(Color::Black);
	Comando3->setColor(Color::Black);
	Comando4->setColor(Color::Black);

	tcon->setTranslation(Vector2(0,-400));
	consola->setGNode(tcon);

	//initOpenGL();

	while(!v->isClosing()){
		v->Update();
		t->Rotate(1,0.0015);
		actualizarConsola(consola, m);
		if(shader){
			gestor->activateShader(GestorRecursos::S_Phong);
		}else{
			gestor->desactivateShader(GestorRecursos::S_Phong);
		}
		cg.Render();
		gestor->desactivateShader(GestorRecursos::S_Phong);
		v->Display();
	}

	return 0;
}
