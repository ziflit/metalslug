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
    int direccionX;
    int direccionY;
    Postura postura;
    bool isShooting;
    bool isJumping;

public:
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

    int getDireccionX() {
        return direccionX;
    }

    void setDireccionX(int direccionX) {
        AnimatedObject::direccionX = direccionX;
    }

    int getDireccionY() {
        return direccionY;
    }

    void setDireccionY(int direccionY) {
        AnimatedObject::direccionY = direccionY;
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
