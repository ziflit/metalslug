#ifndef SERVER_ITEM_H
#define SERVER_ITEM_H


#include "GameObject.h"
#include "Bullet.h"

class Weapon : public GameObject {
private:
    Entity typeOfWeapon;
    Entity typeOfBullet;
    int ammo;
public:
    Bullet* shoot();

    virtual event getState() override;

    virtual void avanzar() override;
};


#endif //SERVER_ITEM_H
