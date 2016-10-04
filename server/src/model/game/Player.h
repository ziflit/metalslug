/*
 * Player.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_PLAYER_H_
#define SRC_MODEL_GAME_PLAYER_H_

#include <string>
#include "../../utils/Protocol.h"

class Player {
private:
	string username;
    string sprite;
    unsigned int x;
    unsigned int y;
    unsigned int speed;


public:
	Player();
	virtual ~Player();

	struct event playerState();

	void movePlayer(EventCode movimiento);

//getters y setters
	unsigned int getSpeed() const {
		return speed;
	}

	void setSpeed(unsigned int speed) {
		this->speed = speed;
	}

	string getSprite() const {
		return sprite;
	}

	string getUsername() const {
		return username;
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



#endif /* SRC_MODEL_GAME_PLAYER_H_ */
