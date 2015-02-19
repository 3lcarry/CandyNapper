/*
 * StateGameOver.cpp
 *
 *  Created on: 24/05/2012
 *      Author: esteve
 */

#include "StateGameOver.h"
#include "StatePlay.h"

#include "InterfazGraphics.h"
#include "InterfazPhysics.h"
#include "EntityManager.h"
#include "Application.h"

#include "Teclado.h"
#include "StateMachineGame.h"

#include "Menu.h"

namespace candy
{

StateGameOver::StateGameOver()
: State(StateMachineGame::GameOver)
{
	_irMenuPrincipal = false;
	_salir = false;
	_iGrafica = InterfazGraphics::getInstance();

}

StateGameOver::~StateGameOver() {
	// TODO Auto-generated destructor stub
}

void StateGameOver::Transition()
{
	if(_iGrafica->getVentana()->isClosing() || _salir){
		SM->ChangeState(StateMachineGame::Exit);
	}
	else if (_irMenuPrincipal) {
		_iGrafica->visibilidadMenuPrincipal(true);
		_iGrafica->visibilidadHUD(false);
		_iGrafica->visibilidadMenuIngame(false);
		_iGrafica->visibilidadWorld(false);
		_iGrafica->visibilidadMenuFinish(false);

		InterfazMusic::getInstancia()->desactivarMusicaFondo();
		InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Menu);
		SM->ChangeState(StateMachineGame::Menu);
	}
	else if(_Reintentar){
		_iGrafica->visibilidadMenuPrincipal(false);
		_iGrafica->visibilidadHUD(true);
		_iGrafica->visibilidadMenuIngame(false);
		_iGrafica->visibilidadWorld(false);
		_iGrafica->visibilidadMenuFinish(false);
		_iGrafica->visibilidadWorld(true);

		if(CandyNapper::getInstancia()->isPartidaRapida)
		{
			CandyNapper::getInstancia()->Init();
			((Application*)SM)->createRandomMap();
		}else{
			string level = CandyNapper::getInstancia()->getActualLevel();
			CandyNapper::getInstancia()->Init();
			((Application*)SM)->LoadFromXML(level);
		}
		InterfazMusic::getInstancia()->desactivarMusicaFondo();
		SM->ChangeState(StateMachineGame::Play);
	}
}

void StateGameOver::Execute()
{
	_Reintentar = false;
	_irMenuPrincipal = false;
	_salir = false;

	_iGrafica->getVentana()->Update();


	if (Raton::isPressed(Raton::Izquierdo)) {
		int seleccion = _iGrafica->seleccionMenuFinish();

		if (seleccion == Menu::I_Reintentar)
			_Reintentar = true;

		if (seleccion == Menu::I_MenuPrincipal)
			_irMenuPrincipal = true;

		if(seleccion == Menu::I_Salir)
			_salir = true;

	}

	//InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Menu);
	_iGrafica->Render();
	_iGrafica->getVentana()->Display();
}


}
