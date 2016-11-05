/*
 * Player.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include <iostream>
#include "Player.h"

Player::Player(string user, Entity entitySelected, int windowWidth) {
    username = user;
    id = entitySelected;
    this->windowWidth = windowWidth;
    /**Para que no arranque pegado al borde izq: | o      | x = 100
     * El sistema de coordenadas que vamos a usar es el de SDL
     * (0,0) en la esquina superior izquierda
     * 			(0,0)___________________(0,800)
     * 			    |					|
     * 	   			|					|
     *        (0,600)___________________(600,800)
     */
    x = 5;
    y = 400;
    direccionY = 0;
    direccionX = 0;
    posAtJump = 0;
    gravity = 10;
    speed = 10;
    postura = MIRANDO_DERECHA_QUIETO;
    isShooting = false;
    isJumping = false;
    bulletType = Entity::BT_BULLET;  //Comienza con la pistola normal
}

Player::~Player() {
}

void Player::set_position(int posx, int posy) {
    x = posx;
    y = posy;
}

bool Player::isMoving() {
    return (Player::direccionX != 0); // en -1 y 1 se esta moviendo
}

bool Player::haveBullets(){
    if (ammo > 0){
        return true;
    }
    return false;
}

Bullet* Player::shoot(){
    Bullet* bullet = new Bullet(bulletType, this->x, this->y, this->direccionX, this->direccionY);
    ammo--;
    return bullet;
};

void Player::updatePosition() {
    if (this->postura != DESCONECTADO) {
        if (this->isMoving()) {

            if (((direccionX == 1) and (x < (windowWidth - 100))) or ((direccionX == -1) and (x > 0))) {
                x += direccionX * speed;
            }
        }

        if (this->getJumpingState()) {
            if (posAtJump < 24) {
                posAtJump++;
                y = 400 - jumpPos[posAtJump];
            } else {
                isJumping = false;
                posAtJump = 0;
            }
        }
    } else {
        x = 0; //pone al grisado en el borde izquierdo
    }
}

void Player::retroceder() {
    x -= speed;
}

struct event Player::getState() {
    struct event estado;
    struct event_ext eventExt;

    eventExt.code = EventCode::PLAYER_STATUS;
    eventExt.id = this->id;

    sprintf(eventExt.username, "%.20s", this->username.c_str());

    eventExt.x = x;  //Actualizo la posicion del player
    eventExt.y = y;
    eventExt.postura = this->postura;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;

    return estado;
}



















































