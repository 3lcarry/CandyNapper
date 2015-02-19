/*
 * Objetos.h
 *
 *  Created on: 11/05/2012
 *      Author: carrillo
 */

#ifndef OBJETOS_H_
#define OBJETOS_H_

#include "IComponent.h"
#include "GEStatic.h"

namespace candy {

class Objetos : public GEStatic {
public:
	enum TiposObjetos{
		Jeringilla,
		Botiquin_Pequeno,
		Botiquin_Mediano,
		Botiquin_Grande,
		Miel,
		Portal,
		NumTipoObjetos
	};


	Objetos(TiposObjetos tipo, Vector3 pos);
	virtual ~Objetos();
	TiposObjetos getTipoObjeto();
	void setNextLevel(string nl);
	string getNextLevel();

	void setMatarTodos(bool mT);
	bool getMatarTodos();

private:
	bool matarTodos;

	string nextLevel;
	TiposObjetos _tipo;

};

} /* namespace candy */
#endif /* OBJETOS_H_ */
