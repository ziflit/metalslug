#include <iostream>
#include "Enemy.h"
#include "../../utils/MathUtil.h"
#include <algorithm>
#include "BulletBuilder.h"

Enemy::Enemy(int number, Entity enemySelected, int spawnX, int spawnY) {
    this->number = number;
    id = enemySelected;
    x = spawnX;
    y = spawnY;
    health = 100;
    box_ancho = 50;
    box_alto = 100;
    direccionY = 0;
    direccionX = 0;
    posAtJump = 0;
    gravity = 10;
    speed = 9;
    postura = CAMINANDO_IZQUIERDA;
    this->colisionables = {BT_BULLET, BT_HEAVY_BULLET, BT_MISSILE, BT_TELE_MISSILE,
                           BT_SHOT, BT_BOMB, MSC_PLATFORM};
    isShooting = false;
    isJumping = false;
    bulletType = Entity::BT_BULLET;  //Comienza con la pistola normal
    this->shootsTo = {MARCO, TARMA, FIO, ERI, MSC_PLATFORM};
}

Enemy::~Enemy() {
}

void Enemy::set_position(int posx, int posy) {
    x = posx;
    y = posy;
};

int Enemy::retroceder() {
    x -= speed;
    return x;
}

void Enemy::avanzar(vector<GameObject *> gameObjects) {
    postura = CAMINANDO_DERECHA;
    x += speed;
}

/** TENER EN CUENTA CUANDO SE CONFIGUREN LAS POSTURAS
 *  SOLO DEFINIMOS POSIBLES LAS SIGUIENTES:
 *  CAMINANDO_DERECHA
 *  CAMINANDO_IZQUIERDA
 *  DISPARANDO_CAMINANDO_DERECHA
 *  DISPARANDO_CAMINANDO_IZQUIERDA
 *  MUERTO
 */

void Enemy::updatePosition(vector<GameObject *> game_objects) {

    int newX = x;
    int newY = y;

    GameObject *playerToFollow = findCloserPlayerToFollow(game_objects);
    float distance = MathUtil::FindDifference(playerToFollow->getX(), x);
    if (not(distance > 700 || distance < 300)) {
        float playerPosX = playerToFollow->getX();
        if (x < playerPosX - 100) {
            cout << "camino derecha" << endl;
            postura = CAMINANDO_DERECHA;
            newX = x + speed;
        } else if (x > playerPosX + 100) {
            postura = CAMINANDO_IZQUIERDA;
            newX = x - speed;
        }
        /* Se mueve en X */
        if (this->canIMove(game_objects, newX, newY)) {
            this->set_position(newX, newY);
        }
    }
    // Minima logica para seguir a los jugadores, mejorarla por favor
    // Logica insolita para saltar cuando pasa por esas posiciones
    if (x == 50 || x == 350 || x == 600) {
        this->setDireccionY(1);
    }
    int newYconGravedad = y + gravity; //HACK HORRIBLE para ver si puedo saltar, y no saltar en el aire
    if (this->canIMove(game_objects, newX, newYconGravedad + this->box_alto)) {
        fsalto = 0;    //Se tiene que optimizar esto moviendolo al chequeo de can i jump, cuando aprieta la A
    }

    newY -= ((this->direccionY * fsalto) + (gravity * -1));
    if (fsalto > 0) {
        fsalto -= gravity;
    }
    if (fsalto == 0) {
        this->setDireccionY(0);
    }
    if (this->canIMove(game_objects, newX, newY + this->box_alto)) {
        this->set_position(newX, newY);
    }

};

struct event Enemy::getState() {
    struct event estado;
    struct event_ext eventExt;

    eventExt.code = EventCode::ENEMY_STATUS;
    eventExt.id = id;
    sprintf(eventExt.username, "%.20s", (to_string(number)).c_str());

    eventExt.x = x;  //Actualizo la posicion del enemy
    eventExt.y = y;
    eventExt.postura = this->postura;
    eventExt.health = this->health;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;

    return estado;
}

bool Enemy::canIMove(vector<GameObject *> game_objects, int newX, int newY) {
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

/**
 * Busco el player mas cercano
 * @param gameObjects
 * @return
 */
GameObject *Enemy::findCloserPlayerToFollow(vector<GameObject *> gameObjects) {
    GameObject *player = nullptr;
    float distance = 999999;
    for (auto gameObject : gameObjects) {
        vector<Entity>::iterator it = std::find(fightAgainst.begin(), fightAgainst.end(), gameObject->getEntity());
        if (it != fightAgainst.end() && distance > MathUtil::FindDifference(gameObject->getX(), x)) {
            distance = MathUtil::FindDifference(gameObject->getX(), x);
            player = gameObject;
        }
    }

    return player;
}

GameObject *Enemy::shoot() {
    Bullet *bullet = BulletBuilder::createBullet(bulletType, this);
    return bullet;
};

