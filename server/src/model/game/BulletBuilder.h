
#ifndef SERVER_BULLETBUILDER_H
#define SERVER_BULLETBUILDER_H


#include "Bullet.h"
#include "AnimatedObject.h"

class BulletBuilder {
private:

    static void setupBullet(Bullet *bullet, int boxAlto, int boxAncho, int damage, int speed, int bulletScore, int directionX,
                            int directionY, vector<Entity> &collisionables);

public:
    Bullet static *createBullet(Entity bulletType, AnimatedObject *firedBy);

};


#endif //SERVER_BULLETBUILDER_H
