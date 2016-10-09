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
private:
	int zindex;  // para saber que background es, parallax
	unsigned int x;
	unsigned int y;
	unsigned int speed;

public:
	Background(int zindex);
	virtual ~Background();

	struct event getState();

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

	int getZindex() const {
		return zindex;
	}

	void setZindex(int zindex) {
		this->zindex = zindex;
	}
};

#endif /* SRC_MODEL_GAME_BACKGROUND_H_ */
