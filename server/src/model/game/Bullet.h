//
// Created by leandro on 02/11/16.
//

#ifndef SERVER_BULLET_H
#define SERVER_BULLET_H

#include "AnimatedObject.h"
#include "../../utils/Protocol.h"

class Bullet : public AnimatedObject{ 
private:
    int damage;
public:
    Bullet(Entity bulletType, int spawnX, int spawnY, int direccionY, int direccionX);

    virtual ~Bullet();
    
    int getDamage() const;

    void setDamage(int damage);

    virtual event getState();

    virtual void avanzar(int dirX, int dirY, int some_enemy_posX, int some_enemy_posY);
};


#endif //SERVER_BULLET_H
