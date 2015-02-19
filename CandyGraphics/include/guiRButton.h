/* 
 * File:   guiRButton.h
 * Author: gustavo
 *
 * Created on 14 de febrero de 2012, 20:43
 */

#ifndef GUIRBUTTON_H
#define	GUIRBUTTON_H

#include "GNode.h"
#include "GestorRecursos.h"

namespace candy {

    class guiRButton: public candy::GNode{
    public:
        guiRButton(string texto, bool check);
        virtual ~guiRButton();
        guiRButton(const guiRButton& rb);
        guiRButton& operator=(const guiRButton& rb);
        void setTexto(string texto);
        string getTexto();
        void Render(bool seleccion);
        bool isChecked();
        void setCheck(bool c);
        
    private:
        void copiarDesde(const guiRButton& rb);
        Text* texto;
        int textura;
        bool checked;
        
    };

}



#endif	/* GUIRBUTTON_H */

