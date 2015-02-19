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

	CandyGraphics cg;

	Ventana* v = new Ventana(ancho, alto, titulo); //Parametros por defecto
	cg.InitOpenGL();

	if(GL_ARB_fragment_shader && GL_ARB_vertex_shader){s
		cout << "OK" << endl;
	}else{
		cout << "MAL" << endl;
	}
}
