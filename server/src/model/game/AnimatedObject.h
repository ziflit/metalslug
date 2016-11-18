#ifndef SERVER_ANIMATEDOBJECT_H
#define SERVER_ANIMATEDOBJECT_H


#include <iostream>
#include "GameObject.h"
#include "Vector.h"

class AnimatedObject : public GameObject {
protected:
    int health;
    int direccionX;
    int direccionY;
    int fsalto;
    int ammo;
    Entity bulletType;
    Postura postura;
    bool isShooting;
    bool isJumping;
    int puntaje;
    Vector *bulletdirection;

    vector<Entity> shootsTo;
public:
    AnimatedObject() {
        bulletdirection = new Vector(1, 0);
    }

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
        if (this->direccionY == direccionY) {
            return;
        }
        this->fsalto = 60;
        this->direccionY = direccionY;
        if (this->direccionY != 0) {
            setJumpingState(true);
        }
    }

    int receiveDamage(int damage) { //devuelve la vida que le queda 
        if (health >= damage) {
            health -= damage;
        } else {
            health = 0;
            postura = MUERTO;
        }
        string a = (postura == MUERTO) ? " muerto " : " vivo ";
        cout << id << a << health << endl;
        return health;
    }

    virtual ~AnimatedObject() {
        delete this->bulletdirection;
    }

    bool getShootingState() {
        return isShooting;
    }

    void setShootingState(bool shootingState) {
        this->isShooting = shootingState;
    }

    bool getJumpingState() {
        return isJumping;
    }

    void setJumpingState(bool jumpingState) {
        this->isJumping = jumpingState;
    }

    vector<Entity> &getShootsTo() {
        return shootsTo;
    }

    void setShootsTo(vector<Entity> &shootsTo) {
        AnimatedObject::shootsTo = shootsTo;
    }

    Vector *getBulletdirection() {
        return bulletdirection;
    }

    void updateBulletdirection(float x, float y) {
        AnimatedObject::bulletdirection->setX(x);
        AnimatedObject::bulletdirection->setY(y);
    }

    Entity getBulletType() {
        return bulletType;
    }

    int getAmmo() {
        return ammo;
    }

    void setAmmo(int ammo) {
        AnimatedObject::ammo = ammo;
    }

    void setBulletType(Entity bulletType) {
        AnimatedObject::bulletType = bulletType;
    }

    int getPoints(){
        return this->puntaje;
    }

    void updateScore(int points){
        this->puntaje += points;
    }
};

#endif //SERVER_ANIMATEDOBJECT_H
