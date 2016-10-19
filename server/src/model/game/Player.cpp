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
    postura =  MIRANDO_DERECHA_QUIETO;
}

Player::~Player() {
}

void Player::set_position( int posx,  int posy) {
    x = posx;
    y = posy;
}

bool Player::isKeyPressed(EventCode nuevoEvento) {
    return ( (nuevoEvento == SDL_KEY_A_PRESSED) or (nuevoEvento == SDL_KEY_S_PRESSED) or (nuevoEvento == SDL_KEYUP_PRESSED) or (nuevoEvento == SDL_KEYDOWN_PRESSED) or (nuevoEvento == SDL_KEYLEFT_PRESSED) or (nuevoEvento == SDL_KEYRIGHT_PRESSED));
}
bool Player::isKeyRealeased(EventCode nuevoEvento) {

    return ( (nuevoEvento == SDL_KEY_A_RELEASED) or (nuevoEvento == SDL_KEY_S_RELEASED) or (nuevoEvento == SDL_KEYUP_RELEASED) or (nuevoEvento == SDL_KEYDOWN_RELEASED) or (nuevoEvento == SDL_KEYLEFT_RELEASED) or (nuevoEvento == SDL_KEYRIGHT_RELEASED));
}

void Player::handleRealeasedKey(EventCode nuevoEvento) {
    switch (nuevoEvento) {

        case EventCode::SDL_KEYLEFT_RELEASED:
            if(direccionX == -1){
                if(postura ==  MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA){postura =  MIRANDO_ARRIBA_IZQUIERDA_QUIETO;}
                else if(postura ==  CAMINANDO_IZQUIERDA){postura =  MIRANDO_IZQUIERDA_QUIETO;}
                else if(postura ==  AGACHADO_AVANZANDO_IZQUIERDA){postura =  AGACHADO_MIRANDO_IZQUIERDA_QUIETO;}
                direccionX = 0;
            }
            /* Puede estar tocando ambas teclas a la vez, y suelta una de ellas */
            else if(direccionX == 0){
                if(postura ==  MIRANDO_DERECHA_QUIETO){postura = CAMINANDO_DERECHA;}
                else if(postura ==  AGACHADO_MIRANDO_DERECHA_QUIETO){postura =  AGACHADO_AVANZANDO_DERECHA;}
                else if(postura ==  MIRANDO_ARRIBA_DERECHA_QUIETO){postura =  MIRANDO_ARRIBA_CAMINANDO_DERECHA;}
                direccionX = 1;
            }
            break;
        case EventCode::SDL_KEYRIGHT_RELEASED:
            if(direccionX == 1){
                if(postura ==  MIRANDO_ARRIBA_CAMINANDO_DERECHA){postura =  MIRANDO_ARRIBA_DERECHA_QUIETO;}
                else if(postura ==  CAMINANDO_DERECHA){postura =  MIRANDO_DERECHA_QUIETO;}
                else if(postura ==  AGACHADO_AVANZANDO_DERECHA){postura =  AGACHADO_MIRANDO_DERECHA_QUIETO;}
                direccionX = 0;
            }
            /* Puede estar tocando ambas teclas a la vez, y suelta una de ellas. */
            else if(direccionX == 0){
                if(postura ==  MIRANDO_IZQUIERDA_QUIETO){postura = CAMINANDO_IZQUIERDA;}
                else if(postura ==  AGACHADO_MIRANDO_IZQUIERDA_QUIETO){postura =  AGACHADO_AVANZANDO_IZQUIERDA;}
                else if(postura ==  MIRANDO_ARRIBA_IZQUIERDA_QUIETO){postura =  MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA;}
                direccionX = -1;
            }
            break;
        case EventCode::SDL_KEYUP_RELEASED:
            switch (postura){
                case  MIRANDO_ARRIBA_DERECHA_QUIETO: postura =  MIRANDO_DERECHA_QUIETO;
                    break;
                case  MIRANDO_ARRIBA_IZQUIERDA_QUIETO: postura =  MIRANDO_IZQUIERDA_QUIETO;
                    break;
                case  MIRANDO_ARRIBA_CAMINANDO_DERECHA: postura =  CAMINANDO_DERECHA;
                    break;
                case  MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA: postura =  CAMINANDO_IZQUIERDA;
                    break;
                default:
                    postura =  MIRANDO_DERECHA_QUIETO;
                    break;
            }

        case EventCode::SDL_KEYDOWN_RELEASED:
            switch (postura){
                case  AGACHADO_MIRANDO_DERECHA_QUIETO: postura =  MIRANDO_DERECHA_QUIETO;
                    break;
                case  AGACHADO_MIRANDO_IZQUIERDA_QUIETO: postura =  MIRANDO_IZQUIERDA_QUIETO;
                    break;
                case  AGACHADO_AVANZANDO_DERECHA: postura =  CAMINANDO_DERECHA;
                    break;
                case  AGACHADO_AVANZANDO_IZQUIERDA: postura =  CAMINANDO_IZQUIERDA;
                    break;
                default:
                    postura =  MIRANDO_DERECHA_QUIETO;
                    break;
            }
        default:
            break;

    }
}
void Player::handlePressedKey(EventCode nuevoEvento){
    switch (nuevoEvento){
        case EventCode::SDL_KEY_A_PRESSED:
            if (!((postura == AGACHADO_MIRANDO_DERECHA_QUIETO) or (postura == AGACHADO_AVANZANDO_DERECHA) or (postura == AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura == AGACHADO_AVANZANDO_IZQUIERDA) )){
                direccionY = 1;
            }
            break;

        case EventCode::SDL_KEYUP_PRESSED:
            if(direccionX == 1){postura =  MIRANDO_ARRIBA_CAMINANDO_DERECHA;}
            else if(direccionX == -1){postura =  MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA;}
            else if(postura ==  MIRANDO_IZQUIERDA_QUIETO and direccionX == 0){postura =  MIRANDO_ARRIBA_IZQUIERDA_QUIETO;}
            else {postura =  MIRANDO_ARRIBA_DERECHA_QUIETO;}
            break;

        case EventCode::SDL_KEYDOWN_PRESSED:
            if(direccionX == 1){postura =  AGACHADO_AVANZANDO_DERECHA;}
            else if(direccionX == -1){postura =  AGACHADO_AVANZANDO_IZQUIERDA;}
            else if(postura ==  MIRANDO_IZQUIERDA_QUIETO and direccionX == 0){postura =  AGACHADO_MIRANDO_IZQUIERDA_QUIETO;}
            else {postura =  AGACHADO_MIRANDO_DERECHA_QUIETO;}
            break;

        case EventCode::SDL_KEYLEFT_PRESSED:
            if(direccionX == 0){
                if((postura ==  MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or (postura ==  MIRANDO_ARRIBA_DERECHA_QUIETO)){postura =  MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA;}
                else if((postura ==  AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura ==  AGACHADO_MIRANDO_DERECHA_QUIETO)){postura =  AGACHADO_AVANZANDO_IZQUIERDA;}
                else if((postura ==  MIRANDO_IZQUIERDA_QUIETO) or (postura ==  MIRANDO_DERECHA_QUIETO)){postura =  CAMINANDO_IZQUIERDA; }
                else{postura =  CAMINANDO_IZQUIERDA;}
                direccionX = -1;
            }
            /* Si está caminando hacia la derecha y presiona LEFT entonces queda quieto */
            else if(direccionX == 1){
                direccionX = -1;
                postura =  CAMINANDO_IZQUIERDA;}
            break;

        case EventCode::SDL_KEYRIGHT_PRESSED:
            if(direccionX == 0){
                if((postura ==  MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or (postura ==  MIRANDO_ARRIBA_DERECHA_QUIETO)){postura =  MIRANDO_ARRIBA_CAMINANDO_DERECHA;}
                else if((postura ==  AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura ==  AGACHADO_MIRANDO_DERECHA_QUIETO)){postura =  AGACHADO_AVANZANDO_DERECHA;}
                else if((postura ==  MIRANDO_IZQUIERDA_QUIETO) or (postura ==  MIRANDO_DERECHA_QUIETO)){postura =  CAMINANDO_DERECHA; }
                else{postura =  CAMINANDO_DERECHA;}
                direccionX = 1;
            }
            /* Si está caminando hacia la izquierda y presiona RIGHT entonces queda quieto */
            else if(direccionX == -1){
                direccionX = 1;
                postura =  CAMINANDO_DERECHA;}
            break;

        default:
            break;
    }
}


void Player::updateState(EventCode nuevoEvento){
    if (nuevoEvento == EventCode::CLIENT_DISCONNECT){
        this->postura =  DESCONECTADO;
    }
    else if (isKeyPressed(nuevoEvento)) {
        handlePressedKey(nuevoEvento);
    }
    else if (isKeyRealeased(nuevoEvento)) {
        handleRealeasedKey(nuevoEvento);
    }
}

bool Player::isMoving() {
	return (Player::direccionX != 0); // en -1 y 1 se esta moviendo
}

bool Player::isJumping() {
    return (direccionY == 1);
}

void Player::updatePosition() {
    if (this->postura != DESCONECTADO){
        if(this->isMoving()) {

            if (((direccionX == 1) and (x < (windowWidth-100))) or ((direccionX == -1) and (x > 0))) {
                x += direccionX*speed;
            }
        }

        if(this->isJumping()) {
            if (posAtJump < 25){
                posAtJump++;
                y = 400 - jumpPos[posAtJump];
            } else {
                direccionY = 0;
                posAtJump = 0;
            }
        }
    }
    else{
        x = 0; //pone al grisado en el borde izquierdo
    }
}

void Player::retroceder(){
    x -= speed;
}

struct event Player::getNewState(){
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




















































