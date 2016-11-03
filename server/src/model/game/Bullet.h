//
// Created by leandro on 02/11/16.
//

#ifndef SERVER_BULLET_H
#define SERVER_BULLET_H


#include "GameObject.h"
#include "AnimatedObject.h"

class Bullet : public AnimatedObject{ 
private:
    int damage;
public:
    int getDamage() const;

    void setDamage(int damage);

public:
    virtual event getState() override;

    virtual void avanzar() override;
};


#endif //SERVER_BULLET_H
