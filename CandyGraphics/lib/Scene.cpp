/*
 * Scene.cpp
 *
 *  Created on: 09/02/2012
 *      Author: kaseyo
 */

#include "Scene.h"

#include "GTree.h"

namespace candy {

Scene::Scene()
	:GNode(GNode::E_Scene)
{
	c_pila = MatrixStack::getInstance();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

Scene::~Scene() {
	delete c_pila;
}

Scene::Scene(const Scene & cop)
	:GNode(cop)
{
	copiarDesde(cop);
}

Scene&
Scene::operator =(const Scene & cop){
	if(this != &cop){
		this->~Scene();
		GNode::copiarDesde(cop);
		copiarDesde(cop);
	}

	return *this;
}

void
Scene::Render(bool seleccion){
#ifdef _DEBUG_
	cout << "Renderizo la ESCENA" << endl;
	cout << "Renderizo los hijos de la ESCENA(" << hijos.size() << ")" << endl;
#endif
	RenderHijos(seleccion);
#ifdef _DEBUG_
	cout << "Vuelvo a la ESCENA" << endl;
#endif
}

void
Scene::copiarDesde(const Scene & cop){

}

void
Scene::loadIdentitys(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//c_pila->Init();
}

void
Scene::RenderHijos(bool seleccion){
	list<GTree*>::iterator it;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(it = hijos.begin(); it != hijos.end(); it++){
		if(!seleccion){
			loadIdentitys();
		}
		(*it)->Render(seleccion);
	}
}

} /* namespace candy */
