#ifndef SERVER_TELEDIRMOVEMENTSTRATEGY_H
#define SERVER_TELEDIRMOVEMENTSTRATEGY_H


#include "BulletMovementStrategy.h"
#include "GameObject.h"

class TeledirBulletMovementStrategy : BulletMovementStrategy {
private:

    GameObject *getCloserObject(const vector<GameObject *> &collisionables, const GameObject *bullet);

    void changeBulletDirection(GameObject *bullet, GameObject *gameObject);

public:


    virtual void avanzar(vector<GameObject *> collisionables, GameObject *bullet) override;
};


#endif //SERVER_TELEDIRMOVEMENTSTRATEGY_H
