//
// Created by leandro on 31/10/16.
//

#include <iostream>
#include "Enemy.h"

Enemy::Enemy(Entity enemySelected, int spawnX, int spawnY) {
    id = enemySelected;
    x = spawnX;
    y = spawnY;
    direccionY = 0;
    direccionX = 0;
    posAtJump = 0;
    gravity = 10;
    speed = 10;
    postura = MIRANDO_IZQUIERDA_QUIETO;
};

Enemy::~Enemy() {
};

void Enemy::set_position(int posx, int posy) {
    x = posx;
    y = posy;
};

bool Enemy::isJumping() {
    return (Enemy::direccionY == 1);
};

void Enemy::avanzar(){
    postura = CAMINANDO_DERECHA;
    x += speed;
};

void Enemy::retroceder(){
    postura = CAMINANDO_IZQUIERDA;
    x -= speed;
};

void Enemy::updatePosition(int posPlayerToFollow) {
	// Minima logica para seguir a los jugadores, mejorarla por favor
	if (x < posPlayerToFollow - 100 ){
		avanzar();
	} else if (x > posPlayerToFollow + 100 ){
        retroceder();
	}

	// Logica insolita para saltar cuando pasa por esas posiciones
	if (x == 50 || x == 350 || x == 600){
		direccionY = 1;
	}

    if (this->isJumping()) {
        if (posAtJump < 24) {
            posAtJump++;
            y = 400 - jumpPos[posAtJump];
        } else {
            direccionY = 0;
            posAtJump = 0;
        }
    }
};

struct event Enemy::getState() {
    struct event estado;
    struct event_ext eventExt;

    eventExt.code = EventCode::ENEMY_STATUS;
    eventExt.id = id;

    eventExt.x = x;  //Actualizo la posicion del player
    eventExt.y = y;
    eventExt.postura = this->postura;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;

    return estado;
};

