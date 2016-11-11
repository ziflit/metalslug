//
// Created by mfp on 10/11/16.
//

#ifndef METALSLUG_MISCELANEASPRITE_H
#define METALSLUG_MISCELANEASPRITE_H


#include "Sprite.h"
#include "types.h"

class MiscelaneaSprite : Sprite {
public:
    MiscelaneaSprite(SDL_Renderer *renderer, miscelaneaType type) : Sprite(renderer,
                                                                      0,
                                                                      0) {
        this->id = type.id;
        this->layer = type.layer;
        this->sourceRect.w = type.frameWidth;
        this->sourceRect.h = type.frameHeigth;
        this->destRect.w = type.ancho;
        this->destRect.h = type.alto;
    }
};


#endif //METALSLUG_MISCELANEASPRITE_H
