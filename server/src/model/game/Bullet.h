
#ifndef SERVER_BULLET_H
#define SERVER_BULLET_H


#include <vector>
#include "../../utils/Protocol.h"
#include "BulletMovementStrategy.h"
#include "GameObject.h"

class Bullet : public GameObject {
private:
    int damage;
    BulletMovementStrategy *movementStrategy = nullptr;
public:
    Bullet(Entity bulletType, int spawnX, int spawnY, int direccionY, int direccionX,
           vector<Entity> collitionables, BulletMovementStrategy *bulletMovementStrategy);

    virtual ~Bullet();

    int getDamage() const;

    void setDamage(int damage);

    virtual event getState() override;

    void avanzar(vector<GameObject *> collitionables) override;

};


#endif //SERVER_BULLET_H
