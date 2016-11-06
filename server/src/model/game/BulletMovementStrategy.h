//
// Created by leandro on 06/11/16.
//

#ifndef SERVER_BULLETMOVEMENTSTRATEGY_H
#define SERVER_BULLETMOVEMENTSTRATEGY_H


#include "Bullet.h"

class BulletMovementStrategy {
protected:
    Bullet *bullet;

    void makeCollition(vector<GameObject *> collitionables, Bullet &bullet);

public:
    BulletMovementStrategy(Bullet *bullet);

    virtual void avanzar(vector<GameObject *> collitionables, Bullet &bullet) = 0;

};


#endif //SERVER_BULLETMOVEMENTSTRATEGY_H
