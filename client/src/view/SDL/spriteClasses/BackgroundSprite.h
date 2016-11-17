#ifndef METALSLUG_BACKGROUNDSPRITE_H
#define METALSLUG_BACKGROUNDSPRITE_H

#include "Sprite.h"

class BackgroundSprite : public Sprite {
public:
    BackgroundSprite(SDL_Renderer *renderer, int window_width, int window_height, xmlBackground backgroundConfig) :
            Sprite(renderer) {

        BackgroundSprite::set_position(0,0);
        BackgroundSprite::frameWidth = window_width;
        BackgroundSprite::frameHeight = window_height;

        BackgroundSprite::setWidth(window_width);
        BackgroundSprite::setHeight(window_height);

        BackgroundSprite::sourceRect.w = window_width;
        BackgroundSprite::sourceRect.h = window_height;

        this->setId(backgroundConfig.id);
        this->setUpImage(backgroundConfig.path);
    }

    void handle(struct event nuevoEvento);

    void setFramePosition(int x);

    void setNextStartBackFrame();

    void setSourceRectWidth(int w){sourceRect.w = w;}
    void setSourceRectHeight(int h){sourceRect.h = h;}

    int getSpriteImageWidth() { return this->spriteImageWidth; }
    int getSpriteImageHeight() { return this->spriteImageHeight; }
};




#endif //METALSLUG_BACKGROUNDSPRITE_H
