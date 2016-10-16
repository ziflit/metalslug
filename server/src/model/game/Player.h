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
	Entity entity;
    int x;
    int y;
    int direccionX;
	int direccionY;
    int posAtJump;
    int jumpPos[201]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,0};
    int speed;
	int gravity;
	Postura postura;
	int windowWidth;


public:
	Player(string user, Entity entitySelected);

	virtual ~Player();

    Entity getEntity() {
        return entity;
    }

	struct event getNewState();

	void handleRealeasedKey(EventCode nuevoEvento);

	void handlePressedKey(EventCode nuevoEvento);

	bool isKeyPressed(EventCode nuevoEvento);

	bool isKeyRealeased(EventCode nuevoEvento);

	// El parametro type, indica con '1' (para presionada)  o '0' (para soltada) si lo que paso fue que se solto o se presiono la tecla (keypressed o keyreleased)
	void updateState(EventCode nuevoEvento);

	bool isJumping();

	bool isMoving();

	void jump();
	
	void jumpGoingUp();

	void jumpGoingDown();
	
	void avanzar();

    void retroceder();

	void updatePosition();

	bool isInHalfWindow();

	void moveLeft();

	void moveRight();

	void set_position( int posx,  int posy);

	void stopMoving();


	//getters y setters -----------------------------------------------------------------------------------------
	unsigned int getSpeed() const {
		return speed;
	}

    unsigned int getDireccionX() const{
        return direccionX;
    }

	void setSpeed(unsigned int speed) {
		this->speed = speed;
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

	Entity getEntity() const {
		return entity;
	}

	void setEntity(Entity entity) {
		this->entity = entity;
	}
};



#endif /* SRC_MODEL_GAME_PLAYER_H_ */
