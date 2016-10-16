/*
 * Player.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include <iostream>
#include "Player.h"

Player::Player(string user, Entity entitySelected) {
	username = user;
	entity = entitySelected;
	/**Para que no arranque pegado al borde izq: | o      | x = 100
	 * El sistema de coordenadas que vamos a usar es el de SDL
	 * (0,0) en la esquina superior izquierda
	 * 			(0,0)___________________(0,800)
	 * 			    |					|
	 * 	   			|					|
	 *      (600,800)___________________(600,800)
	 */
	x = 0;
	y = 400;
    direccionY = 0;
	direccionX = 0;
    posAtJump = 0;
    gravity = 10;
	speed = 10;
    postura = Postura::MIRANDO_DERECHA_QUIETO;
}

Player::~Player() {
}

void Player::set_position( int posx,  int posy) {
    x = posx;
    y = posy;
}

void Player::moveRight() {
/** mueve el sprite en eje X hacia la derecha.
 * Si el sprite tiene coordenadas (mitad de pantalla, y)
 * entonces no sigue avanzando hacia la derecha
 * Solo va a poder avanzar mas de la mitad de pantalla si
 * el BackgroundSprite llego a su ultimo frame.
*/
//  Player::set_position(Player::destRect.x + speed, Player::destRect.y);}
	unsigned int newPos = (x + speed);
	if(newPos < (windowWidth/2)){
		set_position(newPos, y);}
}

// ver como hacer para que salte
void Player::jump(){}
void Player::jumpGoingUp(){y -= 3;}
void Player::jumpGoingDown(){y += 3;}
// -------------------------------------

void Player::stopMoving(){
	direccionX = 0;
	//TODO: Aca habria que cambiar algo de frames? para que quede quieto y muestre la animacion de quieto
}
bool Player::isKeyPressed(EventCode nuevoEvento) {
    return ( (nuevoEvento == SDL_KEY_A_PRESSED) or (nuevoEvento == SDL_KEY_S_PRESSED) or (nuevoEvento == SDL_KEYUP_PRESSED) or (nuevoEvento == SDL_KEYDOWN_PRESSED) or (nuevoEvento == SDL_KEYLEFT_PRESSED) or (nuevoEvento == SDL_KEYRIGHT_PRESSED));
}
bool Player::isKeyRealeased(EventCode nuevoEvento) {

    return ( (nuevoEvento == SDL_KEY_A_RELEASED) or (nuevoEvento == SDL_KEY_S_RELEASED) or (nuevoEvento == SDL_KEYUP_RELEASED) or (nuevoEvento == SDL_KEYDOWN_RELEASED) or (nuevoEvento == SDL_KEYLEFT_RELEASED) or (nuevoEvento == SDL_KEYRIGHT_RELEASED));
}

void Player::handleRealeasedKey(EventCode nuevoEvento) {
    switch (nuevoEvento) {
        //REALEASED____________________________________________________________________________________________________________

        case EventCode::SDL_KEYLEFT_RELEASED:
            if(direccionX == -1){
                if(postura == Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA){postura = Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO;}
                else if(postura == Postura::CAMINANDO_IZQUIERDA){postura = Postura::MIRANDO_IZQUIERDA_QUIETO;}
                else if(postura == Postura::AGACHADO_AVANZANDO_IZQUIERDA){postura = Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO;}
                direccionX = 0;
            }
            /* Puede estar tocando ambas teclas a la vez, y suelta una de ellas */
            else if(direccionX == 0){
                if(postura == Postura::MIRANDO_DERECHA_QUIETO){postura = CAMINANDO_DERECHA;}
                else if(postura == Postura::AGACHADO_MIRANDO_DERECHA_QUIETO){postura = Postura::AGACHADO_AVANZANDO_DERECHA;}
                else if(postura == Postura::MIRANDO_ARRIBA_DERECHA_QUIETO){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA;}
                direccionX = 1;
            }
            break;
        case EventCode::SDL_KEYRIGHT_RELEASED:
            if(direccionX == 1){
                if(postura == Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA){postura = Postura::MIRANDO_ARRIBA_DERECHA_QUIETO;}
                else if(postura == Postura::CAMINANDO_DERECHA){postura = Postura::MIRANDO_DERECHA_QUIETO;}
                else if(postura == Postura::AGACHADO_AVANZANDO_DERECHA){postura = Postura::AGACHADO_MIRANDO_DERECHA_QUIETO;}
                direccionX = 0;
            }
            /* Puede estar tocando ambas teclas a la vez, y suelta una de ellas. */
            else if(direccionX == 0){
                if(postura == Postura::MIRANDO_IZQUIERDA_QUIETO){postura = CAMINANDO_IZQUIERDA;}
                else if(postura == Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO){postura = Postura::AGACHADO_AVANZANDO_IZQUIERDA;}
                else if(postura == Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA;}
                direccionX = -1;
            }
            break;
        case EventCode::SDL_KEYUP_RELEASED:
            switch (postura){
                case Postura::MIRANDO_ARRIBA_DERECHA_QUIETO: postura = Postura::MIRANDO_DERECHA_QUIETO;
                    break;
                case Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO: postura = Postura::MIRANDO_IZQUIERDA_QUIETO;
                    break;
                case Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA: postura = Postura::CAMINANDO_DERECHA;
                    break;
                case Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA: postura = Postura::CAMINANDO_IZQUIERDA;
                    break;
                default:
                    postura = Postura::MIRANDO_DERECHA_QUIETO;
                    break;
            }

        case EventCode::SDL_KEYDOWN_RELEASED:
            switch (postura){
                case Postura::AGACHADO_MIRANDO_DERECHA_QUIETO: postura = Postura::MIRANDO_DERECHA_QUIETO;
                    break;
                case Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO: postura = Postura::MIRANDO_IZQUIERDA_QUIETO;
                    break;
                case Postura::AGACHADO_AVANZANDO_DERECHA: postura = Postura::CAMINANDO_DERECHA;
                    break;
                case Postura::AGACHADO_AVANZANDO_IZQUIERDA: postura = Postura::CAMINANDO_IZQUIERDA;
                    break;
                default:
                    postura = Postura::MIRANDO_DERECHA_QUIETO;
                    break;
            }
        default:
            break;

    }
}
void Player::handlePressedKey(EventCode nuevoEvento){
    switch (nuevoEvento){
        //PRESSED____________________________________________________________________________________________________________
        case EventCode::SDL_KEY_A_PRESSED:
            direccionY = 1;
            break;

        case EventCode::SDL_KEYUP_PRESSED:
            if(direccionX == 1){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA;}
            else if(direccionX == -1){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA;}
            else if(postura == Postura::MIRANDO_IZQUIERDA_QUIETO and direccionX == 0){postura = Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO;}
            else {postura = Postura::MIRANDO_ARRIBA_DERECHA_QUIETO;}
            break;

        case EventCode::SDL_KEYDOWN_PRESSED:
            if(direccionX == 1){postura = Postura::AGACHADO_AVANZANDO_DERECHA;}
            else if(direccionX == -1){postura = Postura::AGACHADO_AVANZANDO_IZQUIERDA;}
            else if(postura == Postura::MIRANDO_IZQUIERDA_QUIETO and direccionX == 0){postura = Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO;}
            else {postura = Postura::AGACHADO_MIRANDO_DERECHA_QUIETO;}
            break;

        case EventCode::SDL_KEYLEFT_PRESSED:
            if(direccionX == 0){
                if((postura == Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or (postura == Postura::MIRANDO_ARRIBA_DERECHA_QUIETO)){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA;}
                else if((postura == Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::AGACHADO_MIRANDO_DERECHA_QUIETO)){postura = Postura::AGACHADO_AVANZANDO_IZQUIERDA;}
                else if((postura == Postura::MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::MIRANDO_DERECHA_QUIETO)){postura = Postura::CAMINANDO_IZQUIERDA; }
                else{postura = Postura::CAMINANDO_IZQUIERDA;}
                direccionX = -1;
            }
            /* Si está caminando hacia la derecha y presiona LEFT entonces queda quieto */
            else if(direccionX == 1){
                direccionX = 0;
                postura = Postura::MIRANDO_DERECHA_QUIETO;}
            break;

        case EventCode::SDL_KEYRIGHT_PRESSED:
            if(direccionX == 0){
                if((postura == Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or (postura == Postura::MIRANDO_ARRIBA_DERECHA_QUIETO)){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA;}
                else if((postura == Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::AGACHADO_MIRANDO_DERECHA_QUIETO)){postura = Postura::AGACHADO_AVANZANDO_DERECHA;}
                else if((postura == Postura::MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::MIRANDO_DERECHA_QUIETO)){postura = Postura::CAMINANDO_DERECHA; }
                else{postura = Postura::CAMINANDO_DERECHA;}
                direccionX = 1;
            }
            /* Si está caminando hacia la izquierda y presiona RIGHT entonces queda quieto */
            else if(direccionX == -1){
                direccionX = 0;
                postura = Postura::MIRANDO_IZQUIERDA_QUIETO;}
            break;

        default:
            break;
    }
}


void Player::updateState(EventCode nuevoEvento){

		if (nuevoEvento == EventCode::CLIENT_DISCONNECT){
			// TODO: aca hay que hacer que el personaje aparezca grisado, y se permita
			// arrastarlo por la pantalla
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
    if(this->isMoving()) {
        if ((!((direccionX == -1) and (x <= speed))) or (!((direccionX == 1) and (x == windowWidth)))) {
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

void Player::avanzar(){
    x += speed;
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


//_________________________________________

bool Player::isInHalfWindow() {
	return (x >= ((windowWidth/2)-speed));
}



















































