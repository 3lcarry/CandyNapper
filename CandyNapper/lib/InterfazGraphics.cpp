/*
 * Graphics.cpp
 *
 *  Created on: 19/11/2011
 *      Author: kaseyo
 */

#include "CandyGraphics.h"
#include "InterfazGraphics.h"
#include "HUD.h"
#include "World3D.h"
#include "Menu.h"
#include <cmath>
#include <iostream>

//DEBUG
#include <sstream>
#include "Timer.h"
//FIN DEBUG

using namespace std;

using namespace candy;

InterfazGraphics* InterfazGraphics::_instancia = NULL;

InterfazGraphics*
InterfazGraphics::getInstance(){
	if(_instancia == NULL){
		_instancia = new InterfazGraphics();
	}

	return _instancia;
}

InterfazGraphics::InterfazGraphics() {
	//Params por defecto
	float ancho;
	float alto;
	string titulo = "CandyNapper";

	_ventana = new Ventana(titulo); //Parametros por defecto

	ancho = _ventana->getWidth();
	alto = _ventana->getHeight();

	cout << "[InterfazGraphics] Antes de init el motor grafico" << endl;
	cout << Timer::getTimeElapsed() << endl;

	//Init del motor grafico...
	_mg = new CandyGraphics();
	_mg->InitOpenGL();
	_mg->setClearColor(Color(0.5, 0.8, 0.99, 1.0)); //Azul cielo

	cout << "[InterfazGraphics]Despues de init el motor grafico" << endl;
	cout << Timer::getTimeElapsed() << endl;

	cout << "[InterfazGraphics]Antes de cargar los recursos" << endl;
	cout << Timer::getTimeElapsed() << endl;

	//Cargamos los recursos
	LoadResources();

	cout << "[InterfazGraphics]Despues de cargar los recursos" << endl;
	cout << Timer::getTimeElapsed() << endl;

	_World3D = new World3D(_mg->getScenePtr(), _ventana);

	_HUD = new HUD(_mg->getScenePtr(), _ventana);
	_HUD->getHUDCamera()->setActive(false);

	_MenuPrincipal = new Menu(_mg->getScenePtr(), _ventana, "CandyNapper",80);

	_MenuPrincipal->setFondo(InterfazGraphics::T_FondoMenu);

	_MenuPrincipal->addButton(Vector2(250,250),"Comenzar Partida",Menu::P_ComenzarPartida,200,40);
	_MenuPrincipal->addButton(Vector2(250,200)," Partida Rapida ",Menu::P_PartidaRapida,200,40);
	_MenuPrincipal->addButton(Vector2(250,150)," Cargar Partida ",Menu::P_Cargar,200,40);
	_MenuPrincipal->addButton(Vector2(250,100),"     Salir      ",Menu::P_Salir,200,40);

	_MenuIngame = new Menu(_mg->getScenePtr(),_ventana, "Pause", 40);

	cout << "[InterfazGraphics]A mitad del constructor de ig" << endl;
	cout << Timer::getTimeElapsed() << endl;

	Transformation* t = _MenuIngame->getMenuCamera()->addTransformation();
	t->setScalation(Vector2(ancho,alto));
	t->setTranslation(Vector3(ancho/2.0,alto/2.0, -0.5));
	Shape* p= t->addShape(4,Color(0,0,0,0.2));
	p->setID(-1);

	_MenuIngame->getMenuCamera()->setActive(false);
	_MenuIngame->addButton(Vector2(ancho/2.0,400),"    Guardar    ",Menu::I_Guardar,200,40);
	_MenuIngame->addButton(Vector2(ancho/2.0,350),"    Continuar  ",Menu::I_Continuar,200,40);
	_MenuIngame->addButton(Vector2(ancho/2.0,300)," Menu Principal",Menu::I_MenuPrincipal,200,40);
	_MenuIngame->addButton(Vector2(ancho/2.0,250),"      Salir    ",Menu::I_Salir,200,40);

	_MenuChangeLevel = new Menu(_mg->getScenePtr(),_ventana, "Nivel Completado",80);
	_MenuChangeLevel->getMenuCamera()->setActive(false);
	_MenuChangeLevel->setFondo(Color::Black);
	_MenuChangeLevel->addButton(Vector2(ancho/2.0,400),"    Guardar",Menu::CL_Guardar,200,40);
	_MenuChangeLevel->addButton(Vector2(ancho/2.0,350)," Siguiente Nivel",Menu::CL_Continuar,200,40);


	_MenuFinish = new Menu(_mg->getScenePtr(), _ventana, "Has perdido",80);
	_MenuFinish->getMenuCamera()->setActive(false);
	_MenuFinish->setFondo(Color::Black);
	_MenuFinish->addButton(Vector2(ancho/2.0,300),"   Reintentar ",Menu::I_Reintentar,200,40);
	_MenuFinish->addButton(Vector2(ancho/2.0,250)," Menu Principal",Menu::I_MenuPrincipal,200,40);
	_MenuFinish->addButton(Vector2(ancho/2.0,200),"      Salir    ",Menu::I_Salir,200,40);


	_MenuWin = new Menu(_mg->getScenePtr(), _ventana, "Has Ganado",80);
	_MenuWin->getMenuCamera()->setActive(false);
	_MenuWin->setFondo(Color::Black);
	_MenuWin->addButton(Vector2(ancho/2.0,300)," Menu Principal",Menu::I_MenuPrincipal,200,40);

	//Panel central
	_MsgCentral = _mg->getScenePtr()->addCamera2D(0,ancho,0,alto);
	_MsgCentral->setDepth(false);
	_MsgCentral->setLight(false);

	Transformation* trans_caja = _MsgCentral->addTransformation();
	trans_caja->Translate(800, 400, 0);
	trans_caja->Scale(40, 20, 1);
	_CuadroCentral = trans_caja->addShape(4, Color(0.6, 0.6, 0.6, 0.8));

	Transformation* trans_texto = _MsgCentral->addTransformation();
	trans_texto->Translate(550, 450, 0);
	_TextoCentral1 = trans_texto->addText();
	_TextoCentral1->setColor(Color(1.0, 0.0, 0.0, 1.0));
	_TextoCentral1->setTamanyo(25);
	_TextoCentral1->setFont(GestorRecursos::E_Anarchy);
	_TextoCentral1->setTexto("");

	Transformation* trans_texto2 = _MsgCentral->addTransformation();
	trans_texto2->Translate(550, 400, 0);
	_TextoCentral2 = trans_texto2->addText();
	_TextoCentral2->setColor(Color(1.0, 0.0, 0.0, 1.0));
	_TextoCentral2->setTamanyo(25);
	_TextoCentral2->setFont(GestorRecursos::E_Anarchy);
	_TextoCentral2->setTexto("");

	_MsgCentral->setActive(false);

	//DEBUG FPS
	Camera* c_fps = _mg->getScenePtr()->addCamera2D(0, ancho, 0, alto);
	c_fps->setLight(false);
	c_fps->setDepth(false);
	Transformation* t_fps = c_fps->addTransformation();
	t_fps->Translate(ancho - 200, 50);
	_FPS = t_fps->addText();
	_FPS->setColor(Color::Red);
	_FPS->setTamanyo(15);
	//FIN DEBUG

	tiempoMostradoCentral = 0;

	cout << "[InterfazGraphics]Al final del constructor de ig" << endl;
	cout << Timer::getTimeElapsed() << endl;
}

void candy::InterfazGraphics::visibilidadHUD(bool vis)
{
	_HUD->getHUDCamera()->setActive(vis);
}

void candy::InterfazGraphics::visibilidadWorld(bool vis)
{
	_World3D->getCamera3D()->setActive(vis);
}

void candy::InterfazGraphics::visibilidadMenuPrincipal(bool vis)
{
	_MenuPrincipal->getMenuCamera()->setActive(vis);
}

int candy::InterfazGraphics::seleccionMenu()
{
	int resultado = -1;

	Vector2 pos = Raton::getPosition(_ventana);

	resultado = _MenuPrincipal->getMenuCamera()->seleccion(pos.getX(),pos.getY());

	return resultado;
}

void candy::InterfazGraphics::visibilidadMenuIngame(bool vis)
{
	_MenuIngame->getMenuCamera()->setActive(vis);
}

int candy::InterfazGraphics::seleccionMenuIngame()
{
	int resultado = -1;

	Vector2 pos = Raton::getPosition(_ventana);

	resultado = _MenuIngame->getMenuCamera()->seleccion(pos.getX(),pos.getY());

	return resultado;

}

void InterfazGraphics::visibilidadMenuFinish(bool vis){
	_MenuFinish->getMenuCamera()->setActive(vis);
}

int InterfazGraphics::seleccionMenuFinish(){
	int resultado = -1;

	Vector2 pos = Raton::getPosition(_ventana);

	resultado = _MenuFinish->getMenuCamera()->seleccion(pos.getX(),pos.getY());

	return resultado;
}

void InterfazGraphics::visibilidadMenuWin(bool vis){
	_MenuWin->getMenuCamera()->setActive(vis);
}

void candy::InterfazGraphics::visibilidadMenuCambioNivel(bool vis)
{
	_MenuChangeLevel->getMenuCamera()->setActive(vis);
}

int candy::InterfazGraphics::seleccionMenuCambioNivel()
{
	int resul = -1;
	if(Raton::isPressed(Raton::Izquierdo))
	{
		Vector2 pos = Raton::getPosition(_ventana);
		resul = _MenuChangeLevel->getMenuCamera()->seleccion(pos.getX(),pos.getY());
	}

	return resul;
}

int
candy::InterfazGraphics::seleccionMenuWin(){
	int resul = -1;
	if(Raton::isPressed(Raton::Izquierdo))
	{
		Vector2 pos = Raton::getPosition(_ventana);
		resul = _MenuWin->getMenuCamera()->seleccion(pos.getX(),pos.getY());
	}

	return resul;
}

void
candy::InterfazGraphics::visibilidadMenuGameOver(bool vis){
	_MenuGameOver->getMenuCamera()->setActive(vis);
}

int
candy::InterfazGraphics::seleccionMenuGameOver(){
	int resul = -1;
	if(Raton::isPressed(Raton::Izquierdo))
	{
		Vector2 pos = Raton::getPosition(_ventana);
		resul = _MenuGameOver->getMenuCamera()->seleccion(pos.getX(),pos.getY());
	}

	return resul;
}

void
InterfazGraphics::LoadResources(){
	//Cargamos los recursos del gestor de recursos (from xml, maybe)
	_gr = GestorRecursos::getInstancia();

	string rec_folder = (string)CANDYROOT + "/resources/";

	_gr->addTextura(T_Chico, rec_folder+"explorador.jpg");
	_gr->addTextura(T_Chica, rec_folder+"coloresTia.png");
	//_gr->add3ds(M_Granero, rec_folder+"caja.3ds");
	//_gr->add3ds(M_Granero, rec_folder+"personaje.3ds");
	_gr->addTextura(T_SkyBack, rec_folder+"sback37.jpg");
	_gr->addTextura(T_SkyFront, rec_folder+"sfront37.jpg");
	_gr->addTextura(T_SkyTop, rec_folder+"stop37.jpg");
	_gr->addTextura(T_SkyBottom, rec_folder+"suelo.jpg");
	_gr->addTextura(T_SkyLeft, rec_folder+"sleft37.jpg");
	_gr->addTextura(T_SkyRight, rec_folder+"sright37.jpg");
	_gr->addTextura(T_Algodon,rec_folder+"algodon.png");
	_gr->addTextura(T_Chupachups,rec_folder+"chupa.png");
	_gr->addTextura(T_OsoAmarillo,rec_folder+"osoamarillov2.png");
	_gr->addTextura(T_OsoRojo,rec_folder+"osorojov2.png");
	_gr->addTextura(T_OsoAzul,rec_folder+"osoazulv2.png");
	_gr->addTextura(T_OsoVerde,rec_folder+"osoverdev2.png");
	_gr->addTextura(T_Gengibre,rec_folder+"gengibre.png");
	_gr->addTextura(T_Osito100,rec_folder+"explorador.jpg");
	_gr->addTextura(T_Osito50,rec_folder+"explorador.jpg");
	_gr->addTextura(T_Melon,rec_folder+"melon.png");
	_gr->addTextura(T_Suelo, rec_folder+"suelo.jpg");
	_gr->addTextura(T_Tarta, rec_folder+"tarta.png");
	_gr->addTextura(T_FondoMenu,rec_folder+"menu.jpg");
	_gr->addTextura(T_Botiquin,rec_folder+"botiquin.png");
	_gr->addTextura(T_Jeringuilla,rec_folder+"jeringuilla.png");
	_gr->addTextura(T_Miel,rec_folder+"miel.jpg");
	_gr->addTextura(T_Espada,rec_folder+"espada.png");
	_gr->addTextura(T_Portal,rec_folder+"portal.png");
	_gr->addTextura(T_Metal,rec_folder+"metal.jpg");

	cout << "[InterfazGraphics]Texturas cargadas" << endl;
	cout << Timer::getTimeElapsed() << endl;


	_gr->add3ds(M_Chico, rec_folder+"defaultboy.3ds");
	_gr->add3ds(M_Chica, rec_folder+"fleurOptonl.3ds");
	_gr->add3ds(M_Melon, rec_folder+"melon.3ds");
	_gr->add3ds(M_Algodon, rec_folder+"algodon.3ds");
	_gr->add3ds(M_Chupachups, rec_folder+"chupa.3ds");
	_gr->add3ds(M_Oso, rec_folder+"osov2.3ds");
	_gr->add3ds(M_Gengibre, rec_folder+"gengibre.3ds");
	_gr->add3ds(M_ChicaMovimiento1, rec_folder+"fleurmov1.3ds");
	_gr->add3ds(M_ChicaMovimiento2, rec_folder+"fleurmov2.3ds");
	_gr->add3ds(M_ChicaMovimiento3, rec_folder+"fleurmov3.3ds");
	_gr->add3ds(M_ChicaMovimiento4, rec_folder+"fleurmov4.3ds");
	_gr->add3ds(M_ChicaMovimiento5, rec_folder+"fleurmov5.3ds");
	_gr->add3ds(M_ChicoMovimiento1, rec_folder+"boymov1.3ds");
	_gr->add3ds(M_ChicoMovimiento2, rec_folder+"boymov2.3ds");
	_gr->add3ds(M_ChicoMovimiento3, rec_folder+"boymov3.3ds");
	_gr->add3ds(M_ChicoMovimiento4, rec_folder+"boymov4.3ds");
	_gr->add3ds(M_ChicoMovimiento5, rec_folder+"boymov5.3ds");
	_gr->add3ds(M_ChicoMovimiento6, rec_folder+"boymov6.3ds");
	_gr->add3ds(M_ChicoMovimiento7, rec_folder+"boymov7.3ds");
	_gr->add3ds(M_ChicoMovimiento8, rec_folder+"boymov8.3ds");
	_gr->add3ds(M_ChicoMovimiento9, rec_folder+"boymov9.3ds");
	_gr->add3ds(M_ChicoMovimiento10, rec_folder+"boymov10.3ds");
	_gr->add3ds(M_ChicoMovimiento11, rec_folder+"boymov11.3ds");
	_gr->add3ds(M_ChicoMovimiento12, rec_folder+"boymov12.3ds");
	_gr->add3ds(M_GengibreMovimiento1,rec_folder+"gengibremov1.3ds");
	_gr->add3ds(M_GengibreMovimiento2,rec_folder+"gengibremov2.3ds");
	_gr->add3ds(M_GengibreMovimiento3,rec_folder+"gengibremov3.3ds");
	_gr->add3ds(M_GengibreMovimiento4,rec_folder+"gengibremov4.3ds");
	_gr->add3ds(M_GengibreMovimiento5,rec_folder+"gengibremov5.3ds");
	_gr->add3ds(M_OsoMovimiento1,rec_folder+"osov2mov1.3ds");
	_gr->add3ds(M_OsoMovimiento2,rec_folder+"osov2mov2.3ds");
	_gr->add3ds(M_OsoMovimiento3,rec_folder+"osov2mov3.3ds");
	_gr->add3ds(M_OsoMovimiento4,rec_folder+"osov2mov4.3ds");
	_gr->add3ds(M_OsoMovimiento5,rec_folder+"osov2mov5.3ds");
	_gr->add3ds(M_Tarta, rec_folder+"tarta.3ds");
	_gr->add3ds(M_BotiquinPe, rec_folder+"botiquinp.3ds");
	_gr->add3ds(M_BotiquinMe, rec_folder+"botiquinm.3ds");
	_gr->add3ds(M_BotiquinGr, rec_folder+"botiquing.3ds");
	_gr->add3ds(M_Jeringuilla, rec_folder+"jeringuilla.3ds");
	_gr->add3ds(M_Miel, rec_folder+"miel.3ds");
	_gr->add3ds(M_Espada, rec_folder+"force_edge.3ds");
	_gr->add3ds(M_ChicoAtaque1, rec_folder+"boyAttack1.3ds");
	_gr->add3ds(M_ChicoAtaque2, rec_folder+"boyAttack2.3ds");
	_gr->add3ds(M_ChicoAtaque3, rec_folder+"boyAttack3.3ds");
	_gr->add3ds(M_ChicoAtaque4, rec_folder+"boyAttack4.3ds");
	_gr->add3ds(M_ChicoAtaque5, rec_folder+"boyAttack5.3ds");
	_gr->add3ds(M_ChicoAtaque6, rec_folder+"boyAttack6.3ds");
	_gr->add3ds(M_ChicoAtaque7, rec_folder+"boyAttack7.3ds");
	_gr->add3ds(M_ChicoAtaque8, rec_folder+"boyAttack8.3ds");
	_gr->add3ds(M_ChicoAtaque9, rec_folder+"boyAttack9.3ds");
	_gr->add3ds(M_ChicoAtaque10, rec_folder+"boyAttack10.3ds");
	_gr->add3ds(M_ChicoAtaque11, rec_folder+"boyAttack11.3ds");
	_gr->add3ds(M_ChicaAtaque, rec_folder+"fleurAttack.3ds");
	_gr->add3ds(M_Pistola, rec_folder+"pistola.3ds");
	_gr->add3ds(M_GengibreAtaque1, rec_folder+"gengAttack1.3ds");
	_gr->add3ds(M_GengibreAtaque2, rec_folder+"gengAttack2.3ds");
	_gr->add3ds(M_GengibreAtaque3, rec_folder+"gengAttack3.3ds");
	_gr->add3ds(M_GengibreAtaque4, rec_folder+"gengAttack4.3ds");
	_gr->add3ds(M_GengibreAtaque5, rec_folder+"gengAttack5.3ds");
	_gr->add3ds(M_GengibreAtaque6, rec_folder+"gengAttack6.3ds");
	_gr->add3ds(M_GengibreAtaque7, rec_folder+"gengAttack7.3ds");
	_gr->add3ds(M_GengibreAtaque8, rec_folder+"gengAttack8.3ds");
	_gr->add3ds(M_OsoAtaque1, rec_folder+"osoAttack1.3ds");
	_gr->add3ds(M_OsoAtaque2, rec_folder+"osoAttack2.3ds");
	_gr->add3ds(M_OsoAtaque3, rec_folder+"osoAttack3.3ds");
	_gr->add3ds(M_OsoAtaque4, rec_folder+"osoAttack4.3ds");
	_gr->add3ds(M_OsoAtaque5, rec_folder+"osoAttack5.3ds");
	_gr->add3ds(M_OsoAtaque6, rec_folder+"osoAttack6.3ds");
	_gr->add3ds(M_OsoAtaque7, rec_folder+"osoAttack7.3ds");
	_gr->add3ds(M_OsoAtaque8, rec_folder+"osoAttack8.3ds");
	_gr->add3ds(M_Portal, rec_folder+"moria.3ds");


/*
	_gr->addBin(M_Chico, rec_folder+"defaultboy.bin");
	_gr->addBin(M_Chica, rec_folder+"fleurOptonl.bin");
	_gr->addBin(M_Melon, rec_folder+"melon.bin");
	_gr->addBin(M_Algodon, rec_folder+"algodon.bin");
	_gr->addBin(M_Chupachups, rec_folder+"chupa.bin");
	_gr->addBin(M_Oso, rec_folder+"osov2.bin");
	_gr->addBin(M_Gengibre, rec_folder+"gengibre.bin");
	_gr->addBin(M_ChicaMovimiento1, rec_folder+"fleurmov1.bin");
	_gr->addBin(M_ChicaMovimiento2, rec_folder+"fleurmov2.bin");
	_gr->addBin(M_ChicaMovimiento3, rec_folder+"fleurmov3.bin");
	_gr->addBin(M_ChicaMovimiento4, rec_folder+"fleurmov4.bin");
	_gr->addBin(M_ChicaMovimiento5, rec_folder+"fleurmov5.bin");
	_gr->addBin(M_ChicoMovimiento1, rec_folder+"boymov1.bin");
	_gr->addBin(M_ChicoMovimiento2, rec_folder+"boymov2.bin");
	_gr->addBin(M_ChicoMovimiento3, rec_folder+"boymov3.bin");
	_gr->addBin(M_ChicoMovimiento4, rec_folder+"boymov4.bin");
	_gr->addBin(M_ChicoMovimiento5, rec_folder+"boymov5.bin");
	_gr->addBin(M_ChicoMovimiento6, rec_folder+"boymov6.bin");
	_gr->addBin(M_ChicoMovimiento7, rec_folder+"boymov7.bin");
	_gr->addBin(M_ChicoMovimiento8, rec_folder+"boymov8.bin");
	_gr->addBin(M_ChicoMovimiento9, rec_folder+"boymov9.bin");
	_gr->addBin(M_ChicoMovimiento10, rec_folder+"boymov10.bin");
	_gr->addBin(M_ChicoMovimiento11, rec_folder+"boymov11.bin");
	_gr->addBin(M_ChicoMovimiento12, rec_folder+"boymov12.bin");
	_gr->addBin(M_GengibreMovimiento1,rec_folder+"gengibremov1.bin");
	_gr->addBin(M_GengibreMovimiento2,rec_folder+"gengibremov2.bin");
	_gr->addBin(M_GengibreMovimiento3,rec_folder+"gengibremov3.bin");
	_gr->addBin(M_GengibreMovimiento4,rec_folder+"gengibremov4.bin");
	_gr->addBin(M_GengibreMovimiento5,rec_folder+"gengibremov5.bin");
	_gr->addBin(M_OsoMovimiento1,rec_folder+"osov2mov1.bin");
	_gr->addBin(M_OsoMovimiento2,rec_folder+"osov2mov2.bin");
	_gr->addBin(M_OsoMovimiento3,rec_folder+"osov2mov3.bin");
	_gr->addBin(M_OsoMovimiento4,rec_folder+"osov2mov4.bin");
	_gr->addBin(M_OsoMovimiento5,rec_folder+"osov2mov5.bin");
	_gr->addBin(M_Tarta, rec_folder+"tarta.bin");
	_gr->addBin(M_BotiquinPe, rec_folder+"botiquinp.bin");
	_gr->addBin(M_BotiquinMe, rec_folder+"botiquinm.bin");
	_gr->addBin(M_BotiquinGr, rec_folder+"botiquing.bin");
	_gr->addBin(M_Jeringuilla, rec_folder+"jeringuilla.bin");
	_gr->addBin(M_Miel, rec_folder+"miel.bin");
	_gr->addBin(M_Espada, rec_folder+"force_edge.bin");
	_gr->addBin(M_ChicoAtaque1, rec_folder+"boyAttack1.bin");
	_gr->addBin(M_ChicoAtaque2, rec_folder+"boyAttack2.bin");
	_gr->addBin(M_ChicoAtaque3, rec_folder+"boyAttack3.bin");
	_gr->addBin(M_ChicoAtaque4, rec_folder+"boyAttack4.bin");
	_gr->addBin(M_ChicoAtaque5, rec_folder+"boyAttack5.bin");
	_gr->addBin(M_ChicoAtaque6, rec_folder+"boyAttack6.bin");
	_gr->addBin(M_ChicoAtaque7, rec_folder+"boyAttack7.bin");
	_gr->addBin(M_ChicoAtaque8, rec_folder+"boyAttack8.bin");
	_gr->addBin(M_ChicoAtaque9, rec_folder+"boyAttack9.bin");
	_gr->addBin(M_ChicoAtaque10, rec_folder+"boyAttack10.bin");
	_gr->addBin(M_ChicoAtaque11, rec_folder+"boyAttack11.bin");
	_gr->addBin(M_ChicaAtaque, rec_folder+"fleurAttack.bin");
	_gr->addBin(M_Pistola, rec_folder+"pistola.bin");
	_gr->addBin(M_GengibreAtaque1, rec_folder+"gengAttack1.bin");
	_gr->addBin(M_GengibreAtaque2, rec_folder+"gengAttack2.bin");
	_gr->addBin(M_GengibreAtaque3, rec_folder+"gengAttack3.bin");
	_gr->addBin(M_GengibreAtaque4, rec_folder+"gengAttack4.bin");
	_gr->addBin(M_GengibreAtaque5, rec_folder+"gengAttack5.bin");
	_gr->addBin(M_GengibreAtaque6, rec_folder+"gengAttack6.bin");
	_gr->addBin(M_GengibreAtaque7, rec_folder+"gengAttack7.bin");
	_gr->addBin(M_GengibreAtaque8, rec_folder+"gengAttack8.bin");
	_gr->addBin(M_OsoAtaque1, rec_folder+"osoAttack1.bin");
	_gr->addBin(M_OsoAtaque2, rec_folder+"osoAttack2.bin");
	_gr->addBin(M_OsoAtaque3, rec_folder+"osoAttack3.bin");
	_gr->addBin(M_OsoAtaque4, rec_folder+"osoAttack4.bin");
	_gr->addBin(M_OsoAtaque5, rec_folder+"osoAttack5.bin");
	_gr->addBin(M_OsoAtaque6, rec_folder+"osoAttack6.bin");
	_gr->addBin(M_OsoAtaque7, rec_folder+"osoAttack7.bin");
	_gr->addBin(M_OsoAtaque8, rec_folder+"osoAttack8.bin");
*/

	cout << "[InterfazGraphics]Modelos cargados" << endl;
	cout <<Timer::getTimeElapsed() << endl;
}

InterfazGraphics::~InterfazGraphics() {
	delete _mg;
	_mg = NULL;

	delete _HUD;
	_HUD = NULL;

	delete _World3D;
	_World3D = NULL;

	delete _gr;
	_gr = NULL;

	delete _ventana;
	_ventana = NULL;
}

void
InterfazGraphics::Render() {
	if(_ventana->isResizing()){
		_ventana->ResizeViewport();
		ResizeCameras(_ventana->getWidth(), _ventana->getHeight());
	}

	if(Timer::getTimeElapsed()-tiempoMostradoCentral>2000)
	{
		visibilidadTextoCentral(false);
	}


	//DEBUG
	ostringstream fps;
	fps << "FPS: " << _ventana->getFramesPerSecond();
	_FPS->setTexto(fps.str());
	//FIN DEBUG

	_mg->Render();
}

void
InterfazGraphics::ResizeCameras(float width, float height) {
	_World3D->Resize(width, height);
	_HUD->Resize(width, height);
}

Ventana*
InterfazGraphics::getVentana(){
	return _ventana;
}

int
InterfazGraphics::Seleccion(){
	/*Raton mouse(_ventana);*/
	Vector2 pos = Raton::getPosition(_ventana);
	return _mg->seleccion(pos.getX(), pos.getY());
}

HUD*
InterfazGraphics::getHUD(){
	return _HUD;
}

World3D*
InterfazGraphics::getWorld3D(){
	return _World3D;
}

void candy::InterfazGraphics::visibilidadTextoCentral(bool vis)
{
	_MsgCentral->setActive(vis);
	tiempoMostradoCentral = Timer::getTimeElapsed();
}



void candy::InterfazGraphics::setTextoCentral1(string tex)
{
	_TextoCentral1->setTexto(tex);
}

void candy::InterfazGraphics::setTextoCentral2(string tex)
{
	_TextoCentral2->setTexto(tex);
}

