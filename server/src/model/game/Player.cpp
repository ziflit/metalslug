/*
 * Player.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include "Player.h"

Player::Player() {
	username = "user";
	sprite = "../../../../client/view/sprites/player/marco.png";
	x = 1;
	y = 1;
	speed = 0;
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
	speed = 0;
	//TODO: Aca habria que cambiar algo de frames? para que quede quieto y muestre la animacion de quieto
}

void Player::movePlayer(EventCode movimiento){
		switch(movimiento) {
			case EventCode::CLIENT_DISCONNECT:
				// TODO: aca hay que hacer que el personaje aparezca grisado, y se permita
				// arrastarlo por la pantalla
				break;

			case EventCode::SDL_KEYUP:
				upArrowPress();
				break;

			case EventCode::SDL_KEYDOWN:
				downArrowPress();
				break;

			case EventCode::SDL_KEYLEFT:
				moveLeft();
				break;

			case EventCode::SDL_KEYRIGHT:
				moveRight();
				if( isInHalfWindow() ){
					// TODO: Si llego a la mitad de la ventana, tengo que mover el background, como hago? el player conoce al background??
				}
				break;

			default:
				stopMoving();   // Si suelta la tecla, me quedo quieto
				break;
		}
}

struct event Player::playerState(){
	struct event estado;
	struct event_ext eventExt;

    eventExt.code = EventCode::PLAYER_STATUS;
    eventExt.id = Entity::MARCO;  // Hardcodeo el nombre de la entidad
    eventExt.x = x;
    eventExt.y = y;
    eventExt.h = speed;  // asumo que en h mando la velocidad

	estado.completion = EventCompletion::FINAL_MSG;
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


















































