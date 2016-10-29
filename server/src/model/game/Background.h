/*
 * Background.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_BACKGROUND_H_
#define SRC_MODEL_GAME_BACKGROUND_H_

#include "../../utils/Protocol.h"
#include "GameObject.h"

class Background : public GameObject {
	/**
	 *	Esta clase define al fondo directo a los jugadores,
	 *	debera avanzar con el movimiento de ellos, cuando
	 *  corresponda.
	 *	El resto de los backgrounds como ser aquellos con nubes,
	 *	por el momento se moveran solos, no tendran comportamiento
	 *	definido.
	 */

public:
	Background(int zindex,int speed, double large);

	virtual ~Background();

	struct event getState();

    void calculateSpeed(int largeMainBackground, int speedMainBackground);

	void setEntity(int zindex);

	void avanzar();

};

#endif /* SRC_MODEL_GAME_BACKGROUND_H_ */
