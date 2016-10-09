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
    unsigned int x;
    unsigned int y;
    int speed;
    unsigned int actualPhotogramOfTheSprite;
    unsigned int anchoDelFotograma;
	unsigned int anchoDelSprite; // Ancho de la imagen total, del sprite, se usa para calcular cuantos fotogramas tiene el sprite
	unsigned int windowWidth;

public:
	Player(string user, Entity entitySelected);
	virtual ~Player();

	struct event getNewState();

	// El parametro type, indica con '1' (para presionada)  o '0' (para soltada) si lo que paso fue que se solto o se presiono la tecla (keypressed o keyreleased)
	void updateState(EventCode evento);

	bool isMoving();

    void avanzar();

    void retroceder();

	void updatePosition();

	// TODO:El modelo debe saber que fotograma del sprite debe mostrar para informarle al cliente, asi sabe que dibujar?
	void setNextSpriteFrame();

	// Indica si el jugador esta en el medio de la pantalla, esto va a ser consultado por el modelo para actualizar el fondo en cada loop
	bool isInHalfWindow();

	void moveLeft();
	void moveRight();

	void set_position(unsigned int posx, unsigned int posy);

	void stopMoving();


	//getters y setters -----------------------------------------------------------------------------------------
	unsigned int getSpeed() const {
		return speed;
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
