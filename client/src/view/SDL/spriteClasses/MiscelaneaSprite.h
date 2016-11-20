#ifndef METALSLUG_MISCELANEASPRITE_H
#define METALSLUG_MISCELANEASPRITE_H


#include "Sprite.h"
#include "../handlers/types.h"

class MiscelaneaSprite : public Sprite {
public:
    MiscelaneaSprite(SDL_Renderer *renderer, simpleSpriteType type) : Sprite(renderer) {
        this->id = type.id;
        this->layer = type.layer;
        this->sourceRect.w = type.frameWidth;
        this->sourceRect.h = type.frameHeigth;
        this->destRect.w = type.ancho;
        this->destRect.h = type.alto;
    }
    void handle(event newEvent){
        this->set_position(newEvent.data.x, newEvent.data.y);
    }
};


#endif //METALSLUG_MISCELANEASPRITE_H
