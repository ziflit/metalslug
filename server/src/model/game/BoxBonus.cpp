/*
 * BoxBonus.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: fpirra
 */

#include "BoxBonus.h"
#include <time.h>

BoxBonus::BoxBonus(int posX, int posY) {
    // Entity entityBoxArray[6] = {MSC_WEAPON_BOX_HEAVY, MSC_WEAPON_BOX_ROCKET,
    //                             MSC_WEAPON_BOX_SHOT, MSC_WEAPON_BOX_CHASER,
    //                             MSC_POWER_BONUS, MSC_BONUS_KILLALL};
    // int RandIndex = rand() % 6;
    // id = entityBoxArray[RandIndex];
    id = MSC_POWER_BONUS;
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
