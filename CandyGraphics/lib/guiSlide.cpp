#include <GL/glew.h>
#include "guiSlide.h"

namespace candy{
    guiSlide::guiSlide(float min, float max, float freq)
        :GNode(GNode::E_Slide){
        minimo=min;
        maximo=max;
        frequencia=freq;
    }
    
    guiSlide::~guiSlide(){
    }
    
    guiSlide::guiSlide(const guiSlide& gs)
        :GNode(gs){
        copiarDesde(gs);
    }
    
    guiSlide& guiSlide::operator =(const guiSlide& gs){
        if(this!=&gs){
            this->~guiSlide();
            copiarDesde(gs);
        }
        
        return *this;
    }
    
    void guiSlide::copiarDesde(const guiSlide& gs){
        minimo=gs.minimo;
        maximo=gs.maximo;
        frequencia=gs.frequencia;
    }
    
    void guiSlide::Render(bool seleccion){
        
        glColor4f(0.6,0.6,0.6,0.8);		
	glBegin(GL_QUADS);			
                glNormal3f(0.0,0.0,1.0);
                glVertex2f(0,0);			
		glVertex2f(10,0);		
		glVertex2f(10,1);			
		glVertex2f(0,1);        
        glEnd();
        
        glColor4f(1.0,0.0,0.0,0.8);
        glBegin(GL_QUADS);			
                glNormal3f(0.0,0.0,1.0);
                glVertex2f(0,-0.5);			
		glVertex2f(0.5,-0.5);		
		glVertex2f(0.5,1.5);			
		glVertex2f(0,1.5);
        glEnd();
    }

}
