
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

bool GameObject::checkCollition(int newX, int newY, GameObject *other_object) {
    if (newX + (box_ancho/2) < other_object->getX()) 
        or (newY + box_alto < other_object->getY())
        or (newX > other_object->getX() + other_object->getBoxAncho()/2 ) 
        or (newY > other_object->getY() + other_object->getBoxAlto() ) {
        return false;
    }
    return true;
}

bool GameObject::checkCollition(GameObject *gameObject) {
    return checkCollition(x, y, gameObject);
}

bool GameObject::puedenColisionar(GameObject *otherObj) {
    Entity otherEnt = otherObj->getEntity();
    for (auto entity : this->colisionables) {
        if (entity == otherEnt) {
            return true;
        }
    }
    return false;
}

int GameObject::retroceder(int cantidad) {
    this->x -= cantidad;
    return x;
}

int GameObject::getDireccionX() {
    return direccionX;
}

void GameObject::setDireccionX(int direccionX) {
    GameObject::direccionX = direccionX;
}

int GameObject::getDireccionY() {
    return direccionY;
}

void GameObject::setDireccionY(int direccionY) {
    GameObject::direccionY = direccionY;
}

void GameObject::setColisionables(vector<Entity> &colisionables) {
    GameObject::colisionables = colisionables;
}
