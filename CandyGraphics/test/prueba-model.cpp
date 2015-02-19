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
	string titulo = "Prueba Render";
	Ventana v(800, 600, titulo);
	Raton mouse(&v);
	//Console consola(&v);
	Console* consola = v.getConsolePtr();

	int contador=0;

	initOpenGL();

	GestorRecursos* g = GestorRecursos::getInstancia();        
	g->add3ds(GRANERO,"personaje.3ds");
	g->addTextura(MADERA,"madera.jpg");        
	g->addTextura(METAL,"metal.jpg");                
	vector<string> comando;

	Scene* escena = new Scene();

	//Construimos la escena 3D
	Vector3 pos;
	Vector3 ambiente(0.5, 0.5, 0.5);
	Vector3 difusa(0.5, 0.5, 0.5);
	Vector3 especular(0.5, 0.5, 0.5);

	Camera* camera = escena->addCamera(1, 2000.0, 4.0/3.0 ,M_PI/2.5);
	Light* luz0 = camera->addLight(pos, ambiente, difusa, especular, 0);

	Transformation* transformacion = camera->addTransformation();
	Transformation* transformacionModelo = transformacion->addTransformation();
	Transformation* transformacionPoligono = transformacion->addTransformation();                               
        
	//Model* m = transformacionModelo->addModel(GRANERO, METAL);
        Model* m = transformacionModelo->addModel(GRANERO,METAL);

	//Color color1(1.0,0.0,0.0);
   // Polygon* pol = transformacionPoligono->addPolygon(50,color1);

	transformacion->Translate(0.0, 0.0, -200.0);

    transformacionPoligono->Scale(0.25,0.25,0.25);
    transformacionPoligono->Translate(0.0, 0.0, -100.0);
        

    //Construimos la escena 2D (HUD)
    Camera* camera2D = escena->addCamera2D(0, 800, 0, 600);
    camera2D->setLight(false);
    camera2D->setDepth(false);
    Transformation* transformacionTexto = camera2D->addTransformation();  
    
    //La GUI debe colgar de la escena 2D
    //Creo que los botones deben ir a la misma altura
    //que la grupbox porque sino se renderizan detras
    Transformation* transformacionGBox = camera2D->addTransformation();
    /*Transformation* transformacionSlide = camera2D->addTransformation();*/
    
    transformacionGBox->Translate(110,320,0);
    /*transformacionSlide->Scale(20,10,1);
    transformacionSlide->Translate(50,20,0);*/
    
    guiGBox* gbox1 = transformacionGBox->addGBox(600,200);
    guiButton* bt1=gbox1->addButton(100,40,"Boton1");
    guiButton* bt2=gbox1->addButton(100,40,"Boton2");
    guiButton* bt3=gbox1->addButton(100,40,"Boton3");
    guiButton* bt4=gbox1->addButton(100,40,"Boton4");
    guiButton* bt5=gbox1->addButton(100,40,"Boton5");
    /*guiSlide* slide = transformacionSlide->addSlide(0,10,1);*/
    
    
    Text* texto = transformacionTexto->addText();    
    Transformation* transformacionConsola = camera2D->addTransformation();
    
    consola->setGNode(transformacionConsola);

    g->addFont(FONT_ANARCHY,"AnarchySans.otf");
    g->addFont(FONT_INTUITIVE,"intuitive.ttf");
    g->addFont(FONT_ANARCHY,"intuitive.ttf");

    

    //Cargamos las fuentes
    //GestorRecursos *g = GestorRecursos::getInstancia();   
    
    cout << "Cargo en Gestor AnarchySans, esta debe de funcionar" << endl;
    if(g->addFont(FONT_ANARCHY,"AnarchySans.otf")){
    	cout << "Anarchy Cargada" << endl;
    }else{
    	cout << "algo falla" << endl;
    }

    cout << "Cargo en Gestor Intuitive, esta debe de funcionar" << endl;
    if(g->addFont(FONT_INTUITIVE,"intuitive.ttf")){
    	cout << "Intuitive Cargada" << endl;
    }else{
    	cout << "algo falla" << endl;
    }

    cout << "Cargo una fuente que no existe de de fallar" << endl;
    if(!g->addFont(5,"noexiste.ttf")){
    	cout << "No existe y da error, por lo que bien" << endl;
    }else{
    	cout << "Ha devuelto True, algo falla" << endl;
    }

    cout << "Cargo una fuente que existe pero repitiendo ids" << endl;
    if(!g->addFont(FONT_ANARCHY,"intuitive.ttf")){
    	cout << "Existe pro da error por id repetido" << endl;
    }else{
    	cout << "Ha devuelto True, algo falla" << endl;
    }

    transformacionTexto->Translate(-300, 200, 0);    

    // Set the font size and render a small text.
    //fuente.FaceSize(15);    
    
	while(!v.isClosing()){
		v.Update();                                

		actualizarConsola(v.getConsolePtr(), transformacionModelo);

		//transformacionModelo->Rotate(1, 0.001);
		transformacionPoligono->Rotate(1, 0.01);

		//Imprimimos los FPS
		ostringstream formato_fps;
		formato_fps << "FPS: " << v.getFramesPerSecond();
		texto->setTamanyo(15);
		texto->setFont(FONT_ANARCHY);
		texto->setTexto(formato_fps.str());

		escena->Render(false);
                                

		v.Display();
	}

	delete escena;
}

