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
	float x,y;
	double large;
    float speed;

public:
	Background(int zindex,int speed, double large);

	virtual ~Background();

	struct event getState();

    void calculateSpeed(int largeMainBackground, int speedMainBackground);

	void setEntity(int zindex);

	void avanzar();

    float getSpeed() const {
		return speed;
	}

	void setSpeed(float speed) {
		this->speed = speed;
	}

    float getX() const {
		return x;
	}

	void setX(float x) {
		this->x = x;
	}

    int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

};

#endif /* SRC_MODEL_GAME_BACKGROUND_H_ */
