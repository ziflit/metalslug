
#include "NormalBulletMovementStrategy.h"


void NormalBulletMovementStrategy::avanzar(vector<GameObject *> collisionables, GameObject *bullet) {
    float x = bullet->getX() + bullet->getDireccionX() * bullet->getSpeed();
    float y = bullet->getY() + bullet->getDireccionY() * bullet->getSpeed();
    bullet->setX(x);
    bullet->setY(y);
    makeCollision(collisionables, bullet);
}
