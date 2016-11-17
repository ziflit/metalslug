#ifndef METALSLUG_BULLETSPRITE_H
#define METALSLUG_BULLETSPRITE_H


#include "Sprite.h"
#include "../handlers/types.h"

class BulletSprite : public Sprite {

public:
    BulletSprite(SDL_Renderer* mainRenderer, simpleSpriteType type) : Sprite(mainRenderer){  //0,0 no importa en el bulletSprite el tamano de ventana
        this->id = type.id;
        this->layer = type.layer;
        this->sourceRect.w = type.frameWidth;
        this->sourceRect.h = type.frameHeigth;
        this->destRect.w = type.ancho;
        this->destRect.h = type.alto;
    }

    void handle(struct event event) {
        this->set_position(event.data.x, event.data.y);
    }

};


#endif //METALSLUG_BULLETSPRITE_H
