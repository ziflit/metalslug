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
    box_alto = 100;
    box_ancho = 50;
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
    return (Player::direccionY == 1);
}

void Player::updatePosition(vector<GameObject*> game_objects) {
    if (this->postura != DESCONECTADO) {
        int newX = x;
        int newY = y;
        if (this->isMoving()) {
            if (((direccionX == 1) and (x < (windowWidth - 100))) or ((direccionX == -1) and (x > 0))) {
                newX = x + direccionX * speed;
            }
        }
        if (this->isJumping()) {
            if (posAtJump < 24) {
                posAtJump++;
                newY = 400 - jumpPos[posAtJump];
            } else {
                direccionY = 0;
                posAtJump = 0;
            }
        }

        if (this->canIMove(game_objects, newX, newY)) {
            x = newX;
            y = newY;
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

    eventExt.x = x;  //Actualizo la posicion del player
    eventExt.y = y;
    eventExt.postura = this->postura;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;

    return estado;
}

bool Player::canIMove(vector<GameObject*> game_objects, int newX, int newY) {
    /* Auto??? que pasa con las cosas abstractas? */
    bool isColisionanding;
    for (auto &game_object : game_objects) {
        // Checkeo de colisiones
        if (puedenColisionar(this, game_object)) {
            isColisionanding = this->checkCollition(newX, newY, game_object);
            if (isColisionanding) {
                // resolucion de colisiones con el game_object:
                return false;
            }
        }
    }
    return true;
}
