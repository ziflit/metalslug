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
    entity = entitySelected;
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

bool Player::isJumping() {
    return (direccionY == 1);
}

void Player::updatePosition() {
    if (this->postura != DESCONECTADO) {
        if (this->isMoving()) {

            if (((direccionX == 1) and (x < (windowWidth - 100))) or ((direccionX == -1) and (x > 0))) {
                x += direccionX * speed;
            }
        }

        if (this->isJumping()) {
            if (posAtJump < 25) {
                posAtJump++;
                y = 400 - jumpPos[posAtJump];
            } else {
                direccionY = 0;
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
    eventExt.id = entity;

    eventExt.x = x;  //Actualizo la posicion del player
    eventExt.y = y;
    eventExt.postura = this->postura;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;

    return estado;
}



















































