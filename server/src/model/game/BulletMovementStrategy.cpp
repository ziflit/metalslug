#include "BulletMovementStrategy.h"

BulletMovementStrategy::BulletMovementStrategy(Bullet *bullet) : bullet(bullet) {
}

void BulletMovementStrategy::makeCollition(vector<GameObject *> collitionables, Bullet &bullet) {
    for (auto object : collitionables) {
        if (object->getY() == bullet.getY() && object->getX() == bullet.getX()) {

        }
    }
}


