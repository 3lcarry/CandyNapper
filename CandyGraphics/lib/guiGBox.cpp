#include <GL/glew.h>

#include "guiGBox.h"
#include "Transformation.h"


namespace candy{    
        guiGBox::guiGBox(float alto, float ancho)
                :GNode(GNode::E_GBox){
            this->alto=alto;
            this->ancho=ancho;
            botones=alto;
        }
        
        guiGBox::~guiGBox(){
        }
        
        guiGBox::guiGBox(const guiGBox& gb)
                :GNode(gb){
            copiarDesde(gb);
        }

        guiGBox& guiGBox::operator =(const guiGBox& gb){
            if(this != &gb){
                this->~guiGBox();
                copiarDesde(gb);
            }
            
            return *this;
        }
        
        void guiGBox::copiarDesde(const guiGBox& gb){
            alto=gb.alto;
            ancho=gb.ancho;
        }
        
        void guiGBox::Render(bool seleccion){
            
        	glColor4f(0.6,0.6,0.6,0.8);
        	glBegin(GL_QUADS);
        		glNormal3f(0.0,0.0,1.0);
        		glVertex2f(-ancho/2.0,-alto/2.0);
        		glVertex2f(ancho/2.0,-alto/2.0);
        		glVertex2f(ancho/2.0,alto/2.0);
        		glVertex2f(-ancho/2.0,alto/2.0);
        	glEnd();
        	this->RenderHijos(seleccion);
        }
        
       guiButton* guiGBox::addButton(float ancho, float alto, string texto){
    	   	Transformation* t=this->addTransformation();
    	   	t->Translate(-ancho/15,botones/2.5,0);
    	   	botones=botones-150;
            guiButton* b=t->addButton(ancho,alto,texto);
            return b;
            
        }   
        
        /*guiRButton* guiGBox::addRButton(string texto, bool check){

        }**/
}
