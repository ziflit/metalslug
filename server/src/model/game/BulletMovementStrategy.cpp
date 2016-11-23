#include <iostream>
#include "BulletMovementStrategy.h"
#include "Bullet.h"
#include "AnimatedObject.h"


void BulletMovementStrategy::makeCollision(vector<GameObject *> collisionables, GameObject *gameObject) {
    Bullet *bullet = (Bullet *) gameObject;
    for (auto object : collisionables) {
        if (bullet->puedenColisionar(object) && object->checkCollition(bullet)) {
            if (object->getEntity() != MSC_PLATFORM && ((AnimatedObject*)object)->getPostura() != DESCONECTADO) {
                AnimatedObject *animatedObject = (AnimatedObject *) object;
                if (animatedObject->receiveDamage(bullet->getDamage()) >= 0 and (animatedObject->getEntity() == ENEMY_NORMAL_1 or animatedObject->getEntity() == ENEMY_NORMAL_2 or animatedObject->getEntity() == ENEMY_NORMAL_3
                    or animatedObject->getEntity() == ENEMY_FINAL_1 or animatedObject->getEntity() == ENEMY_FINAL_2 or animatedObject->getEntity() == ENEMY_FINAL_3) ){
                    bullet->getBulletOwner()->updateScore(bullet->getBulletScore());
                }
            }
            bullet->setEntity(DEAD);
        }
    }
}


