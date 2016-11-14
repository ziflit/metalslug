
#include "NotMoveBulletStrategy.h"

void NotMoveBulletStrategy::avanzar(vector<GameObject *> collisionables, GameObject *bullet) {
    makeCollision(collisionables, bullet);
}
