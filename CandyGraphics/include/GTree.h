/*
 * GTree.h
 *
 *  Created on: 06/02/2012
 *      Author: gustavo
 */

#ifndef GTREE_H_
#define GTREE_H_

#include <iostream>
#include <list>
#include "Color.h"

using namespace std;

namespace candy{

	class GNode;

    class GTree{

        friend class GNode;

    private:

        GNode* raiz;

    public:

        GTree();
        ~GTree();
        GTree(const GTree& gt);
        GTree& operator=(const GTree& gt);
        void copiarDesde(const GTree& gt);
        void addChild(GNode* node);
        void rmChild(GNode* node);
        list<GTree*> Hijos() const;
        void Render(bool seleccion);
        GNode* Raiz() const;
        void setRaiz(GNode* n);
        bool isDestroy();

    };

}
#endif /* GTREE_H_ */
