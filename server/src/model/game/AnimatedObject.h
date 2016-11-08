//
// Created by leandro on 31/10/16.
//

#ifndef SERVER_ANIMATEDOBJECT_H
#define SERVER_ANIMATEDOBJECT_H


#include "GameObject.h"

class AnimatedObject : public GameObject {
protected:
    int health;
    int ammo;
    Entity bulletType;

    Postura postura;
    bool isShooting;
    bool isJumping;

public:

    virtual GameObject *shoot() = 0;

    Postura getPostura() {
        return postura;
    }

    void setPostura(Postura postura) {
        AnimatedObject::postura = postura;
    }

    int getHealth() {
        return health;
    }

    void setHealth(int health) {
        AnimatedObject::health = health;
    }

    void receiveDamage(int damage) {
        if (health >= damage) {
            health -= damage;
        } else {
            health = 0;
        }
    }

    virtual ~AnimatedObject() {
        //delete this->weapon;
    }
    bool getShootingState() {
        return isShooting;
    }

    void setShootingState(bool shootingState){
        this->isShooting = shootingState;
    }

    bool getJumpingState() {
        return isJumping;
    }

    void setJumpingState(bool jumpingState){
        this->isJumping = jumpingState;
    }
};


#endif //SERVER_ANIMATEDOBJECT_H
