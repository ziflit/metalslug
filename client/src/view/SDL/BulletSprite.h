//
// Created by mfp on 10/11/16.
//

#ifndef METALSLUG_BULLETSPRITE_H
#define METALSLUG_BULLETSPRITE_H


#include "Sprite.h"
#include "types.h"

class BulletSprite : Sprite {

public:
    BulletSprite(SDL_Renderer* mainRenderer, bulletType type) : Sprite(mainRenderer,0,0){  //0,0 no importa en el bulletSprite el tamano de ventana
        this->id = type.id;
        this->layer = type.layer;
        this->sourceRect.w = this->destRect.w = type.ancho;
        this->sourceRect.h = this->destRect.h = type.alto;
    }


};


#endif //METALSLUG_BULLETSPRITE_H
