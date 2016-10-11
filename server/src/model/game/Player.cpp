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

void upArrowPress(){
 // TODO: Comlpetar lo que hace cuando aprieta para arriba
}

void downArrowPress() {
// TODO: Comlpetar lo que hace cuando aprieta para abajo
}

void Player::moveRight() {
/* mueve el sprite en eje X hacia la derecha.
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

void Player::moveLeft() {
//    Player::set_position(Player::destRect.x - speed, Player::destRect.y);}
	setNextSpriteFrame();
	int newPos = (x - speed);
	if(newPos > 0){
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

void Player::updateState(EventCode nuevoEvento){
	switch(nuevoEvento) {
		case EventCode::CLIENT_DISCONNECT:
			// TODO: aca hay que hacer que el personaje aparezca grisado, y se permita
			// arrastarlo por la pantalla
			break;

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
                if((postura == Postura::AGACHADO_MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::AGACHADO_MIRANDO_DERECHA_QUIETO)){postura = Postura::AGACHADO_AVANZANDO_IZQUIERDA;}
                else if((postura == Postura::MIRANDO_IZQUIERDA_QUIETO) or (postura == Postura::MIRANDO_DERECHA_QUIETO)){postura = Postura::CAMINANDO_IZQUIERDA; }
                direccion = -1;
            }
            else if(direccion == 1){
                direccion = 0;
                postura = Postura::MIRANDO_DERECHA_QUIETO;}
            else{direccion = -1;}
			break;

		case EventCode::SDL_KEYRIGHT_PRESSED:
			direccion = 1;
			break;
		case EventCode::SDL_KEYLEFT_RELEASED:
            direccion = 0;
            break;
		case EventCode::SDL_KEYRIGHT_RELEASED:
			direccion = 0;
			break;

		default:
			break;
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


















































