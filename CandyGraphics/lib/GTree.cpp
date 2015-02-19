/*
 * GraphicalTree.cpp
 *
 *  Created on: 06/02/2012
 *      Author: gustavo
 */

#include "GTree.h"

#include "GNode.h"

#include "Light.h"
#include "Camera.h"
#include "Transformation.h"
#include "Shape.h"
#include "Model.h"
#include "guiButton.h"
#include "Text.h"
#include "guiRButton.h"
#include "guiGBox.h"
#include "guiSlide.h"

using namespace candy;

////////////////////////////////////////////////////////////
/////////////////////// GTREE //////////////////////////////
////////////////////////////////////////////////////////////

GTree::GTree(){
	raiz = NULL;
}

GTree::~GTree(){
	if(raiz != NULL){
		delete raiz;
		raiz=NULL;
	}
}

GTree::GTree(const GTree& gt){
	copiarDesde(gt);
}

GTree& GTree::operator =(const GTree& gt){
	if(this!=&gt){
	    this->~GTree();
		copiarDesde(gt);
	}
	return *this;
}

void GTree::copiarDesde(const GTree& gt){
    if(gt.raiz!=NULL){
        list<GTree*>::const_iterator it;

        for(it=gt.raiz->hijos.begin(); it!=gt.raiz->hijos.end(); it++){
        	GNode* raiz_aux = (*it)->raiz;
            switch (raiz_aux->tipo) {
                    case GNode::E_Transformation:{
                        raiz=new Transformation((Transformation&)(*raiz_aux));
                    }
                    break;
                    case GNode::E_Camera:{
                        raiz=new Camera((Camera&)(*raiz_aux));
                    }
                    break;
                    case GNode::E_Light:{
                        raiz=new Light((Light&)(*raiz_aux));
                    }
                    break;
                    case GNode::E_Model:{
                        raiz=new Model((Model&)(*raiz_aux));

                    }
                    break;
                    case GNode::E_Polygon:{
                        raiz=new Shape((Shape&)(*raiz_aux));

                    }
                    break;
                    case GNode::E_Text:{
                    	raiz = new Text((Text&)(*raiz_aux));
                    }
                    break;
                    case GNode::E_Button:{
                        raiz = new guiButton((guiButton&)(*raiz_aux));
                    }
                    break;
                    case GNode::E_RButton:{
                        raiz = new guiRButton((guiRButton&)(*raiz_aux));
                    }
                    break;
                    case GNode::E_GBox:{
                        raiz = new guiGBox((guiGBox&)(*raiz_aux));
                    }
                    break;
                    case GNode::E_Slide:{
                        raiz = new guiSlide((guiSlide&)(*raiz_aux));
                    }
                    break;
                    default:

                    	break;
                    }
        }
    }
    else
        raiz=NULL;
}


void GTree::addChild(GNode* node){

    raiz=node;
}

void GTree::rmChild(GNode* node){

    list<GTree*>::iterator it;
    bool borrado=false;

    for(it=raiz->hijos.begin(); (it!=raiz->hijos.end() && !borrado); it++){

        if((*it)->raiz==node){
            it=raiz->hijos.erase(it);
            borrado=true;
        }
    }
}

list<GTree*> GTree::Hijos() const{
    return raiz->hijos;
}

void GTree::Render(bool seleccion){
	//Renderizo
	if(raiz->activo){
		if(!raiz->_depth){
			glDepthMask(false);
		}

		if(!raiz->_light){
			glDisable(GL_LIGHTING);
		}
    	raiz->Render(seleccion);

    	if(!raiz->_light){
    		glEnable(GL_LIGHTING);
    	}

    	if(!raiz->_depth){
    		glDepthMask(true);
    	}
	}
}

GNode* GTree::Raiz() const{
    return raiz;
}

void GTree::setRaiz(GNode* n){
    raiz=n;
}

bool GTree::isDestroy(){
	return raiz->destroy;
}
