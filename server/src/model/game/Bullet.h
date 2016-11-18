
#ifndef SERVER_BULLET_H
#define SERVER_BULLET_H


#include <vector>
#include "../../utils/Protocol.h"
#include "BulletMovementStrategy.h"
#include "GameObject.h"
#include "AnimatedObject.h"

class Bullet : public GameObject {
private:
    int damage;
    int bulletScore;
    AnimatedObject* bulletOwner;
    BulletMovementStrategy *movementStrategy = nullptr;
public:
    Bullet(Entity bulletType, int spawnX, int spawnY, int direccionY, int direccionX,
           vector<Entity> collitionables, BulletMovementStrategy *bulletMovementStrategy, AnimatedObject* bulletOwner);

    virtual ~Bullet();

    int getDamage() const;

    void setDamage(int damage);

    virtual event getState() override;

    void avanzar(vector<GameObject *> collitionables) override;

    AnimatedObject* getBulletOwner(){
        return bulletOwner;
    }

    void setBulletScore(int scoreOfThisType){
        bulletScore = scoreOfThisType;
    }

    int getBulletScore(){
        return bulletScore;
    }
};


#endif //SERVER_BULLET_H
