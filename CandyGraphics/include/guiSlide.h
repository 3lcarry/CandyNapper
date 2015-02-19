/* 
 * File:   guiSlide.h
 * Author: gustavo
 *
 * Created on 17 de febrero de 2012, 11:22
 */

#ifndef GUISLIDE_H
#define	GUISLIDE_H

#include "GNode.h"

namespace candy{

    class guiSlide: public candy::GNode{
    public:
        guiSlide(float min, float max, float freq);
        virtual ~guiSlide();
        guiSlide(const guiSlide& gs);
        guiSlide& operator=(const guiSlide& gs);
        void Render(bool seleccion);
        
    private:
        void copiarDesde(const guiSlide& gs);
        float minimo;
        float maximo;
        float frequencia;
    };
}


#endif	/* GUISLIDE_H */

