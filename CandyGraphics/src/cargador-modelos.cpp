#include "CandyGraphics.h"
#include <sstream>
using namespace std;
using namespace candy;

#define F_ANARCHY 1
#define GRANERO 2
#define ID_MODELO 10

float posX_anterior = 0;
float posY_anterior = 0;

void
actualizarTeclado(Teclado* tec, Transformation* t_modelo){
	if(tec->isPulsada(Teclado::W)){
		t_modelo->Translate(0, 0, -1);
	}

	if(tec->isPulsada(Teclado::S)){
		t_modelo->Translate(0, 0, 1);
	}

	if(tec->isPulsada(Teclado::A)){
		t_modelo->Translate(-0.1, 0, 0);
	}

	if(tec->isPulsada(Teclado::D)){
		t_modelo->Translate(0.1, 0, 0);
	}
}

void
actualizarMouse(Raton* rat, Teclado* tec, Transformation* t_modelo){
	Vector2 pos_raton = rat->getPosition();
	if(pos_raton.getX() != -1){ //Si esta dentro de la ventana
		//Calculo el coeficiente que relaciona ancho_ventana con angulo
		float coeficiente_x = 2.0 * M_PI / 800;
		float coeficiente_y = 2.0 * M_PI / 600;

		float dx = pos_raton.getX() - posX_anterior;
		dx /= 1;

		float dy = pos_raton.getY() - posY_anterior;
		dy /= 1;

		if(dx != 0){
			float ang_x = dx * coeficiente_x;

			cout << "ROTAMOS: " << ang_x << endl;

			if(ang_x > 2.0 * M_PI){
				ang_x = 0;
			}else if(ang_x < -2.0 * M_PI){
				ang_x = 2.0 * M_PI;
			}

			t_modelo->Rotate(1, ang_x);

			posX_anterior = pos_raton.getX();
		}

		if(dy != 0){
			float ang_y = dy * coeficiente_y;

			cout << "ROTAMOS: " << ang_y << endl;

			if(ang_y > 2.0 * M_PI){
				ang_y = 0;
			}else if(ang_y < -2.0 * M_PI){
				ang_y = 2.0 * M_PI;
			}

			if(tec->isPulsada(Teclado::RAlt)){
				t_modelo->Rotate(2, -ang_y);
			}else{
				t_modelo->Rotate(0, ang_y);
			}

			posY_anterior = pos_raton.getY();
		}
	}
}

int main(int argc, char **argv) {
	float ancho = 800;
	float alto = 600;
	Ventana* v = new Ventana(ancho, alto, "Cargador de modelos");
	Teclado* tec = new Teclado();
	Raton* rat = new Raton(v);
	CandyGraphics cg;

	GestorRecursos* gr = GestorRecursos::getInstancia();
	gr->addFont(F_ANARCHY, "AnarchySans.otf");
	gr->add3ds(GRANERO, "caja.3ds");

	Scene* escena = cg.getScenePtr();

	Camera* camera3d = escena->addCamera(1, 2000.0, ancho/alto , M_PI/2.5);
	Camera* camera2d = escena->addCamera2D(0, ancho, 0, alto);

	Vector3 pos;
	Vector3 ambiente(0.5, 0.5, 0.5);
	Vector3 difusa(0.5, 0.5, 0.5);
	Vector3 especular(0.5, 0.5, 0.5);
	Light* luz = camera3d->addLight(pos, ambiente, difusa, especular, 0);

	Transformation* t_modelo = camera3d->addTransformation();
	t_modelo->Translate(1, 0, -150);
		//Init a un modelo por defecto
	Model* modelo = t_modelo->addModel(GestorRecursos::E_Mono, -1);
	modelo->setID(ID_MODELO);
	string modeloActual = "caja.3ds";

	//Dibujamos strings de texto
	Transformation* t_texto = camera2d->addTransformation();
	t_texto->Translate(50, 550);
		//Titulo de la aplicacion
	Text* textoTitulo = t_texto->addText();
	textoTitulo->setFont(F_ANARCHY);
	textoTitulo->setTamanyo(15);
	textoTitulo->setColor(Color(1.0, 0.0, 0.0, 1.0));
	textoTitulo->setTexto("Cargador de Modelos - CandyGraphics");
		//Modelo actual
	Transformation* t_texto2 = t_texto->addTransformation();
	t_texto2->Translate(0, -30);
	Text* texto2 = t_texto2->addText();
	texto2->setFont(F_ANARCHY);
	texto2->setTamanyo(15);
	texto2->setColor(Color(1.0, 0.0, 0.0, 1.0));

	Vector2 pos_raton;

	while(!v->isClosing()){
		v->Update();

		pos_raton = rat->getPosition();

		actualizarTeclado(tec, t_modelo);

		actualizarMouse(rat, tec, t_modelo);

		t_modelo->Rotate(1, 0.001);

		cg.Render();

		v->Display();
	}
}
