#include <iostream>
#include "BulletMovementStrategy.h"
#include "Bullet.h"


void BulletMovementStrategy::makeCollision(vector<GameObject *> collisionables, GameObject *gameObject) {
    Bullet *bullet = (Bullet *) gameObject;
    for (auto object : collisionables) {
        if (bullet->puedenColisionar(object) && object->checkCollition(bullet)) {
            cout << "colision!" << endl;
            //TODO: aca vamos a tener que setearle a la bala el estado de
            // muerto y realizar el impacto con el objeto colisionado
        }
    }
}


