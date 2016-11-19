#include "Bullet.h"

Bullet::Bullet(Entity bulletType, int spawnX, int spawnY, int direccionY, int direccionX,
               vector<Entity> collitionables, BulletMovementStrategy *bulletMovementStrategy, 
               AnimatedObject* bulletOwner) {
    id = bulletType;
    x = spawnX;
    y = spawnY;
    this->direccionY = direccionY;
    this->direccionX = direccionX;
    this->colisionables = collitionables;
    this->movementStrategy = bulletMovementStrategy;
    this->bulletOwner = bulletOwner;
}

Bullet::~Bullet() {
    delete movementStrategy;
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

void Bullet::avanzar(vector<GameObject *> collitionables) {
    movementStrategy->avanzar(collitionables, this);
}

int Bullet::getDamage() const {
    return damage;
}

void Bullet::setDamage(int damage) {
    this->damage = damage;
}
