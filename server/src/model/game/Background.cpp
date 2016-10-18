/*
 * Background.cpp
 *
 *  Created on: 02/10/2016
 *      Author: fpirra
 */

#include <iostream>
#include "Background.h"

Background::Background(int zindex, int speed, double large) {
    x=y=0;
    this->large = large;
    this->setEntity(zindex);
    this->speed = speed;
}

void Background::calculateSpeed(int largeMainBackground, int speedMainBackground) {
    this->speed = ((this->large-800) * speedMainBackground)/(largeMainBackground-800); //800= windowWidth
    std::cout<<"speed: "<<this->speed<<endl;
}
void Background::avanzar() {
    if (x + 800 >= large) {  //todo: ojo con el framewidth
        x = 0;
    }
    this->x += speed;
    std::cout<<"back x: "<<x<<endl;
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
