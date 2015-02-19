/* 
 * File:   Button.h
 * Author: gustavo
 *
 * Created on 13 de febrero de 2012, 20:53
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "GNode.h"
#include "GestorRecursos.h"

namespace candy {
    
        class guiButton: public candy::GNode {
        public:
            guiButton(float ancho, float alto, string texto);
            virtual ~guiButton();
            guiButton(const guiButton& b);
            guiButton& operator=(const guiButton& b);           
            void setTexto(string texto);
            string getTexto();
            void Render(bool seleccion);
            
        private:
            void copiarDesde(const guiButton& b);
            Text* texto;
            int textura;
            float ancho;
            float alto;

        };
}
#endif	/* BUTTON_H */

