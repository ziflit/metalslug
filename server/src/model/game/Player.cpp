#include <iostream>
#include "Player.h"
#include "BulletBuilder.h"
#include "BonusManager.h"

Player::Player(string user, Entity entitySelected, int windowWidth, int groupId) {
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
    y = 0;
    box_alto = 100; // TODO inicializar esto desde el XML y no acá
    box_ancho = 50;
    direccionY = 0;
    direccionX = 0;
    gravity = 10;
    speed = 10;
    postura = MIRANDO_DERECHA_QUIETO;
    health = PLAYER_HEALTH;
    //todo: hay que ver cuanta vida le vamos a meter,
    //todo: tambien tener en cuenta el modo de juego con vida infinita. (Leer enunciado de TP)
    //todo: terminar de configurar esto en PlayerBuilder, ya esta encaminado.
    this->groupId = groupId;

    isShooting = false;
    isJumping = false;
    bulletType = Entity::BT_BULLET;  //Comienza con la pistola normal
    puntaje = 0;

    this->colisionables = {BT_BULLET, BT_HEAVY_BULLET, BT_MISSILE, BT_SHOT, BT_BOMB,
                           MSC_WEAPON_BOX_HEAVY, MSC_WEAPON_BOX_ROCKET, MSC_WEAPON_BOX_SHOT,
                           MSC_WEAPON_BOX_CHASER, MSC_POWER_BONUS, MSC_BONUS_KILLALL, MSC_PLATFORM};
    this->shootsTo = {ENEMY_NORMAL_1, ENEMY_NORMAL_2, ENEMY_NORMAL_3, ENEMY_FINAL_1,
                      ENEMY_FINAL_2, ENEMY_FINAL_3, MSC_PLATFORM};

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

bool Player::haveBullets() {
    return ammo > 0;
}


GameObject *Player::shoot() {
    // TODO : ver tema cuando no quedan mas balas
    if (ammo > 0) {
        ammo--;
    } else {
        bulletType = BT_BULLET;
        // TODO: Habria que ver como cambiar el arma, a pistola comun si se acabaron las balas
    }
    return BulletBuilder::createBullet(bulletType, this);
};


void Player::updatePosition(vector<GameObject *> game_objects) {
    if (this->postura != DESCONECTADO) {
        int newX = x;
        int newY = y;
        if (this->isMoving()) {
            if (((direccionX == 1) and (x < (windowWidth - 100))) or ((direccionX == -1) and (x > 0))) {
                newX = x + direccionX * speed;
            }
            if (this->canIMove(game_objects, newX, newY)) {
                this->set_position(newX, newY);
            }
        }
        /* Checkeo de gravedad */

        int newYconGravedad = y + gravity; //HACK HORRIBLE para ver si puedo saltar, y no saltar en el aire
        if (this->canIMove(game_objects, newX, newYconGravedad + this->box_alto)) {
            isJumping = false;
        }

        newY -= ((fsalto * this->direccionY) + (gravity * -1));
        if (fsalto > 0) {
            fsalto -= gravity;
        }
        if (fsalto == 0) {
            this->setDireccionY(0);
        }
        if (this->canIMove(game_objects, newX, newY + this->box_alto)) {
            this->set_position(newX, newY);
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

    sprintf(eventExt.username, "%.20s", this->username.c_str());

    eventExt.x = x;  //Actualizo la posicion del player
    eventExt.y = y;
    eventExt.postura = this->postura;
    eventExt.puntaje = this->puntaje;
    eventExt.health = this->health;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;

    return estado;
}

bool Player::canIMove(vector<GameObject *> game_objects, int newX, int newY) {
    /* Auto??? que pasa con las cosas abstractas? */
    bool isColisionanding;
    for (auto &game_object : game_objects) {
        // Checkeo de colisiones
        if (this->puedenColisionar(game_object)) {
            isColisionanding = this->checkCollition(newX, newY, game_object);
            if (isColisionanding) {
                // resolucion de colisiones con el game_object:
                return BonusManager::execute(game_object, game_objects, this);
            }
        }
    }
    return true;
}

int Player::getGroupId() const {
    return groupId;
}

void Player::setGroupId(int groupId) {
    Player::groupId = groupId;
}
