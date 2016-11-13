#include <iostream>
#include "BulletMovementStrategy.h"
#include "Bullet.h"
#include "AnimatedObject.h"


void BulletMovementStrategy::makeCollision(vector<GameObject *> collisionables, GameObject *gameObject) {
    Bullet *bullet = (Bullet *) gameObject;
    for (auto object : collisionables) {
        if (bullet->puedenColisionar(object) && object->checkCollition(bullet)) {
            if (object->getEntity() != MSC_PLATFORM) {
                AnimatedObject *animatedObject = (AnimatedObject *) object;
                animatedObject->receiveDamage(bullet->getDamage());
            }
            cout << "colision! con " << object->getEntity() << endl;
            bullet->setEntity(DEAD);
        }
    }
}


