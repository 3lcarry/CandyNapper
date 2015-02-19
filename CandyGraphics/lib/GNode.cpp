/*
 * GraphicalTree.cpp
 *
 *  Created on: 06/02/2012
 *      Author: gustavo
 */

#include "GNode.h"

#include "Light.h"
#include "Camera.h"
#include "Director.h"
#include "Transformation.h"
#include "Shape.h"
#include "Model.h"
#include "Text.h"
#include "Line.h"
#include "Box.h"
#include "Plane.h"
#include "guiButton.h"
#include "guiRButton.h"
#include "guiGBox.h"
#include "guiSlide.h"
#include "AnimatedTransformation.h"
#include "Particles.h"

#include "GestorRecursos.h"

#include "GTree.h"

using namespace candy;

////////////////////////////////////////////////////////////
/////////////////////// GNODE //////////////////////////////
////////////////////////////////////////////////////////////

GNode::GNode(GNodeType tipo){
	id = -1;
	this->tipo=tipo;
	this->activo = true;
	destroy = false;
	_light = true;
	_depth = true;
}

GNode::~GNode(){

    if(!hijos.empty()){
        list<GTree*>::iterator it;

        for(it=hijos.begin(); it!=hijos.end(); it++){

            if((*it)!=NULL)
                delete (*it);

            (*it)=NULL;

        }
    }

    hijos.clear();
}

GNode::GNode(const GNode& node){
    copiarDesde(node);
}

GNode& GNode::operator =(const GNode& node){
	if(this!=&node){
            this->~GNode();
            copiarDesde(node);
	}

	return *this;
}

void GNode::setID(int id){
	this->id = id;
}
int GNode::getID(){
	return id;
}

Particles* candy::GNode::addParticles(int num)
{
	GTree* tree=new GTree();

	candy::Particles* t=new Particles(num);

	tree->raiz=t;
	hijos.push_back(tree);

	return t;
}

AnimatedTransformation *candy::GNode::addAnimatedTransformation()
{
	GTree* tree=new GTree();

	candy::AnimatedTransformation* t=new AnimatedTransformation();

	tree->raiz=t;
	hijos.push_back(tree);

	return t;
}

void
GNode::copiarDesde(const GNode& cop){
    tipo=cop.tipo;
    activo=cop.activo;

    list<GTree*>::const_iterator it;
    for(it = cop.hijos.begin(); it != cop.hijos.end(); it++){
    	hijos.push_back(new GTree(*(*it)));
    }
}

void GNode::RenderHijos(bool seleccion){
    list<GTree*>::iterator it;

    for(it=hijos.begin(); it!=hijos.end(); it++){
        if((*it)->isDestroy()){
        	//Si el nodo esta marcado para destruirlo
        	delete (*it);
        	it = hijos.erase(it);
        }else{
        	(*it)->Render(seleccion);
        }
    }
}

Transformation* GNode::addTransformation(){

	GTree* tree=new GTree();

	candy::Transformation* t=new Transformation();
	tree->raiz=t;
	hijos.push_back(tree);

	return t;
}

Camera* GNode::addCamera(float near, float far, float aspectRatio, float fov){
	GTree* tree=new GTree();
    candy::Camera* c = new Camera(near,far,aspectRatio,fov, true);
	tree->raiz=c;
	hijos.push_back(tree);

	return c;
}

Camera* GNode::addCamera2D(float left, float right, float bottom, float top){
	GTree* tree = new GTree();
	candy::Camera* c2D = new Camera(left, right, bottom, top, false);
	tree->raiz = c2D;
	hijos.push_back(tree);

	return c2D;
}

Director* GNode::addDirector(Vector3 ojo, Vector3 direccion, Vector3 up){
	GTree* tree = new GTree();
	candy::Director* dir = new Director(ojo, direccion, up);
	tree->raiz = dir;
	hijos.push_back(tree);

	return dir;
}

Light* GNode::addLight(Vector3 posicion, Vector3 ambiente, Vector3 difusa, Vector3 especular, int numLuz){
	candy::Light* l = NULL;

	GestorRecursos* res = GestorRecursos::getInstancia();

	if(res->getNumLuces() <= candy::Light::MAX_LIGHTS){
		GTree* tree=new GTree();
		l=new Light(posicion,ambiente,difusa,especular,numLuz);
		tree->raiz=l;
		hijos.push_back(tree);

		res->addLuz();
	}

	return l;
}

Model* GNode::addModel(int idModelo, int textura){
	GTree* tree=new GTree();
    candy::Model* m=new Model(idModelo, textura);
	tree->raiz=m;
	hijos.push_back(tree);

	return m;
}

Shape* GNode::addShape(int numLados, Color color){

	GTree* tree=new GTree();
    candy::Shape* p=new Shape(numLados,color);
	tree->raiz=p;
	hijos.push_back(tree);

	return p;
}

Text* GNode::addText(){
	GTree* tree = new GTree();
	candy::Transformation* trans = new Transformation();
	candy::Text* t = new Text();


	tree->raiz = trans;
	trans->addGNode(t);
	t->setTransformation(trans);
	hijos.push_back(tree);

	return t;
}

Line* GNode::addLine(Vector3 punto_final, Color color, bool punteada){
	GTree* tree = new GTree();
	candy::Line* l = new Line(punto_final, color, punteada);
	tree->raiz = l;
	hijos.push_back(tree);

	return l;
}

Line* GNode::addLine(Vector3 punto_inicial, Vector3 punto_final, Color color, bool punteada){
	GTree* tree = new GTree();
	candy::Line* l = new Line(punto_inicial, punto_final, color, punteada);
	tree->raiz = l;
	hijos.push_back(tree);

	return l;
}

Box* GNode::addBox(){
	GTree* tree = new GTree();
	candy::Box* b = new Box();
	tree->raiz = b;
	hijos.push_back(tree);

	return b;
}

Box*
GNode::addBox(int idFront, int idBack, int idTop, int idBottom, int idLeft, int idRight){
	GTree* tree = new GTree();
	candy::Box* b = new Box(idFront, idBack, idTop, idBottom, idLeft, idRight);
	tree->raiz = b;
	hijos.push_back(tree);

	return b;
}

Plane*
GNode::addPlane(){
	GTree* tree = new GTree();
	candy::Plane* p = new Plane();
	tree->raiz = p;
	hijos.push_back(tree);

	return p;
}

guiButton* GNode::addButton(float ancho, float alto, string texto){
    GTree* tree = new GTree();
    candy::guiButton* b = new guiButton(ancho,alto,texto);
    tree->raiz = b;
    hijos.push_back(tree);
    
    return b;
}

guiRButton* GNode::addRButton(string texto, bool check){
    GTree* tree = new GTree();
    candy::guiRButton* rb = new guiRButton(texto, check);
    tree->raiz = rb;
    hijos.push_back(tree);
    
    return rb;
}

guiGBox* GNode::addGBox(float alto, float ancho){
    GTree* tree = new GTree();
    candy::guiGBox* gb = new guiGBox(alto,ancho);
    tree->raiz = gb;
    hijos.push_back(tree);
    
    return gb;
}

guiSlide* GNode::addSlide(float min, float max, float freq){
    GTree* tree = new GTree();
    candy::guiSlide* gs = new guiSlide(min,max,freq);
    tree->raiz = gs;
    hijos.push_back(tree);
    
    return gs;
}

GNode* GNode::addGNode(GNode* nodo){
	if(nodo != NULL){
		GTree* tree = new GTree();
		tree->raiz = nodo;
		hijos.push_back(tree);
	}

	return nodo;
}

void GNode::setActive(bool active){
	activo = active;
}

bool GNode::isActive(){
	return activo;
}

void GNode::setDestroy(bool dest){
	destroy = dest;
}

bool GNode::isDestroy(){
	return destroy;
}

bool GNode::isLight(){
	return _light;
}

void GNode::setLight(bool light){
	_light = light;
}

bool
GNode::isDepth(){
	return _depth;
}

void
GNode::setDepth(bool depth){
	_depth = depth;
}

void
GNode::rmChilds(){
    if(!hijos.empty()){
        list<GTree*>::iterator it;

        for(it=hijos.begin(); it!=hijos.end(); it++){

            if((*it)!=NULL)
                delete (*it);

            (*it)=NULL;

        }
    }

    hijos.clear();
}
