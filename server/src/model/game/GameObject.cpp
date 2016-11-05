//
// Created by leandro on 28/10/16.
//

#include "GameObject.h"

Entity GameObject::getEntity() const {
    return id;
}

void GameObject::setEntity(Entity entity) {
    GameObject::id = entity;
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
    return largeImage;
}

void GameObject::setLarge(double large) {
    GameObject::largeImage = large;
}

float GameObject::getSpeed() const {
    return speed;
}

void GameObject::setSpeed(float speed) {
    GameObject::speed = speed;
}

int GameObject::getBoxAlto() const {
	return box_alto;
}

void GameObject::setBoxAlto(int boxAlto) {
	box_alto = boxAlto;
}

int GameObject::getBoxAncho() const {
	return box_ancho;
}

void GameObject::setBoxAncho(int boxAncho) {
	box_ancho = boxAncho;
}

bool GameObject::checkCollition(int newX, int newY, GameObject* other_object) {
    /* SOLO MIRA SI 2 RECTANGULOS COINCIDEN EN UN PUNTO */
    if     ((newX + box_ancho / 2 ) >= other_object->getX() - other_object->getBoxAncho() / 2
        and (newX - box_ancho / 2 ) <= other_object->getX() + other_object->getBoxAncho() / 2
        and (newY + box_alto  / 2 ) >= other_object->getY() - other_object->getBoxAlto()  / 2
        and (newY - box_alto  / 2 ) <= other_object->getY() + other_object->getBoxAlto()  / 2) {
            return true;
    }
    return false;
}

bool GameObject::puedenColisionar(GameObject* otherObj) {
    Entity otherEnt = otherObj->getEntity();
    for (auto entity : this->colisionables) {
        if (entity == otherEnt) {
            return true;
        }
    }
    return false;
}
