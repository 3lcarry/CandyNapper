#pragma once
#include "OpenGL.h"

#include <iostream>
using namespace std;

#include <string>



#include <map>
//#include "FTGL/ftgl.h"
//Incluimos la FTGL, para poder cargar Fuentes
#include "FTGL/ftgl.h"
//Includes para las imagenes de la sfml 
#include "SFML/Graphics.hpp"

//Include para manejar los 3ds
#include "load3ds.h"

//Include para poder parsear XML para configurar el gestor de Recursos
#include "ParserGestorRecursos.h"

const int MESHSIZE = 300000;
typedef struct{
	int size;
	float* mesh;
} BinMesh;

class GestorRecursos
{
public:

    enum Primitiva{
        E_Esfera = 1000,
        E_Cubo = 1001,
        E_Cono = 1002,
        E_Toroide = 1003,
        E_Mono = 1004,
        E_Cilindro = 1005
    };
    
    enum Fuentes{
    	E_Anarchy = 1000
    };

    enum guiTextures{
        guiTex_Button = 1006,
        guiTex_RButton = 1007,
        guiTex_RButton_a = 1008
    };

    enum Shaders{
    	S_Phong = 1000,
    	S_CellShading = 1000
    };
	~GestorRecursos();

	/**
	 * Añade una fuente al gestor de recursas (soporta .ttf , .otf ...)
	 * @param id id para referisre a la fuente
	 * @param ruta ruta donde se encuentra la fuente
	 * @return	si se ha cargado bien
	 */
	bool addFont(int id,string ruta);
	/**
	*Carga un 3ds, y genera una display list
	*/
	bool add3ds(int id, string ruta);

	/**
	 * Carga un modelo en formato binario
	 * @param id ID del modelo
	 * @param ruta Ruta del modelo
	 * @return TRUE si se ha cargado bien
	 */
	bool addBin(int id, string ruta);

	/**
	*	Carga un Obj, y crea una display list
	*	Esta en investigaci�n NO USAR
	*/
	bool addOjb(int id, string ruta);
	/**
	*	Carga una textura, en principio no importa el tipo de imagen .jpg, .png, ...
	*/
	bool addTextura(int id, string ruta);
	/**
	*	Devuelve la display list del objeto indicado
	*	si no existe -1
	*/        
	int getDisplayList(int id);
	/**
	*	Devuelve la Textura indicado
	*	si no existe -1
	*/
	int getTextura(int id);

	/**
	 * Devuelve la fuente indicada
	 * @param id
	 * @return
	 */
	FTGLPixmapFont* getFont(int id);

	/**
	*	Carga el Gestor de Recursos desde un fichero
	*/
	bool configureFromFile(string ruta);

	/**
	 * Clase Singleton
	 * @return Obtiene la intancia de la clase, si no existe la crea
	 */
	static GestorRecursos* getInstancia();

	/**
	 * Devuelve el numero de luces actual
	 * @return Numero de luces
	 */
	int getNumLuces();

	/**
	 * A�ade una luz a la "cuenta" de luces
	 */
	void addLuz();

	/**
	 * Get ruta de la fuente
	 */
	string getFontPaht(int id);

	/**
	 * Carga un Shader en memoria
	 *
	 * @param id id del Shader
	 * @param vertexShader ruta al vertex Shader
	 * @param fragmentShader ruta al fragment Shader
	 * @return si se ha cargado correctamente
	 */
	bool loadShader(int id, string vertexShader, string fragmentShader);

	/**
	 * Activamos el shader indicado
	 * @param id shader que queremos activar
	 * @return
	 */
	bool activateShader(int id);

	/**
	 * Desactivamos el Shader
	 * @param id shader que queremos desactivar
	 * @return
	 */
	bool desactivateShader(int id);

private:
	/* Privado para ser singleton*/
	GestorRecursos();
	/**
	 * El gestor de recursos permite almacenar fuentes utilizando la libreria
	 * FTGL y las almacenara mediante Fuentes Texturizadas, para poder utilizarlas
	 * devolvera un objeto FTGLTextureFont, aunque con el motro gráfico simplemente
	 * se podra utilizar mediante la clase TEXT la cual se encargara de especificar
	 * color, tamaño y texto que queremos mostrar y mediante las transformación se
	 * pondran en la posicion indicada
	 */
	map<int, FTGLPixmapFont*> fuentes;
	map<int, string> ruta_fuentes;
	map<int, unsigned int> displayList;
	map<int, unsigned int> texturas;
	map<int, unsigned int>::iterator it;
	map<int, FTGLPixmapFont*>::iterator it_fuentes;
	map<int, string>::iterator it_fuentes_ruta;

	map<int, sf::Shader*> _shaders;
	map<int, sf::Shader*>::iterator _itShaders;

	int numDisplayList;
	int numTexturas;
	int numLuces;
	int numFuentes;

	static GestorRecursos* gestor;

	ParserGestorRecursos* parser;
};

