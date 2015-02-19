#include "GestorRecursos.h"
#include <fstream>

GestorRecursos* GestorRecursos::gestor = NULL;

GestorRecursos *GestorRecursos::getInstancia()
{
	if(gestor == NULL){
		gestor = new GestorRecursos();
	}
	return gestor;
}

bool GestorRecursos::addFont(int id, string ruta)
{
	bool resultado = false;
	FTGLPixmapFont* aux = new FTGLPixmapFont(ruta.c_str());

	it_fuentes = fuentes.find(id);

	if(!aux->Error() && it_fuentes == fuentes.end()){
		numFuentes++;
		resultado = true;
		fuentes.insert(pair<int, FTGLPixmapFont*>(id,aux));
		ruta_fuentes.insert(pair<int, string>(id,ruta));
	}

	return resultado;
}



FTGLPixmapFont *GestorRecursos::getFont(int id)
{
	FTGLPixmapFont* resul = NULL;
	it_fuentes = fuentes.find(id);
	if(it_fuentes != fuentes.end()){
		resul = it_fuentes->second;
	}
	return resul;
}

string GestorRecursos::getFontPaht(int id)
{
	string resul = "";
	it_fuentes_ruta = ruta_fuentes.find(id);
	if(it_fuentes_ruta != ruta_fuentes.end()){
		resul = it_fuentes_ruta->second;
	}
	return resul;
}

bool GestorRecursos::loadShader(int id, string vertexShader, string fragmentShader)
{
	bool correcto = true;
	sf::Shader *shader = new sf::Shader();
	correcto = shader->LoadFromFile(vertexShader,fragmentShader);

	if(correcto){
		cout << "[GestorRecursos.cpp] Cargado el shader " << vertexShader << " , " << fragmentShader << endl;
		_itShaders = _shaders.find(id);
		if(_itShaders == _shaders.end()){
			_shaders.insert(pair<int,sf::Shader*>(id,shader));
		}else{
			correcto = false;
		}
	}

	return correcto;
}

bool GestorRecursos::activateShader(int id)
{
	bool correcto = true;
	_itShaders = _shaders.find(id);
	if(_itShaders != _shaders.end()){
		_itShaders->second->Bind();
	}else{
		correcto = false;
	}
	return correcto;
}

bool GestorRecursos::desactivateShader(int id)
{
	bool correcto = true;
	_itShaders = _shaders.find(id);
	if(_itShaders != _shaders.end()){
		_itShaders->second->Unbind();
	}else{
		correcto = false;
	}
	return correcto;
}

GestorRecursos::GestorRecursos()
{
	numTexturas =0;
	numDisplayList =0;
	parser = NULL;
	parser = new ParserGestorRecursos(this);
	numLuces = 0;
	string croot=CANDYGRAPHICSROOT;

	add3ds(GestorRecursos::E_Esfera,croot+"esfera.3ds");
	add3ds(GestorRecursos::E_Cubo,croot+"cubo.3ds");
	add3ds(GestorRecursos::E_Cono,croot+"cono.3ds");
	add3ds(GestorRecursos::E_Toroide,croot+"toroide.3ds");
	add3ds(GestorRecursos::E_Mono,croot+"mono.3ds");
	add3ds(GestorRecursos::E_Cilindro,croot+"cilindro.3ds");

	addTextura(GestorRecursos::guiTex_Button,croot+"boton.jpeg");
	addTextura(GestorRecursos::guiTex_RButton,croot+"botonradio.jpeg");
	addTextura(GestorRecursos::guiTex_RButton_a,croot+"botonradio-a.jpeg");

	addFont(GestorRecursos::E_Anarchy,croot+"AnarchySans.otf");

	//loadShader(GestorRecursos::S_Phong,croot+"Phong.vert",croot+"Phong.frag");
	loadShader(GestorRecursos::S_CellShading,croot+"cel.vert",croot+"cel.frag");
}
 


GestorRecursos::~GestorRecursos()
{
	numTexturas=0;
	numDisplayList=0;
	if(parser != NULL)
		delete parser;
	texturas.clear();
	displayList.clear();
	for(it_fuentes = fuentes.begin();it_fuentes != fuentes.end();it_fuentes++)
		delete(it_fuentes->second);

	for(_itShaders = _shaders.begin(); _itShaders != _shaders.end();_itShaders++)
		delete(_itShaders->second);

	_shaders.clear();
	fuentes.clear();        
}



// Carga un 3ds, y genera una display list
bool GestorRecursos::add3ds(int id, string ruta)
{
	bool resultado = false;
	float* modelo = NULL;
	int numVertices=0;

	it = displayList.find(id);
	if(it == displayList.end()){
		modelo = Load3DS(ruta.c_str(),&numVertices);
		//cout << "[GestorRecursos.cpp] " << ruta << " : " << numVertices * 8 << endl;
		if(modelo != NULL){
			numDisplayList++;
			resultado = true;
			glNewList(numDisplayList,GL_COMPILE);
			glBegin(GL_TRIANGLES);
			for(int i=0;i<numVertices;i++){
				glNormal3fv((float *) & modelo[i << 3]+3);
				glTexCoord2fv((float *) & modelo[i << 3]+6);
				glVertex3fv((float *) & modelo[i << 3]);
			}
			glEnd();
			glEndList();
			free(modelo);

			displayList.insert(pair<int,unsigned int>(id,numDisplayList));
		}
	}

	return resultado;
}

bool
GestorRecursos::addBin(int id, string ruta){
	bool resultado = false;
	float* modelo = NULL;
	int numVertices=0;

	it = displayList.find(id);
	if(it == displayList.end()){
		//BinMesh m;
		ifstream fileIn;
		fileIn.open(ruta.c_str(), ios::binary);
		if(fileIn.is_open()){
			int arraySizeLeido;
			int sizeLeido;
			float* mallaLeido;

			fileIn.read((char*)&arraySizeLeido, sizeof(int));
			fileIn.read((char*)&sizeLeido, sizeof(int));
			mallaLeido = new float[arraySizeLeido];
			fileIn.read((char*)mallaLeido, sizeof(float) * arraySizeLeido);

			fileIn.close();

			//modelo = Load3DS(ruta.c_str(),&numVertices);
			modelo = mallaLeido;
			numVertices = sizeLeido;
			//cout << "[GestorRecursos.cpp] " << ruta << " : " << numVertices * 8 << endl;
			if(modelo != NULL){
				numDisplayList++;
				resultado = true;
				glNewList(numDisplayList,GL_COMPILE);
				glBegin(GL_TRIANGLES);
				for(int i=0;i<numVertices;i++){
					//cout << "hola: " << i << endl;
					glNormal3fv((float *) & modelo[i << 3]+3);
					glTexCoord2fv((float *) & modelo[i << 3]+6);
					glVertex3fv((float *) & modelo[i << 3]);
				}
				glEnd();
				glEndList();
				//free(modelo);

				displayList.insert(pair<int,unsigned int>(id,numDisplayList));
			}
		}else{
			cout << "[GestorRecursos.cpp] ERROR cargando " << ruta << ". El fichero no existe" << endl;
		}
	}

	return resultado;
}



bool GestorRecursos::addOjb(int id, string ruta)
{
	//En investigaci�n
	return false;
}


bool GestorRecursos::addTextura(int id, string ruta)
{
	bool resultado = false;
	sf::Image imagen;
	it = texturas.find(id);
	if(it == texturas.end()){
		if(imagen.LoadFromFile(ruta.c_str())){
			numTexturas++;
			resultado = true;

			unsigned int indiceTextura=0;
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1,&indiceTextura);

			glBindTexture(GL_TEXTURE_2D, indiceTextura);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagen.GetWidth(),imagen.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imagen.GetPixelsPtr());

			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, imagen.GetWidth(),imagen.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, imagen.GetPixelsPtr());

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glDisable(GL_TEXTURE_2D);

			//Insertamos el indice de textura en el map
			texturas.insert(pair<int,unsigned int>(id,indiceTextura));
		}
	}

	return resultado;
}


int GestorRecursos::getDisplayList(int id)
{
	int resultado = -1;
	it = displayList.find(id);
	if(it != displayList.end()){
		resultado = it->second;
	}
	return resultado;
}


int GestorRecursos::getTextura(int id)
{
	int resultado=-1;
	it = texturas.find(id);
	if(it != texturas.end()){
		resultado = it->second;
	}
	return resultado;
}

bool GestorRecursos::configureFromFile(string ruta){
	bool correcto = false;
	if(parser->loadFile(ruta)){
		if(parser->configure()){
			correcto = true;
		}
		parser->closeFile();
	}
	return correcto;
}

int GestorRecursos::getNumLuces(){
	return numLuces;
}

void GestorRecursos::addLuz(){
	numLuces++;
}
