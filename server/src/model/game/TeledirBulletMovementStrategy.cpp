

#include "TeledirBulletMovementStrategy.h"

TeledirBulletMovementStrategy::TeledirBulletMovementStrategy(Bullet *bullet) : BulletMovementStrategy(bullet) {}

void TeledirBulletMovementStrategy::avanzar(vector<GameObject *> collitionables, Bullet &bullet) {
    GameObject *gameObject = getCloserObject(collitionables, bullet);
    if (gameObject == nullptr) return;
    if (bullet.getX() < gameObject->getX()) {
        bullet.setDireccionX(1);
    } else {
        bullet.setDireccionX(-1);
    }

    if (bullet.getY() < gameObject->getY()) {
        bullet.setDireccionY(1);
    } else {
        bullet.setDireccionY(-1);
    }

    float x = bullet.getX() + bullet.getDireccionX() * bullet.getSpeed();
    float y = bullet.getY() + bullet.getDireccionY() * bullet.getSpeed();
    bullet.setX(x);
    bullet.setY(y);

    makeCollition(collitionables,bullet);
}

GameObject *TeledirBulletMovementStrategy::getCloserObject(
        const vector<GameObject *> &collitionables,
        const Bullet &bullet) {
    float posX = bullet.getX();
    GameObject *gameObject = nullptr;
    for (auto object : collitionables) {
        if (bullet.getEntity() == object->getEntity() && posX > object->getX()) {
            posX = object->getX();
            gameObject = object;
        }
    }
    return gameObject;
}
