//
// Created by leandro on 31/10/16.
//

#ifndef SERVER_ENEMY_H
#define SERVER_ENEMY_H


#include "AnimatedObject.h"

class Enemy : public AnimatedObject{
public:
    virtual event getState() override;

    virtual void avanzar() override;
};


#endif //SERVER_ENEMY_H
