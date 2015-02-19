/*
 * StateWin.cpp
 *
 *  Created on: 25/05/2012
 *      Author: esteve
 */

#include "StateWin.h"

#include "Menu.h"

namespace candy {

StateWin::StateWin()
	:State(StateMachineGame::Win)
{
	_iGrafica = InterfazGraphics::getInstance();
	_irMenuPrincipal = false;
}

StateWin::~StateWin() {
	// TODO Auto-generated destructor stub
}


void StateWin::Transition(){
	if (_irMenuPrincipal) {
		_iGrafica->visibilidadMenuPrincipal(true);
		_iGrafica->visibilidadHUD(false);
		_iGrafica->visibilidadMenuIngame(false);
		_iGrafica->visibilidadWorld(false);
		_iGrafica->visibilidadMenuFinish(false);
		_iGrafica->visibilidadMenuWin(false);

		InterfazMusic::getInstancia()->desactivarMusicaFondo();
		InterfazMusic::getInstancia()->activarMusicaFondo(InterfazMusic::Menu);
		SM->ChangeState(StateMachineGame::Menu);
	}
}

void StateWin::Execute() {
	_irMenuPrincipal = false;
	//_iGrafica->getVentana()->ShowMouse(true);

	_iGrafica->getVentana()->Update();

	if (Raton::isPressed(Raton::Izquierdo)) {
		//std::cout << "[StateWin.cpp] Click izquierdo" << std::endl;
		int seleccion = _iGrafica->seleccionMenuWin();

		if (seleccion == Menu::I_MenuPrincipal)
			_irMenuPrincipal = true;
	}

	_iGrafica->Render();
	_iGrafica->getVentana()->Display();
}

}
