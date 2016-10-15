/*
 * Background.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_BACKGROUND_H_
#define SRC_MODEL_GAME_BACKGROUND_H_

#include "../../utils/Protocol.h"

class Background {
	/**
	 *	Esta clase define al fondo directo a los jugadores,
	 *	debera avanzar con el movimiento de ellos, cuando
	 *  corresponda.
	 *	El resto de los backgrounds como ser aquellos con nubes,
	 *	por el momento se moveran solos, no tendran comportamiento
	 *	definido.
	 */

private:
	Entity entity;
	unsigned int x;
	unsigned int y;
	unsigned int speed;

public:
	Background(int zindex,int speed);
	virtual ~Background();

	struct event getState();

	void setEntity(int zindex);

	void avanzar();

	unsigned int getSpeed() const {
		return speed;
	}

	void setSpeed(unsigned int speed) {
		this->speed = speed;
	}

	unsigned int getX() const {
		return x;
	}

	void setX(unsigned int x) {
		this->x = x;
	}

	unsigned int getY() const {
		return y;
	}

	void setY(unsigned int y) {
		this->y = y;
	}

};

#endif /* SRC_MODEL_GAME_BACKGROUND_H_ */
