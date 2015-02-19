/*
 * InOut.cpp
 *
 *  Created on: 04/11/2011
 *      Author: kaseyo
 */

#include "Ventana.h"
#include "OpenGL.h"

namespace candy{

const string Ventana::NombrePorDefecto = "Mi Ventana";

Ventana::Ventana(float ancho, float alto, string nombre){
	//Modificamos algunos parametros de la Window
	c_window.EnableKeyRepeat(false);
	c_window.EnableVerticalSync(true);
	//c_window.SetFramerateLimit(60.0);
	c_titulo = nombre;

	//Ponemos a false los eventos relativos eventos a la ventana
	c_close = false;
	c_resize = false;
	c_pause = false;
	c_fullscreen = false;
	c_switchfullscreen = false;
	c_focus = true;
	c_fps = c_reloj.Restart().AsSeconds();

	crearVentana(ancho, alto);
}

Ventana::Ventana(string nombre){
	//Modificamos algunos parametros de la Window
	c_window.EnableKeyRepeat(false);
	//c_window.EnableVerticalSync(true);
	//c_window.SetFramerateLimit(60.0); A topee!!
	c_titulo = nombre;

	//Ponemos a false los eventos relativos eventos a la ventana
	c_close = false;
	c_resize = false;
	c_pause = false;
	c_fullscreen = false;
	c_switchfullscreen = false;
	c_focus = true;
	c_fps = c_reloj.Restart().AsMilliseconds();

	crearVentana();
}

Ventana::~Ventana(){

}

Ventana::Ventana(const Ventana & cop)
{
	copiarDesde(cop);
}



Ventana&
Ventana::operator =(const Ventana & cop)
{
	if(&cop != this){
		this->~Ventana();
		copiarDesde(cop);
	}

	return *this;
}



void
Ventana::crearVentana(float width, float height)
{
	/* Get the better videomode */
	sf::VideoMode escritorio = sf::VideoMode::GetDesktopMode();

	if(width > escritorio.Width){
		width = escritorio.Width;
	}

	if(height > escritorio.Height){
		height = escritorio.Height;
	}

	sf::VideoMode mejor_modo = sf::VideoMode(width, height, escritorio.BitsPerPixel);


	c_window.Create(mejor_modo, c_titulo, sf::Style::Default, sf::ContextSettings(32));
}

void
Ventana::crearVentana(){
	/* Get the better videomode */
	sf::VideoMode mejor_modo = sf::VideoMode::GetDesktopMode();

	c_window.Create(mejor_modo, c_titulo, sf::Style::Default, sf::ContextSettings(32));
}



void
Ventana::switchFullscreen()
{
	if(!c_switchfullscreen){
		c_switchfullscreen = true;
		/* Get the better videomode for fullscreen*/
		vector<sf::VideoMode> modos_fullscreen = sf::VideoMode::GetFullscreenModes();
		sf::VideoMode mejor_modo;

		/* Suponemos que el primer elemento es el mejor videmode */
		if(!modos_fullscreen.empty()){
			mejor_modo = modos_fullscreen[0];
		}

		c_window.Create(mejor_modo, c_titulo, sf::Style::Fullscreen);
	}else{
		c_switchfullscreen = false;
		//crearVentana();

		//El fullscreen no va, ni se usa
	}
}

void
Ventana::copiarDesde(const Ventana & cop){
	//La ventana es Non-copyable
}

void
Ventana::Update(){
	sf::Event evento;

	/* Vacia la cola de eventos y trato algunos (como los relativos a la ventana) */
	while(c_window.PollEvent(evento)){
		switch(evento.Type){
			case sf::Event::Closed:
				/* Manejo un evento closing */
				c_close = true;
			break;

			case sf::Event::TextEntered:
				char caracter_introd;
				if(evento.Text.Unicode < 128 && c_consola.IsActive()){ //Es ASCII
					if(evento.Text.Unicode >= 32){ //Es imprimible
						caracter_introd = (char)(evento.Text.Unicode);
						c_consola.AddChar(caracter_introd);
					}else if(evento.Text.Unicode == 13){ //Es el retorno de carro
						c_consola.CommandCompleted();
					}else if(evento.Text.Unicode == 8){ //Es la tecla de borrar
						c_consola.RmChar();
					}
				}
			break;

			case sf::Event::KeyPressed:
				switch(evento.Key.Code){
					case sf::Keyboard::Escape :
						c_close = true;
					break;

					case sf::Keyboard::P :
						if(c_pause){
							if(!c_consola.IsActive()){
								c_pause = false;
							}else{
								c_consola.HideConsole();
							}
						}else{
							if(!c_consola.IsActive()){
								c_pause = true;
							}
						}
					break;

					case sf::Keyboard::F : //Evento Fullscreen (anulamos el resize)
						c_fullscreen = true;
					break;

					case sf::Keyboard::LAlt : //Evento abrir (o cerrar) consola
						if(c_consola.IsActive()){
							c_consola.HideConsole();
						}else{
							c_consola.ShowConsole();
						}
					break;

#ifdef __APPLE__
					case sf::Keyboard::Return: //Enter, completar consola
						if(c_consola.IsActive()){
							c_consola.CommandCompleted();
						}
					break;

					case sf::Keyboard::Back: //Borrar, borrar consola
						if(c_consola.IsActive()){
							c_consola.RmChar();
						}
					break;
#endif

					default:
						//No se contemplan mas teclas
					break;
				}
			break;

			case sf::Event::Resized:
				/* Manejo un evento de resizing */
				c_resize = true;
			break;

			case sf::Event::LostFocus:
				c_focus = false;
			break;

			case sf::Event::GainedFocus:
				c_focus = true;
			break;

			default:
				//No se contemplan mas tipos de eventos
			break;
		}
	}
}

bool
Ventana::isClosing(){
	bool resultado = false;
	if(c_close){
		c_close = false;
		resultado = true;
	}

	return resultado;
}

bool
Ventana::isResizing(){
	bool resultado = false;
	if(c_resize){
		c_resize = false;
		resultado = true;
	}

	return resultado;
}
/*
bool
Ventana::isPause(){
	return (c_pause || c_consola.IsActive());
}
*/

bool
Ventana::isFullScreen(){
	bool resultado = false;
	if(c_fullscreen){
		c_fullscreen = false;
		c_resize = false;
		resultado = true;
		switchFullscreen();
	}

	return resultado;
}

float
Ventana::getFramesPerSecond(){
	return (1000.0/(float)c_fps);
}

float
Ventana::getWidth(){
	return c_window.GetWidth();
}

float
Ventana::getHeight(){
	return c_window.GetHeight();
}

void
Ventana::Display(){
	c_window.Display();
	c_fps = c_reloj.Restart().AsMilliseconds();
}

Console*
Ventana::getConsolePtr(){
	return &c_consola;
}

void
Ventana::ResizeViewport(){
	glViewport(0, 0, getWidth(), getHeight());
}

void
Ventana::ShowMouse(bool show){
	c_window.ShowMouseCursor(show);
}

bool
Ventana::isFocused(){
	return c_focus;
}

}
