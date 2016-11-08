

#include "TeledirBulletMovementStrategy.h"

void TeledirBulletMovementStrategy::avanzar(vector<GameObject *> collisionables, GameObject *bullet) {
    GameObject *gameObject = getCloserObject(collisionables, bullet);
    if (gameObject == nullptr) return;
    changeBulletDirection(bullet, gameObject);

    float x = bullet->getX() + bullet->getDireccionX() * bullet->getSpeed();
    float y = bullet->getY() + bullet->getDireccionY() * bullet->getSpeed();
    bullet->setX(x);
    bullet->setY(y);

    makeCollision(collisionables, bullet);
}

void TeledirBulletMovementStrategy::changeBulletDirection(GameObject *bullet, GameObject *gameObject) {
    if (bullet->getX() < gameObject->getX()) {
        bullet->setDireccionX(1);
    } else {
        bullet->setDireccionX(-1);
    }

    if (bullet->getY() < gameObject->getY()) {
        bullet->setDireccionY(1);
    } else {
        bullet->setDireccionY(-1);
    }
}

GameObject *TeledirBulletMovementStrategy::getCloserObject(
        const vector<GameObject *> &collisionables,
        const GameObject *bullet) {
    float posX = bullet->getX();
    GameObject *gameObject = nullptr;
    for (auto object : collisionables) {
        if (bullet->getEntity() == object->getEntity() && posX > object->getX()) {
            posX = object->getX();
            gameObject = object;
        }
    }
    return gameObject;
}
