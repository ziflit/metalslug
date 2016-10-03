/*
 * Player.h
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#ifndef SRC_MODEL_GAME_PLAYER_H_
#define SRC_MODEL_GAME_PLAYER_H_

class Player {
private:
    char username[20];
    char sprite[250];
    unsigned int x;
    unsigned int y;
    unsigned int speed;


public:
	Player();
	virtual ~Player();

//getters y setters
	unsigned int getSpeed() const {
		return speed;
	}

	void setSpeed(unsigned int speed) {
		this->speed = speed;
	}

	const char* getSprite() const {
		return sprite;
	}

	const char* getUsername() const {
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
