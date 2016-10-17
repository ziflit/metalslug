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
    int jumpPos[25] = {0, 23, 44, 63, 80, 95, 108, 119, 128, 135, 140, 143, 144, 143, 140, 135, 128, 119, 108, 95, 80, 63, 44, 23, 0};
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

    Postura getPostura(){ return this->postura;}

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
