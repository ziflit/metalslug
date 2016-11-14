

#include <iostream>
#include "TeledirBulletMovementStrategy.h"
#include "Bullet.h"
#include "../../utils/MathUtil.h"

void TeledirBulletMovementStrategy::avanzar(vector<GameObject *> collisionables, GameObject *bullet) {
    GameObject *gameObject = getCloserObject(collisionables, bullet);
    if (gameObject != nullptr) {
        changeBulletDirection(bullet, gameObject);
    }

    float x = bullet->getX() + bullet->getDireccionX() * bullet->getSpeed();
    float y = bullet->getY() - bullet->getDireccionY() * bullet->getSpeed();
    bullet->setX(x);
    bullet->setY(y);

    makeCollision(collisionables, bullet);
}

void TeledirBulletMovementStrategy::changeBulletDirection(GameObject *bullet, GameObject *gameObject) {
    if (bullet->getX() < gameObject->getX()) {
        bullet->setDireccionX(1);
    } else if (bullet->getX() > gameObject->getX()) {
        bullet->setDireccionX(-1);
    } else {
        bullet->setDireccionX(0);
    }

    if (bullet->getY() > gameObject->getY()) {
        bullet->setDireccionY(1);
    } else if (bullet->getY() < gameObject->getY()) {
        bullet->setDireccionY(-1);
    } else {
        bullet->setDireccionY(1);
    }
}

GameObject *TeledirBulletMovementStrategy::getCloserObject(vector<GameObject *> collisionables,
                                                           GameObject *bullet) {
    Bullet *bulletObject = (Bullet *) bullet;
    GameObject *gameObject = nullptr;
    float distance = 99999999;
    for (auto object : collisionables) {
        if (bulletObject->puedenColisionar(object) && object->getEntity() != MSC_PLATFORM &&
            distance > MathUtil::FindDifference(object->getX(), bulletObject->getX())) {
            distance = MathUtil::FindDifference(object->getX(), bulletObject->getX());
            gameObject = object;
        }
    }
    return gameObject;
}
