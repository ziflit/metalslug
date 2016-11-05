#include "Bullet.h"

Bullet::Bullet(Entity bulletType, int spawnX, int spawnY, int direccionY, int direccionX) {
    id = bulletType;
    x = spawnX;
    y = spawnY;
    this->direccionY = direccionY;
    this->direccionX = direccionX;
    switch(bulletType) {
        case Entity::BT_HEAVY_BULLET:
            speed = 60;
            damage = 100;
            break;
        case Entity::BT_MISSILE:
            speed = 30;
            damage = 100;
            break;
        case Entity::BT_TELE_MISSILE:
            speed = 10;
            damage = 100;
            break;
        case Entity::BT_SHOT:
            speed = 20;
            damage = 100;
            break;
        default:
            speed = 50;
            damage = 100;
            break;
    }
}

Bullet::~Bullet(){
}

event Bullet::getState() {
    struct event estado;
    struct event_ext eventExt;
    eventExt.code = EventCode::BULLET_STATUS;
    eventExt.id = id;
    eventExt.x = x;  //Actualizo la posicion de la bala
    eventExt.y = y;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;
    return estado;
}

void Bullet::avanzar(int dirX, int dirY, int some_enemy_posX, int some_enemy_posY) { 
    if ( id == Entity::BT_TELE_MISSILE){
        if (x < some_enemy_posX){
            dirX = 1;
        } else {
            dirX = -1;
        }

        if (y < some_enemy_posY){
            dirY = 1;
        } else {
            dirY = -1;
        }
    }

    x += dirX*speed;
    y += dirY*speed;
}

int Bullet::getDamage() const {
    return damage;
}

void Bullet::setDamage(int damage) {
    this->damage = damage;
}
