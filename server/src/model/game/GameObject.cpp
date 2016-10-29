//
// Created by leandro on 28/10/16.
//

#include "GameObject.h"

Entity GameObject::getEntity() const {
    return entity;
}

void GameObject::setEntity(Entity entity) {
    GameObject::entity = entity;
}

float GameObject::getX() const {
    return x;
}

void GameObject::setX(float x) {
    GameObject::x = x;
}

float GameObject::getY() const {
    return y;
}

void GameObject::setY(float y) {
    GameObject::y = y;
}

double GameObject::getLarge() const {
    return large;
}

void GameObject::setLarge(double large) {
    GameObject::large = large;
}

float GameObject::getSpeed() const {
    return speed;
}

void GameObject::setSpeed(float speed) {
    GameObject::speed = speed;
}
