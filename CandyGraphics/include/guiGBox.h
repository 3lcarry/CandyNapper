/* 
 * File:   guiGBox.h
 * Author: gustavo
 *
 * Created on 15 de febrero de 2012, 11:00
 */

#ifndef GUIGBOX_H
#define	GUIGBOX_H

#include "GNode.h"

namespace candy {
    
        class guiGBox: public candy::GNode {
        public:
            guiGBox(float alto, float ancho);
            virtual ~guiGBox();
            guiGBox(const guiGBox& gb);
            guiGBox& operator=(const guiGBox& gb);
            guiButton* addButton(float ancho, float alto, string texto);
            void Render(bool seleccion);
            
        private:
            void copiarDesde(const guiGBox& gb);
            float alto;
            float ancho;
            int botones;

        };
}

#endif	/* GUIGBOX_H */

