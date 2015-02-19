/*
 * InitState.cpp
 *
 *  Created on: 22/11/2011
 *      Author: kaseyo
 */

#include "StateMenu.h"
#include "StateMachineGame.h"
#include "InterfazGraphics.h"
#include "Menu.h"
#include "Application.h"

#include "Timer.h"

using namespace candy;

StateMenu::StateMenu() :
		State(StateMachineGame::Menu)
{
	_pasarJuego = false;
	_salir = false;
	_iGrafica = InterfazGraphics::getInstance();
	_iGrafica->visibilidadHUD(false);
	_iGrafica->visibilidadMenuPrincipal(true);
	_iGrafica->visibilidadWorld(false);
	_partidaRapida = false;
	_cargar = false;
}

StateMenu::~StateMenu() {

}

void StateMenu::Transition() {
	Application* owner = ((Application*)SM);

	if(_iGrafica->getVentana()->isClosing() || _salir){
		SM->ChangeState(StateMachineGame::Exit);
	}

	if (_pasarJuego) {
		SM->ChangeState(StateMachineGame::Play);
		_iGrafica->visibilidadHUD(true);
		_iGrafica->visibilidadMenuPrincipal(false);
		_iGrafica->visibilidadWorld(true);

		string level1 = (string)CANDYROOT+"/resources/level1.xml";
		CandyNapper::getInstancia()->setActualLevel(level1);
		cout << "[StateMenu] Level1: " << level1 << endl;
		CandyNapper::getInstancia()->Init();
		owner->LoadFromXML(level1);

		InterfazGraphics::getInstance()->visibilidadTextoCentral(false);
		InterfazPathfinding::getInstance()->GenerarGrafo();
		InterfazMusic::getInstancia()->desactivarMusicaFondo();
		InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Juego);
		InterfazMusic::getInstancia()->setVolumenMusicaFondo(60);
		_pasarJuego = false;
		CandyNapper::getInstancia()->isPartidaRapida = false;

	}

	if(_partidaRapida)
	{
		SM->ChangeState(StateMachineGame::Play);
		_iGrafica->visibilidadHUD(true);
		_iGrafica->visibilidadMenuPrincipal(false);
		_iGrafica->visibilidadWorld(true);

		CandyNapper::getInstancia()->Init();
		owner->createRandomMap();

		InterfazGraphics::getInstance()->visibilidadTextoCentral(false);
		InterfazPathfinding::getInstance()->GenerarGrafo();
		InterfazMusic::getInstancia()->desactivarMusicaFondo();
		InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Juego);
		InterfazMusic::getInstancia()->setVolumenMusicaFondo(60);
		_partidaRapida = false;
		CandyNapper::getInstancia()->isPartidaRapida = true;
	}

	if(_cargar)
	{
		string fichero = (string)CANDYROOT+"/resources/saved.xml";
		ifstream f;
		f.open(fichero.c_str(),ios::in);
		if(f.is_open()){
			f.close();

			CandyNapper::getInstancia()->isPartidaRapida = false;
			CandyNapper::getInstancia()->setActualLevel(fichero);
			SM->ChangeState(StateMachineGame::Play);
			_iGrafica->visibilidadHUD(true);
			_iGrafica->visibilidadMenuPrincipal(false);
			_iGrafica->visibilidadWorld(true);

			CandyNapper::getInstancia()->Init();
			owner->LoadFromXML(fichero);

			InterfazGraphics::getInstance()->visibilidadTextoCentral(false);
			InterfazPathfinding::getInstance()->GenerarGrafo();
			InterfazMusic::getInstancia()->desactivarMusicaFondo();
			InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Juego);
			InterfazMusic::getInstancia()->setVolumenMusicaFondo(60);

		}
		else
		{
			//Mostrar Mensaje Central
			cout << "[State Menu.cpp]  No hay ninguna partida guardada...." << endl;
			InterfazGraphics::getInstance()->visibilidadTextoCentral(true);
			InterfazGraphics::getInstance()->setTextoCentral1("  No existe ninguna partida guardada");
			InterfazGraphics::getInstance()->setTextoCentral2("      Inicie una partida nueva");
		}

		_cargar = false;

	}
}

void StateMenu::Execute() {
	_pasarJuego = false;
	_salir = false;
	_iGrafica->getVentana()->Update();

	//Mirar Boton y hacer seleccion
	if (Raton::isPressed(Raton::Izquierdo)) {
		int seleccion = _iGrafica->seleccionMenu();

		if (seleccion == Menu::P_ComenzarPartida)
			_pasarJuego = true;

		if (seleccion == Menu::P_Salir)
			_salir = true;

		if(seleccion == Menu::P_Cargar)
			_cargar = true;

		if(seleccion == Menu::P_PartidaRapida)
			_partidaRapida = true;
	}

	InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Menu);
	_iGrafica->Render();
	_iGrafica->getVentana()->Display();
}


