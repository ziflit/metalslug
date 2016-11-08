

#ifndef SERVER_NORMALBULLETMOVEMENTSTRATEGY_H
#define SERVER_NORMALBULLETMOVEMENTSTRATEGY_H


#include "BulletMovementStrategy.h"

class NormalBulletMovementStrategy : public BulletMovementStrategy{
public:

    virtual void avanzar(vector<GameObject *> collisionables, GameObject *bullet) override;

};


#endif //SERVER_NORMALBULLETMOVEMENTSTRATEGY_H
