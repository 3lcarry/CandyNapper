/*
 * AnimatedModel.h
 *
 *  Created on: 17/03/2012
 *      Author: kaseyo
 */

#ifndef ANIMATEDMODEL_H_
#define ANIMATEDMODEL_H_
#include "Model.h"
#include <vector>
using namespace std;

namespace candy {

class ModelAnimation {
public:
	ModelAnimation(Model *m=NULL);
	ModelAnimation(Model *m, vector<int> ids);
	~ModelAnimation();
	void Start();
	void Continue(int tiempoDuracion = 1000);
	void setModel(Model *m);
	void addModels(vector<int> idsModels);

private:
	Model* _modelo;
	vector<int> _modelos;
	int _actualMovement;
	unsigned int _lastTime;
};

} /* namespace candy */
#endif /* ANIMATEDMODEL_H_ */
