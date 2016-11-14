
#ifndef SERVER_NOTMOVEBULLETSTRATEGY_H
#define SERVER_NOTMOVEBULLETSTRATEGY_H


#include "BulletMovementStrategy.h"

class NotMoveBulletStrategy : public BulletMovementStrategy {
public:
    virtual void avanzar(vector<GameObject *> collisionables, GameObject *bullet) override;
};


#endif //SERVER_NOTMOVEBULLETSTRATEGY_H
