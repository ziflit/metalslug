/*
 * Player.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

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
	x = 100;
	y = 550;
	direccion = 0;
	speed = 10;
    postura = Postura ::MIRANDO_DERECHA_QUIETO;
}

Player::~Player() {
}

void Player::set_position(unsigned int posx, unsigned int posy) {
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
	setNextSpriteFrame();
//  Player::set_position(Player::destRect.x + speed, Player::destRect.y);}
	unsigned int newPos = (x + speed);
	if(newPos < (windowWidth/2)){
		set_position(newPos, y);}
}


void jump() {
	//TODO: Hay que ver como hacer con los saltos y los "eventos" que toman mas de una posicion...
	// se me ocurre que haya como un thread subiendole y bajandole el valor en y pero es muy bizarro.
	// ALGUNA IDEA? puede ser que este quemado, son las 3.22am
}

void Player::stopMoving(){
	direccion = 0;
	//TODO: Aca habria que cambiar algo de frames? para que quede quieto y muestre la animacion de quieto
}
bool Player::isKeyPressed(EventCode nuevoEvento) {
    return ((nuevoEvento == SDL_KEYUP_PRESSED) or (nuevoEvento == SDL_KEYDOWN_PRESSED) or (nuevoEvento == SDL_KEYLEFT_PRESSED) or (nuevoEvento == SDL_KEYRIGHT_PRESSED));
}
bool Player::isKeyRealeased(EventCode nuevoEvento) {

    return ((nuevoEvento == SDL_KEYUP_RELEASED) or (nuevoEvento == SDL_KEYDOWN_RELEASED) or (nuevoEvento == SDL_KEYLEFT_RELEASED) or (nuevoEvento == SDL_KEYRIGHT_RELEASED));
}

void Player::handleRealeasedKey(EventCode nuevoEvento) {
    switch (nuevoEvento) {
        //REALEASED____________________________________________________________________________________________________________
        case EventCode::SDL_KEYLEFT_RELEASED:
            if(direccion == -1){
                if(postura == Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA){postura = Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO;}
                else if(postura == Postura::CAMINANDO_IZQUIERDA){postura = Postura::MIRANDO_IZQUIERDA_QUIETO;}
                else if(postura == Postura::AGACHADO_AVANZANDO_IZQUIERDA){postura = Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO;}
                direccion = 0;
            }
            if(direccion = 0){
                if(postura == Postura::MIRANDO_DERECHA_QUIETO){postura = CAMINANDO_DERECHA;}
                else if(postura == Postura::AGACHADO_MIRANDO_DERECHA_QUIETO){postura = Postura::AGACHADO_AVANZANDO_DERECHA;}
                else if(postura == Postura::MIRANDO_ARRIBA_DERECHA_QUIETO){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA;}
                direccion = 1;
            }
            break;
        case EventCode::SDL_KEYRIGHT_RELEASED:
            if(direccion == 1){
                if(postura == Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA){postura = Postura::MIRANDO_ARRIBA_DERECHA_QUIETO;}
                else if(postura == Postura::CAMINANDO_DERECHA){postura = Postura::MIRANDO_DERECHA_QUIETO;}
                else if(postura == Postura::AGACHADO_AVANZANDO_DERECHA){postura = Postura::AGACHADO_MIRANDO_DERECHA_QUIETO;}
                direccion = 0;
            }
            if(direccion = 0){
                if(postura == Postura::MIRANDO_IZQUIERDA_QUIETO){postura = CAMINANDO_IZQUIERDA;}
                else if(postura == Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO){postura = Postura::AGACHADO_AVANZANDO_IZQUIERDA;}
                else if(postura == Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA;}
                direccion = -1;
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
        case EventCode::SDL_KEYUP_PRESSED:
            if(direccion == 1){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA;}
            else if(direccion == -1){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA;}
            else if(postura == Postura::MIRANDO_IZQUIERDA_QUIETO and direccion == 0){postura = Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO;}
            else {postura = Postura::MIRANDO_ARRIBA_DERECHA_QUIETO;}
            break;

        case EventCode::SDL_KEYDOWN_PRESSED:
            if(direccion == 1){postura = Postura::AGACHADO_AVANZANDO_DERECHA;}
            else if(direccion == -1){postura = Postura::AGACHADO_AVANZANDO_IZQUIERDA;}
            else if(postura == Postura::MIRANDO_IZQUIERDA_QUIETO and direccion == 0){postura = Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO;}
            else {postura = Postura::AGACHADO_MIRANDO_DERECHA_QUIETO;}
            break;

        case EventCode::SDL_KEYLEFT_PRESSED:
            if(direccion == 0){
                if((postura == Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or (postura == Postura::MIRANDO_ARRIBA_DERECHA_QUIETO)){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_IZQUIERDA;}
                else if((postura == Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::AGACHADO_MIRANDO_DERECHA_QUIETO)){postura = Postura::AGACHADO_AVANZANDO_IZQUIERDA;}
                else if((postura == Postura::MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::MIRANDO_DERECHA_QUIETO)){postura = Postura::CAMINANDO_IZQUIERDA; }
                else{postura = Postura::CAMINANDO_IZQUIERDA;}
                direccion = -1;
            }
            else if(direccion == 1){
                direccion = 0;
                postura = Postura::MIRANDO_DERECHA_QUIETO;}
            break;

        case EventCode::SDL_KEYRIGHT_PRESSED:
            if(direccion == 0){
                if((postura == Postura::MIRANDO_ARRIBA_IZQUIERDA_QUIETO) or (postura == Postura::MIRANDO_ARRIBA_DERECHA_QUIETO)){postura = Postura::MIRANDO_ARRIBA_CAMINANDO_DERECHA;}
                else if((postura == Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::AGACHADO_MIRANDO_DERECHA_QUIETO)){postura = Postura::AGACHADO_AVANZANDO_DERECHA;}
                else if((postura == Postura::MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::MIRANDO_DERECHA_QUIETO)){postura = Postura::CAMINANDO_DERECHA; }
                else{postura = Postura::CAMINANDO_DERECHA;}
                direccion = 1;
            }
            else if(direccion == -1){
                direccion = 0;
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
	return (Player::direccion != 0); // en -1 y 1 se esta moviendo
}

void Player::updatePosition() {
	if(Player::isMoving()) {
		if (!((direccion == -1) and (x == 0)) or (!((direccion == 1) and (x == windowWidth)))) {
			x += direccion*speed;
		}
	}
}

void Player::avanzar(){
    x += speed;
}

void Player::retroceder(){
    x -=speed;
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

void Player::setNextSpriteFrame() {
	if (actualPhotogramOfTheSprite == (anchoDelSprite - 1)) {
		actualPhotogramOfTheSprite = 0;
	}
	x = (anchoDelFotograma * actualPhotogramOfTheSprite);
	actualPhotogramOfTheSprite++;
}


















































