//
// Created by leandro on 06/11/16.
//

#ifndef SERVER_TELEDIRMOVEMENTSTRATEGY_H
#define SERVER_TELEDIRMOVEMENTSTRATEGY_H


#include "BulletMovementStrategy.h"

class TeledirBulletMovementStrategy : BulletMovementStrategy{
public:
private:
    virtual void avanzar(vector<GameObject *> collitionables, Bullet &bullet) override;

public:
    TeledirBulletMovementStrategy(Bullet *bullet);

    GameObject *getCloserObject(const vector<GameObject *> &collitionables, const Bullet &bullet);
};


#endif //SERVER_TELEDIRMOVEMENTSTRATEGY_H
