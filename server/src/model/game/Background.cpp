#include "Background.h"

Background::Background(Entity id, int speed, double largeImage, int windowWidth) {
    x=y=0;
    this->largeImage = largeImage;
    this->id = id;
    this->speed = speed;
    this->windowWidth = windowWidth;
}

void Background::calculateSpeed(int largeMainBackground, int speedMainBackground) {
    this->speed = ((this->largeImage-windowWidth) * speedMainBackground)/(largeMainBackground-windowWidth);
}
void Background::avanzar() {
    if (x + windowWidth >= largeImage) {
        x = 0;
    }
    this->x += speed;
}

struct event Background::getState(){
	struct event estado;
	struct event_ext eventExt;

    eventExt.code = EventCode::BACKGROUND_STATUS;
    eventExt.id = this->id;
    eventExt.x = x;
    eventExt.y = y;

    estado.completion = EventCompletion::PARTIAL_MSG;
    estado.data = eventExt;

    return estado;
}


Background::~Background() {
}
