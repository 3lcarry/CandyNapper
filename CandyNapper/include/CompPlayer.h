/*
 * CompPlayer.h
 *
 *  Created on: 11/05/2012
 *      Author: carrillo
 */

#ifndef COMPPLAYER_H_
#define COMPPLAYER_H_

#include "IComponent.h"

namespace candy {


class CompPlayer : public candy::IComponent {
public:
	CompPlayer();
	virtual ~CompPlayer();
	void Update(GameEntity* entidad);
private:
	long int inicioAtope;
	bool Atope;
	int dirMensaje;
};

} /* namespace candy */
#endif /* COMPPLAYER_H_ */
