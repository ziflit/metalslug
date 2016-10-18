/*
 * Background.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include "Background.h"

Background::Background(int zindex, int speed, double large) {
    x=y=0;
    this->large = large;
    this->setEntity(zindex);
    this->speed = speed;
}

void Background::calculateSpeed(int largeMainBackground, int speedMainBackground) {
    this->speed = (largeMainBackground/speedMainBackground)/this->large;
}
void Background::avanzar() {
    if (x + 800 >= large) {
        x = 0;
    }
    this->x+=speed;
}

void Background::setEntity(int zindex) {
    switch (zindex){
        case 0:
            this->entity = Entity::BACKGROUND_Z0;
            break;
        case 1:
            this->entity = Entity::BACKGROUND_Z1;
            break;
        case 2:
            this->entity = Entity::BACKGROUND_Z2;
            break;
        case 3:
            this->entity = Entity::BACKGROUND_Z3;
            break;
        default:
            break;
    }
}

struct event Background::getState(){
	struct event estado;
	struct event_ext eventExt;

    eventExt.code = EventCode::BACKGROUND_STATUS;
    eventExt.id = this->entity; //
    eventExt.x = x;
    eventExt.y = y;

	estado.completion = EventCompletion::PARTIAL_MSG;
	estado.data = eventExt;

	return estado;
}


Background::~Background() {
}
