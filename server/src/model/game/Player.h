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
#include "GameObject.h"

class Player : public GameObject{
private:
    string username;
    int direccionX;
    int direccionY;
    int posAtJump;
    int gravity;
    int jumpPos[25] = {0, 23, 44, 63, 80, 95, 108, 119, 128, 135, 140, 143, 144, 143, 140, 135, 128, 119, 108, 95, 80,
                       63, 44, 23, 0};
    Postura postura;
    int windowWidth;


public:
    Player(string user, Entity entitySelected, int windowWidth);

    virtual ~Player();

    Postura getPostura() { return this->postura; }

    void setPostura(Postura postura) {
        Player::postura = postura;
    }

    struct event getState() override ;

    // El parametro type, indica con '1' (para presionada)  o '0' (para soltada) si lo que paso fue que se solto o se presiono la tecla (keypressed o keyreleased)

    bool isJumping();

    bool isMoving();

    void jump();

    void jumpGoingUp();

    void jumpGoingDown();

    void avanzar() override { x += speed; };

    void retroceder();

    void updatePosition();

    bool isInHalfWindow();

    void moveLeft();

    void moveRight();

    void set_position(int posx, int posy);

    void stopMoving();


    //getters y setters -----------------------------------------------------------------------------------------

    void setDireccionX(int direccionX) {
        Player::direccionX = direccionX;
    }

    void setDireccionY(int direccionY) {
        Player::direccionY = direccionY;
    }

    int getDireccionX() const {
        return direccionX;
    }

    int getDireccionY() const {
        return direccionY;
    }

    string getUsername() const {
        return username;
    }
};


#endif /* SRC_MODEL_GAME_PLAYER_H_ */
