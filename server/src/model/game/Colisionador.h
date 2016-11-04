/*
 * Colisionador.h
 *
 *  Created on: Nov 3, 2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_COLISIONADOR_H_
#define SRC_MODEL_GAME_COLISIONADOR_H_

#include <iostream>
#include <vector>
#include "../../utils/Protocol.h"
#include "GameObject.h"

using namespace std;

class Colisionador {
private:

public:
	Colisionador();
	virtual ~Colisionador();

	/* La idea es que devuelva un vector con los pares de elementos que colisionan, tendriamos
	 * que ver como definir esto bien, para ver como obtener esa data.
	 * En base a eso, se le avisa a los objetos que colisionen que realicen las tareas debidas */
	vector<GameObject*> cualesColisionan(vector<GameObject*> objetosParaColisionar);
};

#endif /* SRC_MODEL_GAME_COLISIONADOR_H_ */
