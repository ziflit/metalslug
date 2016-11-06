
#ifndef SERVER_BULLETMOVEMENTSTRATEGY_H
#define SERVER_BULLETMOVEMENTSTRATEGY_H


#include "GameObject.h"


class BulletMovementStrategy {
protected:
    void makeCollision(vector<GameObject *> collisionables, GameObject *bullet);

public:
    virtual void avanzar(vector<GameObject *> collisionables, GameObject *bullet) = 0;
};


#endif //SERVER_BULLETMOVEMENTSTRATEGY_H
