#include <GL/glew.h>

#include "guiButton.h"
#include "Text.h"
#include "GestorRecursos.h"
#include "Transformation.h"

namespace candy
{
    
    guiButton::guiButton(float ancho, float alto, string texto)
        :GNode(GNode::E_Button){
        GestorRecursos* g =  GestorRecursos::getInstancia();
        textura = g->getTextura(GestorRecursos::guiTex_Button);
        this->ancho=ancho;
        this->alto=alto;

        Transformation* t=this->addTransformation();
        t->Translate(-ancho/2.0+5,-alto/(alto/10),0);
        this->texto = t->addText();
        this->texto->setTamanyo(20);
        this->texto->setFont(GestorRecursos::E_Anarchy);
        this->texto->setColor(Color(0,0,0.5,1));
        this->texto->setTexto(texto);
        this->texto->setID(id);
    }
    
    guiButton::~guiButton(){
    }
    
    guiButton::guiButton(const guiButton& b)
        :GNode(b)
    {
        copiarDesde(b);
    }
    
    guiButton& guiButton::operator =(const guiButton& b){
        if(this!=&b)
            this->~guiButton();
            copiarDesde(b);
        
        return *this;                    
    }
    
    void guiButton::copiarDesde(const guiButton& b){                        
        texto=b.texto;        
    }
    
    void guiButton::setTexto(string texto){
        this->texto->setTexto(texto);
    }
    
    string guiButton::getTexto(){
        return texto->getTexto();
    }        
    
    void guiButton::Render(bool seleccion){
    	if(id != -1 && seleccion){
    		glLoadName(id);
    	}

    	if(!seleccion){
			glColor3f(0.9,0.9,0.9);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,textura);
    	}

        glBegin(GL_QUADS);
       		glNormal3f(0.0,0.0,1.0);
       		glTexCoord2f(0.0,0.0);
			glVertex2f(-ancho/2,-alto/2);

			glTexCoord2f(1.0,0.0);
			glVertex2f(ancho/2,-alto/2);

			glTexCoord2f(1.0,1.0);
			glVertex2f(ancho/2,alto/2);

			glTexCoord2f(0.0,1.0);
			glVertex2f(-ancho/2,alto/2);

		glEnd();
		if(!seleccion){
			glDisable(GL_TEXTURE_2D);
		}

		RenderHijos(seleccion);
    }
}
