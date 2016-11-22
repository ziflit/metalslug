
#include "NotMoveBulletStrategy.h"

void NotMoveBulletStrategy::avanzar(vector<GameObject *> collisionables, GameObject *bullet) {
    Bullet *bulletObject = (Bullet *) bullet;
    if (bulletObject->getCantPasos() < 3){
        float x = bullet->getX() + bullet->getDireccionX() * bullet->getSpeed();
        float y = bullet->getY() - bullet->getDireccionY() * bullet->getSpeed();
        bullet->setX(x);
        bullet->setY(y);
        makeCollision(collisionables, bullet);
        bulletObject->updateCantPasos(1);
    } else {
        bullet->setEntity(DEAD);
    }
}
