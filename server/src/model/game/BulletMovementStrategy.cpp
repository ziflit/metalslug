#include <iostream>
#include "BulletMovementStrategy.h"
#include "Bullet.h"
#include "AnimatedObject.h"


void BulletMovementStrategy::makeCollision(vector<GameObject *> collisionables, GameObject *gameObject) {
    Bullet *bullet = (Bullet *) gameObject;
    for (auto object : collisionables) {
        if (bullet->puedenColisionar(object) && object->checkCollition(bullet)) {
            if (gameObject->getEntity() != MSC_PLATFORM) {
                AnimatedObject *animatedObject = (AnimatedObject *) object;
                animatedObject->receiveDamage(bullet->getDamage());
            }
            bullet->setEntity(DEAD);
            cout << "colision!" << endl;
            //TODO: aca vamos a tener que setearle a la bala el estado de
            // muerto y realizar el impacto con el objeto colisionado
        }
    }
}


