/*
 * Model.cpp
 *
 *  Created on: 09/02/2012
 *      Author: carrillo
 */

#include "Model.h"

namespace candy {

Model::Model()
:GNode(GNode::E_Model)
{
	idModel = -1;
	texture = -1;
	_shader = -1;
	this->color[0] = 1;
	this->color[1] = 1;
	this->color[2] = 1;
	this->color[3] = 1;
}

Model::Model(int idModel, int textura)
	:GNode(GNode::E_Model)
{
	_shader = -1;
	this->idModel = idModel;
	this->texture = textura;
	this->color[0] = 1;
	this->color[1] = 1;
	this->color[2] = 1;
	this->color[3] = 1;

}

Model::~Model()
{
	idModel = -1;
	texture = -1;
}

Model::Model(const Model& cop)
	:GNode(cop)
{
	copiarDesde(cop);
}

Model & Model::operator =(const Model & o)
{
	if(this != &o){
		this->~Model();
		GNode::copiarDesde(o);
		copiarDesde(o);
	}

	return *this;
}

void Model::copiarDesde(const Model& cop){
	idModel = cop.idModel;
	texture = cop.texture;
}


void Model::Render(bool seleccion) {

	GestorRecursos* g = GestorRecursos::getInstancia();
	int display,t=-1;
	display = g->getDisplayList(idModel);

	if(texture != -1){
		t = g->getTextura(texture);
	}

	if(id != -1 && seleccion){
		glLoadName(id);
	}

	if(id != -1 || !seleccion){
		//glColorMaterial(GL_FRONT_AND_BACK ,GL_AMBIENT_AND_DIFFUSE );

		if(display != -1){
			if(_shader != -1){
				if(!seleccion){
					GestorRecursos::getInstancia()->activateShader(_shader);
				}
			}else{
				if(!seleccion){
					GestorRecursos::getInstancia()->activateShader(GestorRecursos::S_CellShading);
				}
			}

			glColor4fv(color);

			if(t != -1 && !seleccion){
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,t);
			}

			glCallList(display);
	        //glutSolidTeapot(1.0);

			if(t != -1 && !seleccion){
				glDisable(GL_TEXTURE_2D);
			}

			if(_shader != -1){
				if(!seleccion){
					GestorRecursos::getInstancia()->desactivateShader(_shader);
				}
			}else{
				if(!seleccion){
					GestorRecursos::getInstancia()->desactivateShader(GestorRecursos::S_CellShading);
				}
			}
		}
	}

#ifdef _DEBUG_
	cout << "Renderizo el modelo" << endl;
	cout << "Renderizo los hijos del modelo(" << hijos.size() << ")" << endl;
	cout << endl;
#endif
	RenderHijos(seleccion);
#ifdef _DEBUG_
	cout << endl;
	cout << "Vuelvo al modelo" << endl;
#endif
}

void Model::setIdModel(int id)
{
	idModel = id;
}

int Model::getIdModel()
{
	return idModel;
}

void Model::setShader(int shader){
	_shader = shader;
}

}
