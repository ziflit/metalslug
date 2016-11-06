//
// Created by leandro on 31/10/16.
//

#include <iostream>
#include "Enemy.h"
#include "Bullet.h"
#include "NormalBulletMovementStrategy.h"

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
    isShooting = false;
    isJumping = false;
    bulletType = Entity::BT_BULLET;  //Comienza con la pistola normal
}

Enemy::~Enemy() {
}

void Enemy::set_position(int posx, int posy) {
    x = posx;
    y = posy;
}

void Enemy::retroceder(){
    postura = CAMINANDO_IZQUIERDA;
    x -= speed;
}

void Enemy::updatePosition(int posPlayerToFollow) {
	// Minima logica para seguir a los jugadores, mejorarla por favor
	if (x < posPlayerToFollow - 100 ){
		//avanzar();
	} else if (x > posPlayerToFollow + 100 ){
        retroceder();
	}

	// Logica insolita para saltar cuando pasa por esas posiciones
	if (x == 50 || x == 350 || x == 700){
		isJumping = true;
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
}

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
}

void Enemy::avanzar(vector<GameObject *> gameObjects) {
    postura = CAMINANDO_DERECHA;
    x += speed;
}

GameObject *Enemy::shoot() {
    Bullet *bullet = new Bullet(bulletType, this->x, this->y, this->direccionX, this->direccionY, shootsTo, new NormalBulletMovementStrategy());
    ammo--;
    return bullet;
};
