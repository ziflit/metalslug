//
// Created by leandro on 31/10/16.
//

#include <iostream>
#include "Enemy.h"

Enemy::Enemy(Entity enemySelected, int spawnX, int spawnY) {
    id = enemySelected;
    x = spawnX;
    y = spawnY;
    box_ancho = 50;
    box_alto = 100;
    direccionY = 0;
    direccionX = 0;
    posAtJump = 0;
    gravity = 10;
    speed = 10;
    postura = MIRANDO_IZQUIERDA_QUIETO;
    this->colisionables = {BT_BULLET, BT_HEAVY_BULLET, BT_MISSILE, BT_TELE_MISSILE, BT_SHOT, BT_BOMB, MSC_PLATFORM};
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

void Enemy::avanzar() {}


int Enemy::retroceder(){
    this->x -= speed;
    return x;
};

void Enemy::updatePosition(int posPlayerToFollow, vector<GameObject*> game_objects) {

    int newX = x;
    int newY = y;

    // Minima logica para seguir a los jugadores, mejorarla por favor
    if (x < posPlayerToFollow - 100 ){
        postura = CAMINANDO_DERECHA;
        newX =  x + speed;
	} else if (x > posPlayerToFollow + 100 ){
        postura = CAMINANDO_IZQUIERDA;
        newX = x - speed;
	}

	// Logica insolita para saltar cuando pasa por esas posiciones
	if (x == 50 || x == 350 || x == 600){
		direccionY = 1;
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

    if (this->canIMove(game_objects, newX, newY)){
        this->set_position(newX,newY);
    }

};

struct event Enemy::getState() {
    struct event estado;
    struct event_ext eventExt;

    eventExt.code = EventCode::ENEMY_STATUS;
    eventExt.id = id;

    eventExt.x = x;  //Actualizo la posicion del enemy
    eventExt.y = y;
    eventExt.postura = this->postura;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;

    return estado;
};


bool Enemy::canIMove(vector<GameObject*> game_objects, int newX, int newY) {
    bool isColisionanding;
    for (auto &game_object : game_objects) {
        // Checkeo de colisiones
        if (this->puedenColisionar(game_object)) {
            isColisionanding = this->checkCollition(newX, newY, game_object);
            if (isColisionanding) {
                // resolucion de colisiones con el game_object:
                return false;
            }
        }
    }
    return true;
}

