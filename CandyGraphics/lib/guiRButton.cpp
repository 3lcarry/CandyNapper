#include <GL/glew.h>

#include "guiRButton.h"
#include "Text.h"
#include "GestorRecursos.h"

namespace candy
{
    
    guiRButton::guiRButton(string texto,bool check)
        :GNode(GNode::E_RButton){
        GestorRecursos* g =  GestorRecursos::getInstancia();
        
        if(check)
                textura = g->getTextura(GestorRecursos::guiTex_RButton);       
        else
                textura = g->getTextura(GestorRecursos::guiTex_RButton_a);
        
        this->texto=new Text();        
        this->texto->setTamanyo(15);
        this->texto->setFont(10);        
        this->texto->setTexto(texto);  
        checked=false;
    }
    
    guiRButton::~guiRButton(){
    }
    
    guiRButton::guiRButton(const guiRButton& rb)
        :GNode(rb)
    {
        copiarDesde(rb);
    }
    
    guiRButton& guiRButton::operator =(const guiRButton& rb){
        if(this!=&rb)
            this->~guiRButton();
            copiarDesde(rb);
        
        return *this;                    
    }
    
    void guiRButton::copiarDesde(const guiRButton& rb){                        
        texto=rb.texto;        
    }
    
    void guiRButton::setTexto(string texto){
        this->texto->setTexto(texto);
    }
    
    string guiRButton::getTexto(){
        return texto->getTexto();
    } 
    
    void guiRButton::setCheck(bool c){
        checked=c;
    }
    
    bool guiRButton::isChecked(){
        return checked;
    }
    
    void guiRButton::Render(bool seleccion){
        
        float segmentos=40;
	float incremento=2*M_PI/40;
	float angulo=-incremento/2;
        
        glColor3f(0.9,0.9,0.9);
        glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textura);
   	glBegin(GL_TRIANGLE_FAN);
	for(int i=0; i<segmentos; i++){
		float x=0+1*cos(angulo);
		float y=0+1*sin(angulo);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2d(cos(angulo)/2.0+0.5,sin(angulo)/2.5+0.5);
		glVertex2f(x,y);
		angulo-=incremento;
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
        
    }
}
