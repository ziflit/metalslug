#include "Weapon.h"


Bullet* Weapon::shoot(){
    if (ammo > 0){
        Bullet* bullet = new Bullet(typeOfBullet, this->x, this->y, this->direccionX, this->direccionY);
        ammo--;
        return bullet;
    }
        
};

event Weapon::getState() {
    struct event newEvent;
    return newEvent;
}

void Weapon::avanzar() {

}
