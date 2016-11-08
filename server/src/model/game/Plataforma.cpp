/*
 * Plataforma.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: fpirra
 */

#include "Plataforma.h"

Plataforma::Plataforma(int posX, int posY, int ancho, int largo) {
    id = MSC_PLATFORM;
    x = posX;
    y = posY;
    box_ancho = ancho;
    box_alto = largo;
}

Plataforma::~Plataforma() {
    // TODO Auto-generated destructor stub
}

struct event Plataforma::getState() {
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

void Plataforma::avanzar(vector<GameObject *> gameObjects) {
    return;
}
