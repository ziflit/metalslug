#ifndef SERVER_TELEDIRMOVEMENTSTRATEGY_H
#define SERVER_TELEDIRMOVEMENTSTRATEGY_H


#include "BulletMovementStrategy.h"
#include "GameObject.h"

class TeledirBulletMovementStrategy : public BulletMovementStrategy {
private:

    GameObject *getCloserObject(vector<GameObject *> collisionables, GameObject *bullet);

    void changeBulletDirection(GameObject *bullet, GameObject *gameObject);

public:


    virtual void avanzar(vector<GameObject *> collisionables, GameObject *bullet) override;
};


#endif //SERVER_TELEDIRMOVEMENTSTRATEGY_H
