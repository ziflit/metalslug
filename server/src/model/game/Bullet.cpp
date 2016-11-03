#include "Bullet.h"

event Bullet::getState() {
    struct event newEvent;
    return newEvent;
}

void Bullet::avanzar() {

}

int Bullet::getDamage() const {
    return damage;
}

void Bullet::setDamage(int damage) {
    Bullet::damage = damage;
}
