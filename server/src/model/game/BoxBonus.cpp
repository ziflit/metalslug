/*
 * BoxBonus.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: fpirra
 */

#include "BoxBonus.h"

BoxBonus::BoxBonus(Entity boxType, int posX, int posY) {
    id = boxType;
    x = posX;
    y = posY;
    box_ancho = 50;
    box_alto = 50;
}

BoxBonus::~BoxBonus() {
    // TODO Auto-generated destructor stub
}

struct event BoxBonus::getState() {
    struct event estado;
    struct event_ext eventExt;
    eventExt.code = EventCode::BACKGROUND_STATUS; // TODO No va
    eventExt.id = this->id;

    eventExt.x = x;
    eventExt.y = y;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;

    return estado;
}

void BoxBonus::avanzar(vector<GameObject *> gameObjects) {
    return;
}
