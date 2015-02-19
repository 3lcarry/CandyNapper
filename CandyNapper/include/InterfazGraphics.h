/*
 * Graphics.h
 *
 *  Created on: 19/11/2011
 *      Author: kaseyo
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "CandyGraphics.h"
#include <math.h>
using namespace std;

namespace candy {
	class HUD;
	class World3D;
	class Menu;
/**
 * \addtogroup Graphics
 * @brief Modulo encargado de la gestion de la parte grafica.
 * @{
 */

	/**
	 * @class Graphics
	 * @brief Interfaz especifica del motor grafico
	 * Interfaz del juego con el motor gráfico. Tiene los métodos init(EntityManager) y render(), que renderiza
	 * el escenario.
	 */
	class InterfazGraphics {
	public:
		/**
		 * Enum que guarda las texturas del juego
		 */
		enum TexturasCandy{
			T_FondoMenu,
			T_Metal,
			T_Madera,
			T_SkyFront,
			T_SkyBack,
			T_SkyBottom,
			T_SkyTop,
			T_SkyLeft,
			T_SkyRight,
			T_Osito100,
			T_Osito50,
			T_Suelo,
			T_Chica,
			T_Chico,
			T_Melon,
			T_Algodon,
			T_Chupachups,
			T_Gengibre,
			T_OsoAmarillo,
			T_OsoRojo,
			T_OsoAzul,
			T_OsoVerde,
			T_Tarta,
			T_Botiquin,
			T_Jeringuilla,
			T_Miel,
			T_Espada,
			T_Portal,
			MaxTextures
		};

		/**
		 * Enum que guarda los modelos del juego
		 */
		enum ModelosCandy{
			M_Granero,
			M_Chico,
			M_Chica,
			M_Oso,
			M_OsoMovimiento1,
			M_OsoMovimiento2,
			M_OsoMovimiento3,
			M_OsoMovimiento4,
			M_OsoMovimiento5,
			M_ChicaMovimiento1,
			M_ChicaMovimiento2,
			M_ChicaMovimiento3,
			M_ChicaMovimiento4,
			M_ChicaMovimiento5,
			M_ChicoMovimiento1,
			M_ChicoMovimiento2,
			M_ChicoMovimiento3,
			M_ChicoMovimiento4,
			M_ChicoMovimiento5,
			M_ChicoMovimiento6,
			M_ChicoMovimiento7,
			M_ChicoMovimiento8,
			M_ChicoMovimiento9,
			M_ChicoMovimiento10,
			M_ChicoMovimiento11,
			M_ChicoMovimiento12,
			M_GengibreMovimiento1,
			M_GengibreMovimiento2,
			M_GengibreMovimiento3,
			M_GengibreMovimiento4,
			M_GengibreMovimiento5,
			M_Melon,
			M_Algodon,
			M_Chupachups,
			M_Gengibre,
			M_Tarta,
			M_BotiquinPe,
			M_BotiquinMe,
			M_BotiquinGr,
			M_Jeringuilla,
			M_Miel,
			M_ChicoAtaque1,
			M_ChicoAtaque2,
			M_ChicoAtaque3,
			M_ChicoAtaque4,
			M_ChicoAtaque5,
			M_ChicoAtaque6,
			M_ChicoAtaque7,
			M_ChicoAtaque8,
			M_ChicoAtaque9,
			M_ChicoAtaque10,
			M_ChicoAtaque11,
			M_ChicaAtaque,
			M_Pistola,
			M_Espada,
			M_GengibreAtaque1,
			M_GengibreAtaque2,
			M_GengibreAtaque3,
			M_GengibreAtaque4,
			M_GengibreAtaque5,
			M_GengibreAtaque6,
			M_GengibreAtaque7,
			M_GengibreAtaque8,
			M_OsoAtaque1,
			M_OsoAtaque2,
			M_OsoAtaque3,
			M_OsoAtaque4,
			M_OsoAtaque5,
			M_OsoAtaque6,
			M_OsoAtaque7,
			M_OsoAtaque8,
			M_Portal,
			M_Caja = GestorRecursos::E_Cubo
		};

		/**
		 * Enum que guarda las fuentes del juego
		 */
		enum FuentesCandy{
			F_Anarchy = GestorRecursos::E_Anarchy
		};

		/**
		 * Destructor por defecto
		 */
		~InterfazGraphics();

		/**
		 * Renderiza el motor grafico
		 */
		void Render();

		/**
		 * Devuelve un puntero a la ventana
		 * @return Puntero a la ventana
		 */
		Ventana* getVentana();

		/**
		 * Obtiene un puntero a la instancia actual
		 * @return Puntero a la instancia actual
		 */
		static InterfazGraphics* getInstance();

		/**
		 * Devuelve el HUD
		 * @return Puntero a HUD
		 */
		HUD* getHUD();

		/**
		 * Devuelve un puntero al mundo 3D
		 * @return Puntero a World3D
		 */
		World3D* getWorld3D();

		/**
		 * Devuelve lo que esta seleccionado en pantalla
		 * @return Devuelve el id seleccionado
		 */
		int Seleccion();

		void visibilidadHUD(bool vis);

		void visibilidadWorld(bool vis);

		void visibilidadMenuPrincipal(bool vis);

		int seleccionMenu();

		void visibilidadMenuIngame(bool vis);

		int seleccionMenuIngame();

		void visibilidadMenuFinish(bool vis);

		int seleccionMenuFinish();

		void visibilidadMenuWin(bool vis);

		int seleccionMenuWin();

		void visibilidadMenuCambioNivel(bool vis);

		int seleccionMenuCambioNivel();

		void visibilidadTextoCentral(bool vis);

		void visibilidadMenuGameOver(bool vis);

		int seleccionMenuGameOver();

		void setTextoCentral1(string tex);

		void setTextoCentral2(string tex);

	private:



		/**
		 * Constructor por defecto
		 */
		InterfazGraphics();

		/**
		 * Cambia de tamaño las cameras a un determinado ancho y alto.
		 * @param width Ancho
		 * @param heigth Alto
		 */
		void ResizeCameras(float width, float height);

		/**
		 * Carga todos los recursos que hay en los enum
		 */
		void LoadResources();

		/**
		 * Puntero al motor grafico
		 */
		CandyGraphics* _mg;

		/**
		 * Puntero a ventana (manejador de la ventana)
		 */
		Ventana* _ventana;

		/**
		 * Puntero al gestor de recursos
		 */
		GestorRecursos* _gr;

		/**
		 * Puntero al HUD
		 */
		HUD* _HUD;

		/**
		 * Puntero al mundo 3D
		 */
		World3D* _World3D;

		/**
		 * Puntero al menu principal
		 */
		Menu* _MenuPrincipal;

		/**
		 * Puntero al menu ingame
		 */
		Menu* _MenuIngame;

		Menu* _MenuFinish;

		Menu* _MenuWin;

		/**
		 * "Menu" Cambio nivel
		 */
		Menu* _MenuChangeLevel;

		/**
		 * Menu Game over
		 */
		Menu* _MenuGameOver;

		/**
		 * Menu de partida acabada
		 */
		//Menu* _MenuWin;

		Camera* _MsgCentral;

		Shape* _CuadroCentral;

		Text* _TextoCentral1;

		Text* _TextoCentral2;

		//DEBUG
		Text* _FPS;
		//FIN DEBUG

		/**
		 * Puntero a la instancia actual
		 */
		static InterfazGraphics* _instancia;

		int tiempoMostradoCentral;
	};

} /* namespace candy */
#endif /* GRAPHICS_H_ */
