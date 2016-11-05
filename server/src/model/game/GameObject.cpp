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

bool GameObject::puedenColisionar(GameObject *obj1, GameObject *obj2) {
    /* Checkeo de las 2 entities posta, y devuelvo true según una tabla
       predefinida de colisiones. Es una suma de ifs gigante */
    Entity ent1 = obj1->getEntity();
    Entity ent2 = obj2->getEntity();
    /* Los background no chocan contra nada */
    if (ent1 == BACKGROUND_Z0 or ent1 == BACKGROUND_Z1 or ent1 == BACKGROUND_Z2 or ent1 == BACKGROUND_Z3 or
        ent2 == BACKGROUND_Z0 or ent2 == BACKGROUND_Z1 or ent2 == BACKGROUND_Z2 or ent2 == BACKGROUND_Z3) {
        return false;
    }
    /* Los player no chocan entre ellos */
    if (((ent1 == MARCO || ent1 == FIO || ent1 == ERI || ent1 == TARMA) and
        (ent2 == MARCO || ent2 == FIO || ent2 == ERI || ent2 == TARMA)) or
        ((ent2 == MARCO || ent2 == FIO || ent2 == ERI || ent2 == TARMA) and
         (ent1 == MARCO || ent1 == FIO || ent1 == ERI || ent1 == TARMA))) {
        return false;
    }
    /* Enemigo y player no colisionan */
    if (((ent1 == ENEMY_NORMAL_1 or ent1 == ENEMY_NORMAL_2 or ent1 == ENEMY_NORMAL_3) and
        (ent2 == MARCO or ent2 == FIO or ent2 == ERI or ent2 == TARMA)) or
        ((ent1 == MARCO or ent1 == FIO or ent1 == ERI or ent1 == TARMA) and
         (ent2 == ENEMY_NORMAL_1 or ent2 == ENEMY_NORMAL_2 or ent2 == ENEMY_NORMAL_3))) {
        return false;
    }

    return true;
}
