#ifndef SERVER_ITEM_H
#define SERVER_ITEM_H


#include "GameObject.h"

class Weapon : public GameObject {
private:
    int ammo;
public:
    void shoot(){
        ammo--;
        // esto va a cambiar y va a soltar una proyectil o algo (Hay que decidirlo)
    };

    virtual event getState() override;

    virtual void avanzar() override;
};


#endif //SERVER_ITEM_H
