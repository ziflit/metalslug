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


